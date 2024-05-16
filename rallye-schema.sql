CREATE DATABASE rallye;

CREATE TABLE pilote(
   id_pilote SERIAL,
   nom_pilote VARCHAR(50) ,
   prenom_pilote VARCHAR(50)  NOT NULL,
   club VARCHAR(50),
   PRIMARY KEY(id_pilote)
);

CREATE TABLE categorie(
   id_categorie SERIAL,
   nom_categorie VARCHAR(50)  NOT NULL,
   PRIMARY KEY(id_categorie)
);

CREATE TABLE voiture(
   id_voiture SERIAL,
   modele_voiture VARCHAR(50)  NOT NULL,
   plaque_immatriculation VARCHAR(10),
   PRIMARY KEY(id_voiture)
);

CREATE TABLE copilote(
   id_copiltoe SERIAL,
   nom_copilote VARCHAR(50)  NOT NULL,
   prenom_copilote VARCHAR(50)  NOT NULL,
   club VARCHAR(50),
   PRIMARY KEY(id_copiltoe)
);

CREATE TABLE saison(
   id_saison SERIAL,
   année INTEGER NOT NULL,
   PRIMARY KEY(id_saison)
);

CREATE TABLE point(
   id_point SERIAL,
   classement INTEGER NOT NULL,
   points INTEGER NOT NULL,
   PRIMARY KEY(id_point)
);

CREATE TABLE concurrent(
   id_concurrent SERIAL,
   num_concurrent INTEGER NOT NULL,
   id_voiture INTEGER NOT NULL,
   id_copiltoe INTEGER NOT NULL,
   id_pilote INTEGER NOT NULL,
   PRIMARY KEY(id_concurrent),
   FOREIGN KEY(id_voiture) REFERENCES voiture(id_voiture),
   FOREIGN KEY(id_copiltoe) REFERENCES copilote(id_copiltoe),
   FOREIGN KEY(id_pilote) REFERENCES pilote(id_pilote)
);

CREATE TABLE manche(
   id_manche SERIAL,
   nom_manche VARCHAR(50) ,
   date_debut DATE,
   date_fin DATE,
   id_saison INTEGER NOT NULL,
   PRIMARY KEY(id_manche),
   FOREIGN KEY(id_saison) REFERENCES saison(id_saison)
);

CREATE TABLE speciale(
   id_speciale SERIAL,
   nom_speciale VARCHAR(50) ,
   longeur_km NUMERIC(15,2)   NOT NULL,
   id_manche INTEGER NOT NULL,
   PRIMARY KEY(id_speciale),
   FOREIGN KEY(id_manche) REFERENCES manche(id_manche)
);

CREATE TABLE temps(
   id_temps SERIAL,
   chrono TIME NOT NULL,
   id_speciale INTEGER NOT NULL,
   id_concurrent INTEGER NOT NULL,
   PRIMARY KEY(id_temps),
   FOREIGN KEY(id_speciale) REFERENCES speciale(id_speciale),
   FOREIGN KEY(id_concurrent) REFERENCES concurrent(id_concurrent)
);

CREATE TABLE categorie_concurrent(
   id_categorie INTEGER,
   id_concurrent INTEGER,
   PRIMARY KEY(id_categorie, id_concurrent),
   FOREIGN KEY(id_categorie) REFERENCES categorie(id_categorie),
   FOREIGN KEY(id_concurrent) REFERENCES concurrent(id_concurrent)
);

insert into pilote values(default,'Razafinjoelina','Tahina','ASACM');
insert into pilote values(default,'Rabekoto','Fred','ASACM');
insert into pilote values(default,'Andrianjafy','Mathieu','ASACM');
insert into pilote values(default,'Rajemison','Ndrianja','ASACM');
insert into pilote values(default,'Andriamanantena','Tahiana','ASACM');
insert into pilote values(default,'Bona','','ASACM');

insert into copilote values(default,'Razafinjoelina','Baovola','ASACM');
insert into copilote values(default,'Rakotomalala','Andry Tahina','ASACM');
insert into copilote values(default,'Rakotomalala','Zanak-Ambila','ASACM');
insert into copilote values(default,'Rajemison','Fanja','ASACM');
insert into copilote values(default,'Andriamanantena','Tahiry','ASACM');
insert into copilote values(default,'Miangaly','','ASACM');
                           
insert into categorie values(default,'M12');
insert into categorie values(default,'N12');
insert into categorie values(default,'mixte');
insert into categorie values(default,'generale');

