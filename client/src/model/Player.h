//
// Created by NiL on 15/6/16.
//

#ifndef V3_PLAYER_H
#define V3_PLAYER_H

#include <QDebug>

#include "User.h"

class Player: public User {

public:
    Player(QJsonObject json): User(json){
        maxExp = data["max_exp"].toInt();
    };

    int maxExp = 10;

    int getStage() {
        return data["stage_obtained"].toInt();
    }

    bool obtainExp(int exp) {
        int t_exp = getExp() + exp;
        int t_level = getLevel();
        bool flag = false;

        while (t_exp >= maxExp) {
            t_exp -= maxExp;
            t_level++;
            flag = true;
        }


        set("exp", t_exp);
        set("level", t_level);

        return flag;
    }

    void addStage() {
        int stage = getStage();
        set("stage_obtained", stage+1);
    }

};


#endif //V3_PLAYER_H
