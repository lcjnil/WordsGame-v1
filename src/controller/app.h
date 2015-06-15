#ifndef APP_H
#define APP_H

#include <QString>
#include <QTextStream>

#include "game.h"
#include "../model/Referee.h"
#include "../model/Player.h"
#include "board.h"

class App {
public:
    void start();

private:
    Player * player;
    Referee * referee;

    void registerController();
    void loginController();

    // 出题者主循环
    void refereeController();
    void addWordController();
    void listWordController();

    // 答题者主循环
    void playerController();

    void importController();

    Game *game;
    Board *board = new Board;
};

#endif // APP_H