insert into voiture values(default,'SUBARU IMPREZA','1206 TAN');
insert into voiture values(default,'SUBARU IMPREZA','1345 TBH');
insert into voiture values(default,'SUBARU IMPREZA','8654 TBN');
insert into voiture values(default,'SUBARU IMPREZA','9811 TBG');
insert into voiture values(default,'SUBARU IMPREZA','2365 TBG');
insert into voiture values(default,'SUBARU IMPREZA','1276 TBH');

insert into point values(default,1, 18);
insert into point values(default,2,15);
insert into point values(default,3, 13);
insert into point values(default,4, 10);
insert into point values(default,5, 8);
insert into point values(default,6, 6);
insert into point values(default,7, 4);
insert into point values(default,8, 3);
insert into point values(default,9, 2);
insert into point values(default,10, 1);

insert into concurrent values(default,1,1,1,1);
insert into concurrent values(default,2,2,2,2);
insert into concurrent values(default,3,3,3,3);
insert into concurrent values(default,4,4,4,4);
insert into concurrent values(default,5,5,5,5);
insert into concurrent values(default,6,6,6,6);

insert into categorie_concurrent values(1,1);
insert into categorie_concurrent values(3,1);
insert into categorie_concurrent values(4,1);

insert into categorie_concurrent values(2,2);
insert into categorie_concurrent values(4,2);

insert into categorie_concurrent values(1,3);
insert into categorie_concurrent values(4,3);

insert into categorie_concurrent values(2,4);
insert into categorie_concurrent values(3,4);
insert into categorie_concurrent values(4,4);

insert into categorie_concurrent values(2,5);
insert into categorie_concurrent values(3,5);
insert into categorie_concurrent values(4,5);

insert into categorie_concurrent values(1,6);
insert into categorie_concurrent values(3,6);
insert into categorie_concurrent values(4,6);

insert into saison values(default,2017);

insert into manche (nom_manche,id_saison) values('Rallye FMMSAM',1);
insert into manche (nom_manche,id_saison) values('Rallye Antsirabe',1);
insert into manche (nom_manche,id_saison) values('Rallye GoJanga',1);
insert into manche (nom_manche,id_saison) values('RIM',1);

insert into speciale (nom_speciale,longeur_km,id_manche) values('Ankadilalana - Ambohimanga',7.32,1);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Xt Ampitrevo - Andraikiba',19.51,1);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Ambohinome - Ambodifasina',8.26,1);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Ankorondrano - Ankadimainty 1',12.80,1);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Ankorondrano - Ankadimainty 2',12.80,1);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Tsimahandry - Ambodimanga',18.04,1);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Ambohimasina - Xt Andranovaky',12.70,1);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Xt Must  A - Xt Must B',15.30,3);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Antsanitia - Ampitilova',11.33,3);

CREATE TABLE temps(
   id_temps SERIAL,
   chrono TIME NOT NULL,
   id_speciale INTEGER NOT NULL,
   id_concurrent INTEGER NOT NULL,
   PRIMARY KEY(id_temps),
   FOREIGN KEY(id_speciale) REFERENCES speciale(id_speciale),
   FOREIGN KEY(id_concurrent) REFERENCES concurrent(id_concurrent)
);

insert into temps values(default,'00:17:01',6,3);
insert into temps values(default,'00:16:08',6,1);
insert into temps values(default,'00:16:13',6,2);

insert into temps values(default,'00:10:01',7,3);
insert into temps values(default,'00:10:02',7,1);
insert into temps values(default,'00:10:03',7,2);

insert into temps values(default,'00:04:59',1,3);
insert into temps values(default,'00:04:53',1,1);
insert into temps values(default,'00:05:00',1,2);

insert into temps values(default,'00:18:09',2,3);
insert into temps values(default,'00:18:20',2,1);
insert into temps values(default,'00:18:01',2,2);

/*données rallye*/

insert into categorie values(default,'generale');
insert into categorie values(default,'A');
insert into categorie values(default,'B');

insert into categorie_concurrent values(5,1);
insert into categorie_concurrent values(5,2);
insert into categorie_concurrent values(5,3);
insert into categorie_concurrent values(5,4);
insert into categorie_concurrent values(5,5);
insert into categorie_concurrent values(5,6);

insert into categorie_concurrent values(6,2);
insert into categorie_concurrent values(6,3);
insert into categorie_concurrent values(6,6);

