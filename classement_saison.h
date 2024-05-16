#ifndef CLASSEMENT_SAISON_H
#define CLASSEMENT_SAISON_H

#include "mainwindow.h"

#include <QSqlQuery>
#include <QTableWidget>
#include <QVector>
#include <chrono>
class Classement_saison
{
public:
    Classement_saison();
    // Constructor
    Classement_saison(int idConcurrent, int idSaison, int annee, int numConcurrent, std::chrono::milliseconds totalChrono,int id_categorie,QString nom_categorie,int winsCount,int points);

    // Getter methods
    std::chrono::milliseconds getTotalChrono() const { return total_chrono; }
    int getIdConcurrent() const { return id_concurrent; }
    int getidSaison() const { return id_saison; }
    int getAnnee() const {return annee;}
    int getNumConcurrent() const { return num_concurrent; }
    int getPoints() const {return points;}
    int getIdCategorie() const { return id_categorie; }
    QString getNomCategorie() const {return nom_categorie;}
    int getWinsCount() const {return wins_count;}

    // Setter methods
    void setIdConcurrent(int idConcurrent) { id_concurrent = idConcurrent; }
    void setidSaison(int idSaison) { id_saison = idSaison; }
    void setAnnee(int ann) {annee = ann;}
    void setNumConcurrent(int numConcurrent) { num_concurrent = numConcurrent; }
    void setTotalChrono(std::chrono::milliseconds totalChrono) { total_chrono = totalChrono; }
    void setPoints(int pt){points=pt;}
    void setIdCategorie(const int id) { id_categorie = id; }
    void setNomCategorie(const QString c){nom_categorie = c;}
    void setWinsCount(const int w){wins_count = w;}

    QVector<Classement_saison> fetchData(QSqlQuery qry);
    void displayClassement(QTableWidget* tableWidget,const QVector<Classement_saison>& classe,const MainWindow& mw);
    std::chrono::milliseconds parseTimeString(const std::string& timeStr);
    QString timePointAsString(std::chrono::milliseconds chrono);


private:
    std::chrono::milliseconds total_chrono ;
    int id_concurrent ;
    int id_saison ;
    int annee;
    int num_concurrent;
    int id_categorie;
    QString nom_categorie;
    int wins_count;
    int points;
};

#endif // CLASSEMENT_SAISON_H
