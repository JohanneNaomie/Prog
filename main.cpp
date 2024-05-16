
#include <Classement_manche.h>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVectorIterator>
#include "classement_saison.h"
#include "classement_speciale.cpp"
#include "mainwindow.h"
#include "qapplication.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mw;

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("172.30.40.14");
    db.setDatabaseName("rallye");
    db.setUserName("postgres");
    db.setPassword("mimimavo");
    db.open();

    if (!db.open()) {
        qDebug() << "Error opening database:";
        return 1;
    }
    mw.show();

    return app.exec();
}
