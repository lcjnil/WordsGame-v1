#ifndef APP_H
#define APP_H

#include <QString>
#include <QTextStream>
#include <QJsonObject>

#include "../service/ClientService.h"
#include "../controller/game.h"
#include "../controller/board.h"

class App: QObject {

Q_OBJECT

public:
    App();
    void start();

private slots:
    void responseHandler(QJsonObject json);
    void subControllerHandler(QString type);

private:
    ClientService &clientService = ClientService::getInstance();
    QJsonObject user;

    Game game;
    Board board;


    void registerController();
    void registerHandler(QJsonObject json);

    void loginController();
    void loginHandler(QJsonObject json);

    void playerController();

    void refereeController();
    void addWordController();
    void addWordHandler(QJsonObject json);
};

#endif // APP_H
