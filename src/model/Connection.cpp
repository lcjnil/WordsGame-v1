//
// Created by NiL on 15/4/8.
//

#include "Connection.h"

#include <QDebug>
#include <QFileInfo>
#include <QSqlError>

Connection::Connection(QString t_dbPath) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    dbPath = t_dbPath;

    if (isDbExist()) {
        db.setDatabaseName(dbPath);
    } else {
        //TODO: add for no db
        qDebug() << "Connection: no such db";
        db.setDatabaseName(dbPath);
    }

    if (!db.open()) {
        qDebug() << db.lastError();
        qDebug() << "Connection: open database failed";
    }
    qDebug() << "Connection: open database success";
}

bool Connection::isDbExist() {
    QFileInfo dbFile(dbPath);
    if (dbFile.exists()) {
        return true;
    } else {
        return false;
    }
}

bool Connection::isTableExist(QString table) {
    return db.tables().contains(table);
}
