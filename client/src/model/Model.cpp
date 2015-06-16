//
// Created by NiL on 15/6/16.
//

#include "Model.h"


Model::Model(QJsonObject json) {
    data = json;
}

void Model::set(QString key, int value) {
    data[key] = value;
}

void Model::set(QString key, QString value) {
    data[key] = value;
}

QJsonValue Model::get(QString key) {
    return data[key];
}