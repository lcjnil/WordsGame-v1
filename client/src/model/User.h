//
// Created by NiL on 15/6/16.
//

#ifndef V3_USER_H
#define V3_USER_H

#include <QJsonObject>
#include "Model.h"

class User: public Model {

public:
    User(QJsonObject json): Model(json){};

    QString getName() {
        return get("name").toString();
    }

    QString getType() {
        return get("userType").toString();
    }

    int getLevel() {
        return get("level").toInt();
    }

    int getExp() {
        return get("exp").toInt();
    }

    int getId() {
        return data["userId"].toInt();
    }
};


#endif //V3_USER_H
