#include "qsqlquery.h"
#include <QSqlDatabase>
#include <qstring.h>

class Connect {
public:

    ~Connect() {
        disconnect();
    }

    QSqlDatabase* connect() {
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("172.30.40.14");
        db.setDatabaseName("rallye");
        db.setUserName("postgres");
        db.setPassword("mimimavo");
        return &db;
    }

    void disconnect() {
        QSqlDatabase::removeDatabase("QPSQL");
    }

    template<typename T>
    T selectSingle(const QString& query, const QStringList& params = {}) {
        QSqlQuery queryObj;
        if (!queryObj.prepare(query)) {
            qDebug() << "Error preparing query:";
            return T(); // Return default value or throw exception
        }
        foreach (const QString& param, params) {
            queryObj.addBindValue(param);
        }
        if (!queryObj.exec()) {
            qDebug() << "Error executing query:";
            return T(); // Return default value or throw exception
        }
        queryObj.next();
        return queryObj.value(0).value<T>();
    }

};
