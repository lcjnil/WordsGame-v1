#ifndef GAME_H
#define GAME_H

#include <vector>

#include "../model/Player.h"
#include "../model/Question.h"

class Game
{
public:
    Game(Player *player);
    void start();

private:
    Player *player;
    vector<Question> list;
    //关卡需要的次数
    int size = 5;
    int stage_time = 3000;

    void initQuestion();
    bool answerQuestion(int i);
    int getExp(int time);

    //Helper method
    void printInfo();
};

#endif // GAME_H
