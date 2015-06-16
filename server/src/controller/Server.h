//
// Created by NiL on 15/6/15.
//

#ifndef V3_SERVER_H
#define V3_SERVER_H

#include <QCoreApplication>
#include <src/model/Connection.h>

#include "../service/ServerService.h"

class Server: QObject {
    Q_OBJECT
public:
    Server(QCoreApplication *app);

private slots:
    void responseHandler(QJsonObject json, qintptr id);

private:
    ServerService &serverService = ServerService::getInstance();
    Connection connection;

    const int stage_size = 5;

    void registerHandler(QJsonObject data, qintptr id);
    void loginHandler(QJsonObject data, qintptr id);
    void gameStartHandler(QJsonObject data, qintptr id);
    void gameOverHandler(QJsonObject data, qintptr id);

    void boardHandler(QJsonObject data, qintptr id);
    void addQuestionHandler(QJsonObject data, qintptr id);

    void importQuestion(QString filename);

};


#endif //V3_SERVER_H
