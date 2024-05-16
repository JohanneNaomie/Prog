/*get all classement*/

select * from temps where id_speciale = X order by chrono asc;

select * from temps_categ where id_speciale = X and id_categorie = Y order by chrono asc;

select id_concurrent,sum(chrono) as chrono,id_manche from temps_manche where id_manche = X group by id_concurrent,id_manche order by chrono asc;

select id_concurrent,sum(chrono) as chrono,id_manche from temps_manche where id_manche = X and id_categorie = Y group by id_concurrent,id_manche order by chrono asc;


select id_concurrent,sum(chrono) as chrono,id_saison from temps_saison where id_saison = X group by id_concurrent,id_saison order by chrono asc;

select id_concurrent,sum(chrono) as chrono,id_saison from temps_saison where id_saison = X and id_categorie = Y group by id_concurrent,id_saison order by chrono asc;


create or replace view temps_categ as 
select temps.*,categorie_concurrent.id_categorie from temps 
join categorie_concurrent
on categorie_concurrent.id_concurrent = temps.id_concurrent;

create or replace view temps_manche as 
select  sum(temps_categ.chrono) as total_chrono , temps_categ.id_concurrent,speciale.id_manche,id_categorie from temps_categ 
join speciale
on speciale.id_speciale = temps_categ.id_speciale
group by id_concurrent,id_manche,id_categorie;

create or replace view temps_saison as 
select sum(temps_manche.total_chrono) as total_chrono, id_concurrent,manche.id_saison , id_categorie from temps_manche
join manche
on manche.id_manche = temps_manche.id_manche
group by id_concurrent,id_saison,id_categorie;

create or replace view aff_tss as
SELECT 
    temps_categ.*,nom_speciale,longeur_km,num_concurrent,nom_categorie
FROM 
    temps_categ
JOIN
    speciale
    ON speciale.id_speciale = temps_categ.id_speciale
JOIN categorie
    ON categorie.id_categorie = temps_categ.id_categorie
JOIN 
    concurrent
    ON concurrent.id_concurrent = temps_categ.id_concurrent
order by chrono asc;

SELECT num_concurrent,id_manche,nom_manche,MIN(total_chrono) AS total_chrono
FROM aff_tm
GROUP BY num_concurrent,id_manche,nom_manche;

create or replace view aff_tm as
SELECT 
    temps_manche.*,nom_manche,num_concurrent,nom_categorie
FROM 
    temps_manche
JOIN categorie
ON categorie.id_categorie = temps_manche.id_categorie
JOIN
    manche
    ON manche.id_manche = temps_manche.id_manche
JOIN 
    concurrent
    ON concurrent.id_concurrent = temps_manche.id_concurrent;


SELECT num_concurrent,id_saison,année,MIN(total_chrono) AS total_chrono
FROM aff_ts
GROUP BY num_concurrent,id_saison,année;

create or replace view aff_ts as
SELECT 
    temps_saison.*,année,num_concurrent,nom_categorie
FROM 
    temps_saison
JOIN
    saison
    ON saison.id_saison = temps_saison.id_saison
JOIN 
    categorie
    ON categorie.id_categorie = temps_saison.id_categorie
JOIN 
    concurrent
    ON concurrent.id_concurrent = temps_saison.id_concurrent;


CREATE OR REPLACE VIEW classement_gen_manche as
WITH filtered_temps AS (
   SELECT id_concurrent,id_categorie,num_concurrent,id_manche,nom_manche,MIN(total_chrono) AS total_chrono,nom_categorie
    FROM aff_tm
    GROUP BY num_concurrent,id_manche,nom_manche,id_concurrent,id_categorie,nom_categorie
),
ranked_temps AS (
    SELECT
        *,
        ROW_NUMBER() OVER (PARTITION BY id_manche ORDER BY total_chrono ASC) AS rank
    FROM
        filtered_temps
    order by total_chrono asc
)
SELECT
    ranked_temps.total_chrono,
    ranked_temps.id_concurrent,
    ranked_temps.id_manche,
    ranked_temps.id_categorie,
    ranked_temps.nom_manche,
    ranked_temps.nom_categorie,
    ranked_temps.num_concurrent,
    Point.points
FROM
    ranked_temps
JOIN
    point ON ranked_temps.rank = point.classement
ORDER BY
    ranked_temps.rank

CREATE OR REPLACE VIEW classement_categ_manche as
WITH ranked_temps AS (
    SELECT
        *,
        ROW_NUMBER() OVER (PARTITION BY id_manche,id_categorie ORDER BY total_chrono ASC) AS rank
    FROM
        aff_tm
    order by total_chrono asc
)
SELECT
    ranked_temps.total_chrono,
    ranked_temps.id_concurrent,
    ranked_temps.id_manche,
    ranked_temps.id_categorie,
    ranked_temps.nom_manche,
    ranked_temps.nom_categorie,
    ranked_temps.num_concurrent,
    Point.points
FROM
    ranked_temps
JOIN
    point ON ranked_temps.rank = point.classement
ORDER BY
    ranked_temps.rank

create or replace view classement_saison_gen as
select sum(classement_gen_manche.total_chrono) as total_chrono,classement_gen_manche.id_concurrent,aff_ts.id_saison,classement_gen_manche.id_categorie,aff_ts.année,classement_gen_manche.nom_categorie,classement_gen_manche.num_concurrent,sum(points) as points
from classement_gen_manche
join aff_ts on 
classement_gen_manche.id_concurrent = aff_ts.id_concurrent
group by classement_gen_manche.id_categorie,classement_gen_manche.id_concurrent,aff_ts.id_saison,aff_ts.année,classement_gen_manche.nom_categorie,classement_gen_manche.num_concurrent;


create or replace view temp_saison_categ as
SELECT
    SUM(total_chrono) AS total_chrono,
    id_concurrent,
    id_categorie,
    SUM(points) AS total_points
FROM 
    classement_categ_manche
GROUP BY 
    id_concurrent, id_categorie;

create or replace view temp_saison as
SELECT
    SUM(total_chrono) AS total_chrono,
    id_concurrent,
    id_categorie,
    SUM(points) AS total_points
FROM 
    classement_categ_manche
GROUP BY 
    id_concurrent, id_categorie;


create or replace view classement_saison as
SELECT DISTINCT temp_saison.*, année
FROM temp_saison
LEFT JOIN aff_ts ON temp_saison.id_concurrent = aff_ts.id_concurrent 
order by id_categorie,total_points desc,select count(id_manche) from victoire;

CREATE OR REPLACE VIEW classement_saison AS
SELECT DISTINCT ts.*, v.wins_count, année
FROM temp_saison ts
LEFT JOIN aff_ts at ON ts.id_concurrent = at.id_concurrent 
LEFT JOIN (
    SELECT id_concurrent, COUNT(*) AS wins_count
    FROM victoire
    GROUP BY id_concurrent
) v ON ts.id_concurrent = v.id_concurrent
ORDER BY total_points DESC,v.wins_count ASC;

CREATE OR REPLACE FUNCTION insert_into_victoire()
RETURNS TRIGGER AS $$
BEGIN
    INSERT INTO victoire (id_manche, id_concurrent)
    SELECT id_manche, id_concurrent  FROM classement_categ_manche where id_categorie=5 and points=10 as NEW
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

-- Example: Assuming classement_categ_manche is a view on a table named classement_categ_manche_table
CREATE TRIGGER trg_insert_victoire_after_insert
AFTER INSERT ON manche
FOR EACH ROW EXECUTE PROCEDURE insert_into_victoire();


