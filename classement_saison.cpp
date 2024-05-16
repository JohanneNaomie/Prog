#include "classement_saison.h"
#include "mainwindow.h"
#include <chrono>
#include <QString>
#include <QTableWidget>
#include <iomanip>
#include <QDateTime>
#include <QDateTime>

Classement_saison::Classement_saison() {}

Classement_saison::Classement_saison(int idConcurrent, int idSaison, int annee, int numConcurrent, std::chrono::milliseconds totalChrono,int id_categorie,QString nom_categorie,int winsCount,int points)
    : total_chrono(totalChrono), id_concurrent(idConcurrent), id_saison(idSaison),annee(annee), num_concurrent(numConcurrent),id_categorie(id_categorie),nom_categorie(nom_categorie),wins_count(winsCount),points(points) {};

QVector<Classement_saison> Classement_saison::fetchData(QSqlQuery qry) {
    QVector<Classement_saison> classement;
    while (qry.next()) {
        std::string stringy = qry.value(0).toString().toStdString();
        std::chrono::milliseconds chrono = parseTimeString(stringy);
        int id_saison = 0;
        int id_concurrent = qry.value(1).toInt();
        int id_categorie = qry.value(2).toInt();
        int wins = qry.value(4).toInt();
        int annee = qry.value(5).toInt();
        QString nom_categorie = "";
        int num_concurrent = 0;
        int points = qry.value(3).toInt();
        classement.append(Classement_saison(id_concurrent,id_saison,annee,num_concurrent,chrono,id_categorie,nom_categorie,wins,points));
    }
    return classement;
}
std::chrono::milliseconds Classement_saison::parseTimeString(const std::string& timeStr) {
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
    int totalMillisecs = static_cast<int>(hours * 3600000 + mins * 60000 + secs * 1000 + fracSecs);

    return std::chrono::milliseconds(totalMillisecs);
}
QString Classement_saison::timePointAsString(std::chrono::milliseconds ms) {
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
void Classement_saison::displayClassement(QTableWidget* tableWidget,const QVector<Classement_saison>& classe,const MainWindow& mw){
    tableWidget->clear();
    tableWidget->setFixedSize(QSize(600, 600));
    tableWidget->setRowCount(classe.size());
    tableWidget->setColumnCount(6);

    QStringList headers;
    headers << "chrono" << "année" << "id_categorie" << "id_concurrent" << "victoires" << "points";
    tableWidget->setHorizontalHeaderLabels(headers);

    for (int row = 0; row < classe.size(); ++row) {
        Classement_saison classy = classe[row];

        QTableWidgetItem *chrono = new QTableWidgetItem(timePointAsString(classy.getTotalChrono()));
        QTableWidgetItem *annee = new QTableWidgetItem(QString::number(classy.getAnnee()));
        QTableWidgetItem *categ = new QTableWidgetItem(QString::number(classy.getIdCategorie()));
        QTableWidgetItem *num_concurrent = new QTableWidgetItem(QString::number(classy.getIdConcurrent()));
        QTableWidgetItem *vics = new QTableWidgetItem(QString::number(classy.getWinsCount()));
        QTableWidgetItem *pts = new QTableWidgetItem(QString::number(classy.getPoints()));

        tableWidget->setItem(row, 0, chrono);
        tableWidget->setItem(row, 1, annee);
        tableWidget->setItem(row, 2, categ);
        tableWidget->setItem(row, 3, num_concurrent);
        tableWidget->setItem(row, 4, vics);
        tableWidget->setItem(row, 5, pts);
    }

}
