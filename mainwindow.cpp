#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "classement_saison.h"
#include "classement_manche.h"
#include "classement_speciale.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query2;
    QString sais = ui->saison->text();
    query2.prepare("SELECT * FROM classement_saison where année =:sais and id_categorie=5");
    query2.bindValue(":sais",sais);
    Classement_saison spec3;
    if(query2.exec()){
        QTableWidget* tab = ui->tableWidget;
        QVector<Classement_saison> classe3 = spec3.fetchData(query2);
        QVectorIterator<Classement_saison> itNumbers3(classe3);
        spec3.displayClassement(tab,classe3,this);
    }
    else{
        qDebug() << "Query not executed";
    }

    query2.prepare("SELECT * FROM classement_saison where année =:sais and id_categorie!=5");
    query2.bindValue(":sais",sais);
    if(query2.exec()){
        QTableWidget* tab = ui->tableWidget_5;
        QVector<Classement_saison> classe3 = spec3.fetchData(query2);
        QVectorIterator<Classement_saison> itNumbers3(classe3);
        spec3.displayClassement(tab,classe3,this);
    }
    else{
        qDebug() << "Query not executed";
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery query2;
    QString man = ui->manche->text();
    query2.prepare("SELECT * FROM classement_categ_manche where id_manche=:manche and id_categorie=5");
    query2.bindValue(":manche",man);
    Classement_manche spec3;
    if(query2.exec()){
        QTableWidget* tab = ui->tableWidget_2;
        QVector<Classement_manche> classe3 = spec3.fetchData(query2);
        QVectorIterator<Classement_manche> itNumbers3(classe3);
        spec3.displayClassement(tab,classe3,this);
    }
    else{
        qDebug() << "Query not executed";
    }

    query2.prepare("SELECT * FROM classement_categ_manche where id_manche=:manche and id_categorie!=5 order by id_categorie,total_chrono asc");
    query2.bindValue(":manche",man);
    Classement_manche spec4;
    if(query2.exec()){
        QTableWidget* tab = ui->tableWidget_4;
        QVector<Classement_manche> classe3 = spec4.fetchData(query2);
        QVectorIterator<Classement_manche> itNumbers3(classe3);
        spec3.displayClassement(tab,classe3,this);
    }
    else{
        qDebug() << "Query not executed";
    }

}


void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery query2;
    QString speciale = ui->speciale->text();
    query2.prepare("SELECT * FROM aff_tss where id_speciale=:spec order by id_categorie,chrono asc");
    query2.bindValue(":spec",speciale);
    Classement_speciale spec3;
    if(query2.exec()){
        QTableWidget* tab = ui->tableWidget_3;
        QVector<Classement_speciale> classe3 = spec3.fetchData(query2);
        QVectorIterator<Classement_speciale> itNumbers3(classe3);
        spec3.displayClassement(tab,classe3,this);
    }
    else{
        qDebug() << "Query not executed";
    }
}