insert into categorie_concurrent values(7,1);
insert into categorie_concurrent values(7,4);
insert into categorie_concurrent values(7,5);

insert into temps values(default,'00:12:45.400',10,1);
insert into temps values(default,'00:15:22.300',11,1);
insert into temps values(default,'00:11:09.268',12,1);
insert into temps values(default,'00:26:39.267',13,1);
insert into temps values(default,'00:19:23.280',14,1);

insert into temps values(default,'00:21:15.275',10,2);
insert into temps values(default,'00:22:18.338',11,2);
insert into temps values(default,'00:12:15.735',12,2);
insert into temps values(default,'00:19:46.186',13,2);
insert into temps values(default,'00:24:06.446',14,2);

insert into temps values(default,'00:25:13.251',10,3);
insert into temps values(default,'00:14:52.145',11,3);
insert into temps values(default,'00:11:29.113',12,3);
insert into temps values(default,'00:26:10.261',13,3);
insert into temps values(default,'00:28:47.285',14,3);

insert into temps values(default,'00:16:09.169',10,4);
insert into temps values(default,'00:17:20.172',11,4);
insert into temps values(default,'00:32:29.323',12,4);
insert into temps values(default,'00:22:48.225',13,4);
insert into temps values(default,'00:29:10.291',14,4);

insert into temps values(default,'00:16:36.164',10,5);
insert into temps values(default,'00:33:13.331',11,5);
insert into temps values(default,'00:11:41.114',12,5);
insert into temps values(default,'00:29:21.292',13,5);
insert into temps values(default,'00:29:57.296',14,5);

insert into temps values(default,'00:27:48.275',10,6);
insert into temps values(default,'00:16:17.162',11,6);
insert into temps values(default,'00:15:47.155',12,6);
insert into temps values(default,'00:21:53.215',13,6);
insert into temps values(default,'00:27:24.272',14,6);

CREATE TABLE victoire(
   id_manche INTEGER NOT NULL,
   id_concurrent INTEGER NOT NULL,
   PRIMARY KEY(id_manche,id_concurrent),
   FOREIGN KEY(id_manche) REFERENCES manche(id_manche),
   FOREIGN KEY(id_concurrent) REFERENCES concurrent(id_concurrent)
);

insert into victoire values(1,1);
INSERT INTO victoire (id_manche, id_concurrent)
SELECT id_manche, id_concurrent  FROM classement_categ_manche where id_categorie=5 and points=10;

insert into manche (nom_manche,id_saison) values('Rallye CTMOTORS',1);

insert into speciale (nom_speciale,longeur_km,id_manche) values('Xt Must  A - Xt Must B',15.30,2);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Antsanitia - Ampitilova',11.33,2);

insert into temps values(default,'00:26:39.267',16,2);
insert into temps values(default,'00:19:23.280',17,2);

insert into temps values(default,'00:19:46.186',16,1);
insert into temps values(default,'00:24:06.446',17,1);

insert into temps values(default,'00:26:10.261',16,3);
insert into temps values(default,'00:28:47.285',17,3);

insert into temps values(default,'00:22:48.225',16,4);
insert into temps values(default,'00:29:10.291',17,4);

insert into temps values(default,'00:29:21.292',16,5);
insert into temps values(default,'00:29:57.296',17,5);

insert into temps values(default,'00:21:53.215',16,6);
insert into temps values(default,'00:27:24.272',17,6);

insert into manche (nom_manche,id_saison) values('Rallye HOHO',1);

insert into temps values(default,'00:38:59.852',15,1);
insert into temps values(default,'00:17:55.075',15,2);
insert into temps values(default,'00:13:57.136',15,3);
insert into temps values(default,'00:34:19.342',15,4);
insert into temps values(default,'00:31:54.315',15,5);
insert into temps values(default,'00:34:48.345',15,6);

insert into speciale (nom_speciale,longeur_km,id_manche) values('Ankorondrano - Ankadimainty 1',12.80,2);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Ankorondrano - Ankadimainty 2',12.80,2);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Tsimahandry - Ambodimanga',18.04,2);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Ambohimasina - Xt Andranovaky',12.70,2);

insert into temps values(default,'00:12:45.400',16,1);
insert into temps values(default,'00:15:22.300',17,1);
insert into temps values(default,'00:11:09.000',18,1);
insert into temps values(default,'00:26:39.267',19,1);
insert into temps values(default,'00:19:23.280',20,1);

