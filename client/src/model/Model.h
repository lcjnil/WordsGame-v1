//
// Created by NiL on 15/6/16.
//

#ifndef V3_MODEL_H
#define V3_MODEL_H


#include <QJsonObject>
#include <QVariant>

class Model {

public:
    Model(QJsonObject json);
    void set(QString key, QString value);
    void set(QString key, int value);

    QJsonValue get(QString key);

protected:
    QJsonObject data;
};


#endif //V3_MODEL_H
