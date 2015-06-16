#ifndef GAME_H
#define GAME_H

#include <QList>

#include "../model/Player.h"
#include "../model/Question.h"
#include "../service/ClientService.h"


class Game : public QObject{
    Q_OBJECT
public:
    Game();
    void start(Player *player);
    void gameStartHandler();

signals:
    void finish(QString type);
private:
    Player *player;
    QList<Question> list;
    ClientService &clientService = ClientService::getInstance();

    //关卡需要的次数
    int size = 5;
    int stage_time = 3000;

    bool answerQuestion(int i);
    int getExp(int time);

    //Helper method
    void printInfo();


private slots:
    void responseHandler(QJsonObject json);
};

#endif // GAME_H