insert into temps values(default,'00:21:15.275',16,2);
insert into temps values(default,'00:23:18.000',17,2);
insert into temps values(default,'00:12:15.735',18,2);
insert into temps values(default,'00:19:46.186',19,2);
insert into temps values(default,'00:24:06.446',20,2);

insert into temps values(default,'00:25:13.251',16,3);
insert into temps values(default,'00:10:52.000',17,3);
insert into temps values(default,'00:11:29.113',18,3);
insert into temps values(default,'00:26:10.261',19,3);
insert into temps values(default,'00:28:47.285',20,3);

insert into temps values(default,'00:16:09.169',16,4);
insert into temps values(default,'00:17:20.172',17,4);
insert into temps values(default,'00:32:29.323',18,4);
insert into temps values(default,'00:22:48.225',19,4);
insert into temps values(default,'00:29:10.291',20,4);

insert into temps values(default,'00:16:36.164',16,5);
insert into temps values(default,'00:13:13.000',17,5);
insert into temps values(default,'00:11:41.114',18,5);
insert into temps values(default,'00:29:21.292',19,5);
insert into temps values(default,'00:19:57.000',20,5);

insert into temps values(default,'00:27:48.275',16,6);
insert into temps values(default,'00:16:17.162',17,6);
insert into temps values(default,'00:15:47.155',18,6);
insert into temps values(default,'00:21:53.215',19,6);
insert into temps values(default,'00:27:24.272',20,6);

insert into temps values(default,'00:38:59.852',21,1);
insert into temps values(default,'00:17:55.075',21,2);
insert into temps values(default,'00:13:57.136',21,3);
insert into temps values(default,'00:34:19.342',21,4);
insert into temps values(default,'00:11:54.000',21,5);
insert into temps values(default,'00:34:48.345',21,6);


insert into speciale (nom_speciale,longeur_km,id_manche) values('Ankadilalana - Ambohimanga',7.32,3);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Xt Ampitrevo - Andraikiba',19.51,3);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Ambohinome - Ambodifasina',8.26,3);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Ankorondrano - Ankadimainty 1',12.80,3);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Ankorondrano - Ankadimainty 2',12.80,3);
insert into speciale (nom_speciale,longeur_km,id_manche) values('Tsimahandry - Ambodimanga',18.04,3);

insert into temps values(default,'00:12:45.400',22,1);
insert into temps values(default,'00:15:22.300',23,1);
insert into temps values(default,'00:12:09.000',24,1);
insert into temps values(default,'00:16:39.000',25,1);
insert into temps values(default,'00:19:23.280',26,1);

insert into temps values(default,'00:21:15.275',22,2);
insert into temps values(default,'00:22:18.338',23,2);
insert into temps values(default,'00:12:15.735',24,2);
insert into temps values(default,'00:19:46.186',25,2);
insert into temps values(default,'00:24:06.446',26,2);

insert into temps values(default,'00:25:13.251',22,3);
insert into temps values(default,'00:14:52.145',23,3);
insert into temps values(default,'00:11:29.113',24,3);
insert into temps values(default,'00:22:10.000',25,3);
insert into temps values(default,'00:28:47.285',26,3);

insert into temps values(default,'00:16:09.169',22,4);
insert into temps values(default,'00:17:20.172',23,4);
insert into temps values(default,'00:32:29.323',24,4);
insert into temps values(default,'00:22:48.225',25,4);
insert into temps values(default,'00:29:10.291',26,4);

insert into temps values(default,'00:16:36.164',22,5);
insert into temps values(default,'00:33:13.331',23,5);
insert into temps values(default,'00:11:41.114',24,5);
insert into temps values(default,'00:29:21.292',25,5);
insert into temps values(default,'00:29:57.296',26,5);

insert into temps values(default,'00:20:48.000',22,6);
insert into temps values(default,'00:16:17.162',23,6);
insert into temps values(default,'00:15:47.155',24,6);
insert into temps values(default,'00:21:53.215',25,6);
insert into temps values(default,'00:27:24.272',26,6);

insert into temps values(default,'00:38:59.852',27,1);
insert into temps values(default,'00:17:55.075',27,2);
insert into temps values(default,'00:34:48.345',27,3);
insert into temps values(default,'00:34:19.342',27,4);
insert into temps values(default,'00:31:54.315',27,5);
insert into temps values(default,'00:14:48.000',27,6);

insert into manche (nom_manche,id_saison) values('Rallye DMAX',1);