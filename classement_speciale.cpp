#include "Classement_speciale.h" // Include the header file where your class is declared
#include "mainwindow.h"
#include <chrono>
#include <QString>
#include <QTableWidget>
#include <iomanip>
#include <QDateTime>
#include <QDateTime>
Classement_speciale::Classement_speciale(const int id_temps)
    : id_temps(id_temps) {
    // Initialize other members as needed
    // For example:// Set to current time or another default value
    id_speciale = 0; // Or another default value
    id_concurrent = 0; // Or another default value
    id_categorie = 0; // Or another default value
    nom_speciale = ""; // Or another default value
    longeur_km = 0.0; // Or another default value
    num_concurrent = 0; // Or another default value
}


Classement_speciale::Classement_speciale(const int id_temps, const std::chrono::milliseconds& chrono,
                                         const int id_speciale, const int id_concurrent, const int id_categorie,
                                         const QString& nom_speciale, const double longeur_km, const int num_concurrent,const QString nom_categorie)
    : id_temps(id_temps), chrono(chrono), id_speciale(id_speciale), id_concurrent(id_concurrent),
    id_categorie(id_categorie), nom_speciale(nom_speciale), longeur_km(longeur_km), num_concurrent(num_concurrent),nom_categorie(nom_categorie) {
    // Constructor body can be left empty if no additional initialization is needed
}

// Constructor definition for Classement_speciale with no parameters
Classement_speciale::Classement_speciale() {
    // Initialize member variables to their default values
    id_temps = 0; // Assuming 0 is a sensible default for an ID// Current time
    id_speciale = 0;
    id_concurrent = 0;
    id_categorie = 0;
    nom_speciale = ""; // Empty string as a default
    longeur_km = 0.0; // Assuming 0.0 is a sensible default for length
    num_concurrent = 0; // Assuming 0 is a sensible default for a count
}
QVector<Classement_speciale> Classement_speciale::fetchData(QSqlQuery qry) {
    QVector<Classement_speciale> classement;
    while (qry.next()) {
        int id_temps = qry.value(0).toInt();
        std::string stringy = qry.value(1).toString().toStdString();
        std::chrono::milliseconds chrono = parseTimeString(stringy);
        int id_speciale = qry.value(2).toInt();
        int id_concurrent = qry.value(3).toInt();
        int id_categorie = qry.value(4).toInt();
        QString nom_speciale = qry.value(5).toString();
        double longeur_km = qry.value(6).toDouble();
        int num_concurrent = qry.value(7).toInt();
        QString nom_categorie = qry.value(8).toString();
        classement.append(Classement_speciale(id_temps,chrono,id_speciale,id_concurrent,id_categorie,nom_speciale,longeur_km,num_concurrent,nom_categorie));
    }
    return classement;
}
std::chrono::milliseconds Classement_speciale::parseTimeString(const std::string& timeStr) {
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
QString Classement_speciale::timePointAsString(std::chrono::milliseconds ms) {
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

void Classement_speciale::displayClassement(QTableWidget* tableWidget,const QVector<Classement_speciale>& classe,const MainWindow& mw){
    tableWidget->clear();
    tableWidget->setFixedSize(QSize(600, 600)); // Sets the widget's size to 300x200 pixels
    tableWidget->setRowCount(classe.size());
    tableWidget->setColumnCount(5); // Assuming 3 columns: Name, Grade, Attendance


    // Manually set the column headers based on class attributes
    QStringList headers;
    headers << "chrono" << "ES" << "longeur_km" << "num_concurrent" << "nom_categorie";
    tableWidget->setHorizontalHeaderLabels(headers);

    // Populate the table with data
    for (int row = 0; row < classe.size(); ++row) {
        Classement_speciale classy = classe[row];

        QTableWidgetItem *chrono = new QTableWidgetItem(timePointAsString(classy.getChrono()));
        QTableWidgetItem *nom_speciale = new QTableWidgetItem(classy.getNomSpeciale());
        QTableWidgetItem *longeur_km = new QTableWidgetItem(QString::number(classy.getLongeurKm()));
        QTableWidgetItem *num_concurrent = new QTableWidgetItem(QString::number(classy.getNumConcurrent()));
        QTableWidgetItem *nom_categorie = new QTableWidgetItem(classy.getNomCategorie());

        tableWidget->setItem(row, 0, chrono);
        tableWidget->setItem(row, 1, nom_speciale);
        tableWidget->setItem(row, 2, longeur_km);
        tableWidget->setItem(row, 3, num_concurrent);
        tableWidget->setItem(row, 4, nom_categorie);
    }

}
