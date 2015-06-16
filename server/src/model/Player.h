#ifndef PLAYER_H
#define PLAYER_H

#include "User.h"

#include <vector>
using namespace std;


class Player : public User {
public:
    static int maxExp;

    QString getType() {
        return "player";
    }

    int getStage() {
        return get("stage_obtained").toInt();
    }

    // 返回是否升级
    bool obtainExp(int exp) {
        int t_exp = getExp() + exp;
        int t_level = getLevel();
        bool flag = false;

        while (t_exp >= maxExp) {
            t_exp -= maxExp;
            t_level++;
            flag = true;
        }

        set("exp", QString::number(t_exp));
        set("level", QString::number(t_level));

        update();

        return flag;
    }

    void addStage() {
        int stage = get("stage_obtained").toInt();
        set("stage_obtained", stage+1);
        update();
    }
};

#endif // PLAYER_H
