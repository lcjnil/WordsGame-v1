#include "app.h"
#include "../util/Console.h"

#include <QDebug>
#include <QString>
#include <QFile>
#include <QStringList>

using namespace Console;

App::App() {
    cls();
    print("Please input IP address (blank for localhost): ", 2, 4, BLACK);

    QString ip = scin.readLine();
    clientService.link(ip);

    connect(&clientService, SIGNAL(receiveJSON(QJsonObject)), this, SLOT(responseHandler(QJsonObject)));
    connect(&game, SIGNAL(finish(QString)), this, SLOT(subControllerHandler(QString)));
    connect(&board, SIGNAL(finish(QString)), this, SLOT(subControllerHandler(QString)));

}

void App::start() {
    cls();
    print("Welcome To Words Game\n\n", RED);

    bool quit = false;

    printCenter("Words Game ver.2 By LCJ", 1, BLUE);
    print("Please select your ", 4, 4);
    print("ACTION: ", RED);

    print("1. Register", 4, 5);
    print("2. Login", 4, 6);
    print("3. Import Question", 4, 7);
    print("Q. Quit", 4, 8);

    locateCursor(4, 9);

    switch (getch()) {
        case '1':
            registerController();
            break;
        case '2':
            loginController();
            break;
        case '3':
            //importController();
            break;
        case 'q':
            break;
        default:
            break;
    }
}

void App::responseHandler(QJsonObject json) {
    QString type = json["type"].toString();
    if (type == "register") {
        registerHandler(json);
    } else if (type == "login") {
        loginHandler(json);
    } else if (type == "add_question") {
        addWordHandler(json);
    }
}

void App::registerController() {
    cls();
    printCenter("Register", 2, RED);
    QString username, password, type;


    print("Username: ", 4, 4);
    scin>>username;

    print("Password:  ", 4, 6);
    password = getPassword();

    print("Are you ", 4, 8);print("1. Player ", BLUE);print("2. Referee :", RED);

    switch (getch()) {
        case '1':
            type = "player";
            break;
        case '2':
        default:
            type = "referee";
            break;
    }

    QJsonObject json {
        {"type", "register"},
        {"username", username},
        {"password", password},
        {"user_type", type}
    };
    clientService.sendJSON(json);
}

void App::registerHandler(QJsonObject json) {
    if (json["status"].toBool()) {
        info("Register Success!!!");
    } else {
        warn("Register Failed");
    }

    start();
}

void App::loginController() {
    cls();

    printCenter("Login", 2, RED);

    QString username, password, type;
    print("Username: ", 4, 4);
    scin>>username;

    print("Password:  ", 4, 6);
    password = getPassword();

    clientService.sendJSON(QJsonObject{
            {"type", "login"},
            {"username", username},
            {"password", password}
    });
}

void App::loginHandler(QJsonObject json) {
    bool flag = json["status"].toBool();
    if (flag) {
        info("Login Success!!");
        user = json;

        if (user["user_type"] == "player") {
            playerController();
        } else {
            refereeController();
        }
    } else {
        warn("Login Failed!");
        start();
    }
}


void App::playerController() {
    cls();
    print("Player: ", 4, 0); print(user["name"].toString(), GREEN);

    print("Please select your ", 4, 4);
    print("ACTION: ", RED);

    print("1. Play GAME!!!", 4, 5, RED);
    print("2. View All Players", 4, 6, RED);
    print("Q. Quit", 4, 7);


    switch (getch()) {
        case '1':
            game.start(new Player(user));
            break;
        case '2':
            board.showPlayer();
            break;
        case 'q':
            start();
            break;
        default:
            playerController();
            break;
    }
}

void App::subControllerHandler(QString type) {
    if (type == "game") {
        playerController();
    } else if (type == "board_player") {
        playerController();
    } else if (type == "board_referee") {
        refereeController();
    }
}



void App::refereeController() {
    cls();
    print("Refree: ", 4, 0); print(user["name"].toString(), GREEN);

    print("Please select your ", 4, 4);
    print("ACTION: ", RED);

    print("1. Add a word", 4, 5);
    print("2. View all referee", 4, 6);
    print("Q. Quit", 4, 7);


    switch (getch()) {
        case '1':
            addWordController();
            break;
        case '2':
            board.showReferee();
            break;
        case 'q':
            start();
            break;
        default:
            refereeController();
    }
}

void App::addWordController() {
    QString word; int level;

    cls();
    print("Word: ", 4, 4); scin>>word;
    print("Level: ", 4, 6); scin>>level;

    clientService.sendJSON(QJsonObject{
            {"type", "add_question"},
            {"word", word},
            {"level", level},
            {"userId", user["userId"].toInt()}
    });
}

void App::addWordHandler(QJsonObject data) {
    if (data["status"].toBool()) {
        info("Add Word Success!!!");
    } else {
        warn("Word Already Exists");
    }

    refereeController();
}
