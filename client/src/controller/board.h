//
// Created by NiL on 15/6/14.
//

#ifndef WORDSGAME_BOARD_H
#define WORDSGAME_BOARD_H


#include <QString>
#include <vector>
#include <QObject>
#include <src/service/ClientService.h>

class Board: public QObject {

    Q_OBJECT

public:
    Board();
    void showPlayer();
    void showReferee();

signals:
    void finish(QString);

private slots:
    void responseHandler(QJsonObject data);

private:
    void listPlayer(QString order);
    void listReferee(QString order);
    static std::vector<QString> PlayerKeys;
    static std::vector<QString> RefereeKeys;

    void boardHandler(QJsonObject data);

    ClientService &clientService = ClientService::getInstance();
};


#endif //WORDSGAME_BOARD_H
