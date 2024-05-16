#ifndef CLASSEMENT_MANCHE_CATEG_H
#define CLASSEMENT_MANCHE_CATEG_H

#include "mainwindow.h"

#include <QSqlQuery>
#include <QTableWidget>
#include <QVector>
#include <chrono>
class Classement_manche_categ
{
public:
    Classement_manche_categ();
    // Constructor
    Classement_manche_categ(int idConcurrent, int idManche, QString nomManche, int numConcurrent, std::chrono::milliseconds totalChrono,int id_categorie,QString nom_categorie,int points);

    // Getter methods
    std::chrono::milliseconds getTotalChrono() const { return total_chrono; }
    int getIdConcurrent() const { return id_concurrent; }
    int getIdManche() const { return id_manche; }
    QString getNomManche() const { return nom_manche; }
    int getNumConcurrent() const { return num_concurrent; }
    int getPoints() const {return points;}
    int getIdCategorie() const { return id_categorie; }
    QString getNomCategorie() const {return nom_categorie;}

    // Setter methods
    void setIdConcurrent(int idConcurrent) { id_concurrent = idConcurrent; }
    void setIdManche(int idManche) { id_manche = idManche; }
    void setNomManche(QString nomManche) { nom_manche = nomManche; }
    void setNumConcurrent(int numConcurrent) { num_concurrent = numConcurrent; }
    void setTotalChrono(std::chrono::milliseconds totalChrono) { total_chrono = totalChrono; }
    void setPoints(int pt){points=pt;}
    void setIdCategorie(const int id) { id_categorie = id; }
    void setNomCategorie(const QString c){nom_categorie = c;}

    QVector<Classement_manche_categ> fetchData(QSqlQuery qry);
    void displayClassement(QTableWidget* tableWidget,const QVector<Classement_manche_categ>& classe,const MainWindow& mw);
    std::chrono::milliseconds parseTimeString(const std::string& timeStr);
    QString timePointAsString(std::chrono::milliseconds chrono);


private:
    std::chrono::milliseconds total_chrono ;
    int id_concurrent ;
    int id_manche ;
    QString nom_manche;
    int num_concurrent;
    int id_categorie;
    QString nom_categorie;
    int points;
};

#endif // CLASSEMENT_MANCHE_CATEG_H
