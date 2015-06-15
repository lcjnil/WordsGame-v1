//
// Created by NiL on 15/6/3.
//

#ifndef WORDSGAME_REFEREE_H
#define WORDSGAME_REFEREE_H

#include "User.h"

class Referee : public User {
public:
    QString getType() {
        return "referee";
    }

    bool addQuestion(QString word, int level);

private:
    static int MAXEXP;
};


#endif //WORDSGAME_REFEREE_H
