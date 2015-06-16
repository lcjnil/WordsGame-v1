//
// Created by NiL on 15/6/16.
//

#ifndef V3_QUESTION_H
#define V3_QUESTION_H

#include "Model.h"

class Question: public Model {

public:
    Question(QJsonObject json): Model(json){};

    QString getWord() {
        return get("word").toString();
    }

    int getLevel() {
        return get("level").toInt();
    }

};


#endif //V3_QUESTION_H
