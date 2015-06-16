//
// Created by NiL on 15/4/8.
//

#ifndef _TESTPROJECT_USER_H_
#define _TESTPROJECT_USER_H_

#include "Model.h"

#include <QMap>
#include <QString>
#include <vector>

class User: public Model<User> {

public:
    static QString auth(QString name, QString password);
    static User findByName(QString name);
    static bool reg(QString name, QString password, QString type);

    virtual QString getType() {
        return get("type");
    };

    QString getName() {
        return get("name");
    }

    int getExp() {
        return get("exp").toInt();
    }

    int getLevel() {
        return get("level").toInt();
    }
};


#endif //_TESTPROJECT_USER_H_
