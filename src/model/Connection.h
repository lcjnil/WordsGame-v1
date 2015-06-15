//
// Created by NiL on 15/4/8.
//

#ifndef _TESTPROJECT_CONNECTION_H_
#define _TESTPROJECT_CONNECTION_H_

#include <QSqlDatabase>

class Connection {
public:
    Connection(QString t_dbPath);
    bool isTableExist(QString table);
    QSqlDatabase db;

private:
    bool isDbExist();
    QString dbPath;
};


#endif //_TESTPROJECT_CONNECTION_H_
