#include "classement_manche.h"
#include "mainwindow.h"
#include <chrono>
#include <QString>
#include <QTableWidget>
#include <iomanip>
#include <QDateTime>
#include <QDateTime>

Classement_manche::Classement_manche() {}

Classement_manche::Classement_manche(int idConcurrent, int idManche, QString nomManche, int numConcurrent, std::chrono::milliseconds totalChrono,int id_categorie,QString nom_categorie,int points)
    : total_chrono(totalChrono), id_concurrent(idConcurrent), id_manche(idManche), nom_manche(nomManche), num_concurrent(numConcurrent),id_categorie(id_categorie),nom_categorie(nom_categorie),points(points) {};

QVector<Classement_manche> Classement_manche::fetchData(QSqlQuery qry) {
    QVector<Classement_manche> classement;
    while (qry.next()) {
        std::string stringy = qry.value(0).toString().toStdString();
        std::chrono::milliseconds chrono = parseTimeString(stringy);
        int id_manche = qry.value(2).toInt();
        int id_concurrent = qry.value(1).toInt();
        int id_categorie = qry.value(3).toInt();
        QString nom_manche = qry.value(4).toString();
        QString nom_categorie = qry.value(5).toString();
        int num_concurrent = qry.value(6).toInt();
        int points = qry.value(7).toInt();
        classement.append(Classement_manche(id_concurrent,id_manche,nom_manche,num_concurrent,chrono,id_categorie,nom_categorie,points));
    }
    return classement;
}
std::chrono::milliseconds Classement_manche::parseTimeString(const std::string& timeStr) {
    std::stringstream ss(timeStr);
    std::string hoursStr, minsStr, secsStr, fracSecsStr;

    getline(ss, hoursStr, ':');
    getline(ss, minsStr, ':');
    getline(ss, secsStr, '.');
    getline(ss, fracSecsStr);

    int hours = std::stoi(hoursStr);
    int mins = std::stoi(minsStr);
    int secs = std::stoi(secsStr);
    int fracSecs = std::stoi(fracSecsStr);

    // Convert everything to milliseconds
    int totalMillisecs = static_cast<int>(hours * 3600000 + mins * 60000 + secs * 1000+fracSecs);

    return std::chrono::milliseconds(totalMillisecs);
}
QString Classement_manche::timePointAsString(std::chrono::milliseconds ms) {
    using namespace std::chrono;
    auto secs = duration_cast<seconds>(ms);
    ms -= duration_cast<milliseconds>(secs);
    auto mins = duration_cast<minutes>(secs);
    secs -= duration_cast<seconds>(mins);
    auto hour = duration_cast<hours>(mins);
    mins -= duration_cast<minutes>(hour);

    std::stringstream ss;
    ss << std::setw(2) << std::setfill('0') << hour.count() << ":"
       << std::setw(2) << std::setfill('0') << mins.count() << ":"
       << std::setw(2) << std::setfill('0') << secs.count() << ".";
    ss << std::setw(3) << std::setfill('0') << ms.count(); // Add milliseconds
    return QString::fromStdString(ss.str());
}
void Classement_manche::displayClassement(QTableWidget* tableWidget,const QVector<Classement_manche>& classe,const MainWindow& mw){
    tableWidget->clear();
    tableWidget->setFixedSize(QSize(600, 600)); // Sets the widget's size to 300x200 pixels
    tableWidget->setRowCount(classe.size());
    tableWidget->setColumnCount(5); // Sets the table to have 3 columns

    // Manually set the column headers based on class attributes
    QStringList headers;
    headers << "chrono" << "nom_manche" << "nom_categorie" << "num_concurrent" << "points";
    tableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table with data
    for (int row = 0; row < classe.size(); ++row) {
        Classement_manche classy = classe[row];

        QTableWidgetItem *chrono = new QTableWidgetItem(timePointAsString(classy.getTotalChrono()));
        QTableWidgetItem *nom_manche = new QTableWidgetItem(classy.getNomManche());
        QTableWidgetItem *categ = new QTableWidgetItem(classy.getNomCategorie());
        QTableWidgetItem *num_concurrent = new QTableWidgetItem(QString::number(classy.getNumConcurrent()));
        QTableWidgetItem *pts = new QTableWidgetItem(QString::number(classy.getPoints()));

        tableWidget->setItem(row, 0, chrono);
        tableWidget->setItem(row, 1, nom_manche);
        tableWidget->setItem(row, 2, categ);
        tableWidget->setItem(row, 3, num_concurrent);
        tableWidget->setItem(row, 4, pts);
    }
}
