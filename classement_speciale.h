#ifndef CLASSEMENT_SPECIALE_H
#define CLASSEMENT_SPECIALE_H


#include "mainwindow.h"
#include "qsqlquery.h"
#include <chrono>
#include <QString>
#include <QSqlDatabase>
#include <QTableWidget>

class Classement_speciale {
public:
    // Constructor
    Classement_speciale(const int id_temps, const std::chrono::milliseconds& chrono,
                        const int id_speciale, const int id_concurrent, const int id_categorie,
                        const QString& nom_speciale, const double longeur_km, const int num_concurrent,QString nom_categorie);

    Classement_speciale(const int id_temps);
    Classement_speciale();


    // Getter methods
    int getIdTemps() const { return id_temps; }
    std::chrono::milliseconds getChrono() const { return chrono; }
    int getIdSpeciale() const { return id_speciale; }
    int getIdConcurrent() const { return id_concurrent; }
    int getIdCategorie() const { return id_categorie; }
    QString getNomSpeciale() const { return nom_speciale; }
    double getLongeurKm() const { return longeur_km; }
    int getNumConcurrent() const { return num_concurrent; }
    QString getNomCategorie() const {return nom_categorie;}

    // Setter methods
    void setIdTemps(const int id) { id_temps = id; }
    void setChrono(const std::chrono::milliseconds& t) { chrono = t; }
    void setIdSpeciale(const int id) { id_speciale = id; }
    void setIdConcurrent(const int id) { id_concurrent = id; }
    void setIdCategorie(const int id) { id_categorie = id; }
    void setNomSpeciale(const QString& n) { nom_speciale = n; }
    void setLongeurKm(const double l) { longeur_km = l; }
    void setNumConcurrent(const int nc) { num_concurrent = nc; }
    void setNomCategorie(const QString c){nom_categorie = c;}

    QVector<Classement_speciale> fetchData(QSqlQuery qry);
    void displayClassement(QTableWidget* tableWidget,const QVector<Classement_speciale>& classe,const MainWindow& mw);
    std::chrono::milliseconds parseTimeString(const std::string& timeStr);
    QString timePointAsString(std::chrono::milliseconds chrono);


private:
    int id_temps;
    std::chrono::milliseconds chrono;
    int id_speciale;
    int id_concurrent;
    int id_categorie;
    QString nom_speciale;
    double longeur_km;
    int num_concurrent;
    QString nom_categorie;

};

#endif // CLASSEMENT_SPECIALE_H
