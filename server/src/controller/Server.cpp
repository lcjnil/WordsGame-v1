//
// Created by NiL on 15/6/15.
//

#include "Server.h"
#include "../model/Connection.h"
#include "../model/User.h"
#include "../model/Player.h"
#include "../model/Referee.h"
#include "../model/Question.h"
#include "../util/Console.h"

#include <QJsonArray>
#include <QDir>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

using namespace Console;

Server::Server(QCoreApplication *app) {
    QString db_path = app->applicationDirPath() + QDir::separator() + "data.db";
    connection = Connection(db_path);
    User::setConnection(&connection);
    Question::setConnection(&connection);

    cls();
    print("Enter CVS file to import questions\n:", 2);
    QString fileName = scin.readLine();
    if (fileName != "") {
        importQuestion(fileName);
    }

    // initial serverService
    serverService.start();
    connect(&serverService, SIGNAL(receiveJSON(QJsonObject, qintptr)), this, SLOT(responseHandler(QJsonObject, qintptr)));
    connect(&serverService, SIGNAL(addRoom(int, int)), this, SLOT(addRoom(int, int)));
}

void Server::responseHandler(QJsonObject json, qintptr id) {
    QString type = json["type"].toString();
    if (type == "register") {
        registerHandler(json, id);
    } else if (type == "login") {
        loginHandler(json, id);
    } else if (type == "game_start") {
        gameStartHandler(json, id);
    } else if (type == "game_over") {
        gameOverHandler(json, id);
    } else if (type == "board") {
        boardHandler(json, id);
    } else if (type == "add_question") {
        addQuestionHandler(json, id);
    }
}

void Server::registerHandler(QJsonObject data, qintptr id) {
    QString username = data["username"].toString(),
            password = data["password"].toString(),
            type = data["user_type"].toString();

    bool flag = User::reg(username, password, type);
    QJsonObject message{
            {"type", "register"},
            {"status", flag}
    };
    serverService.send(message, id);
}

void Server::loginHandler(QJsonObject data, qintptr id) {
    QString username = data["username"].toString(),
            password = data["password"].toString();

    QString type = User::auth(username, password);

    qDebug() << type;
    User * user;
    QJsonObject message;
    message["type"] = "login";
    message["status"] = true;

    if (type == "player") {
        user = new Player();
        *user = Player::findByName(username);
        Player *player =  dynamic_cast<Player *>(user);

        message["user_type"] = "player";
        message["name"] = player->getName();
        message["level"] = player->getLevel();
        message["stage_obtained"] = player->getStage();
        message["exp"] = player->getExp();
        message["max_exp"] = Player::maxExp;
        message["userId"] = player->get("userId").toInt();

    } else if (type == "referee") {
        user = new Referee();
        *user = Player::findByName(username);
        Referee *referee = dynamic_cast<Referee *>(user);

        message["user_type"] = "referee";
        message["name"] = referee->getName();
        message["level"] = referee->getLevel();
        message["exp"] = referee->getExp();
        message["userId"] = referee->get("userId").toInt();
    } else {
        message["status"] = false;
    }


    serverService.send(message, id);
}

void Server::gameStartHandler(QJsonObject data, qintptr id) {
    int userId = data["userId"].toInt();
    int roomId = data["room"].toInt();

    User user = User::findById(userId);

    if (serverService.addToRoom(roomId, id)) {
        roomLevel[roomId] += user.getLevel();
    };
}

void Server::addRoom(int roomId, int size) {
    if (size != 2) return;


    // Game start!!!!
    vector<Question> list = Question::getAllQuestion();
    std::random_shuffle(list.begin(), list.end(), [](int i){return clock() % i;});

    QJsonObject message;
    message["type"] = "game_start";

    QJsonArray questions;
    for (int i = 0; i < stage_size; i++) {
        questions.push_back(QJsonObject{
                {"word", list[i].getWord()},
                {"level", list[i].getLevel()}
        });
    }

    int stage_time = 3000 + roomLevel[roomId]/2 * 300;
    if (stage_time <= 1000) {
        stage_time = 1000;
    }
    message["questions"] = questions;
    message["stage_time"] = stage_time;

    serverService.multicast(roomId, message);

    roomLevel[roomId] = 0; //reset
}

/*
 * type: game_over
 * userId: player's id
 * exp: new exp
 * level: new level
 * stage_obatined: new..
 */
void Server::gameOverHandler(QJsonObject data, qintptr id) {
    User user = User::findById(data["userId"].toInt());
    user.set("exp", data["exp"].toInt());
    user.set("level", data["level"].toInt());
    user.set("stage_obtained", data["stage_obtained"].toInt());

    user.update();

    serverService.removeFromRoom(id);
}


/*
 * receive:
 *
 * type: board
 * data_type: 'player' 'referee' 'question'
 * order_by
 *
 * send:
 *
 * type: board
 * data_type:
 * order_by
 * users; [] all field is string
 */
void Server::boardHandler(QJsonObject data, qintptr id) {
    QString type = data["data_type"].toString(),
            order_by = data["order_by"].toString();

    vector<User> users =  User::findAllWithOrder(order_by);

    QJsonArray array;

    for (auto user: users) {
        if (user.getType() != type) continue;
        array.push_back(QJsonObject{
                {"name", user.get("name")},
                {"level", user.get("level")},
                {"exp", user.get("exp")},
                {"stage_obtained", user.get("stage_obtained")},
                {"userId", QString::number(user.getId())},
                {"words_count", user.get("words_count")}
        });
    }

    serverService.send(QJsonObject{
            {"type", "board"},
            {"data_type", type},
            {"users", array},
            {"order_by", order_by}
    }, id);
}

/*
 * type: add_question
 * word:
 * level:
 * userId:
 *
 * type: add_question
 * status: bool
 */
void Server::addQuestionHandler(QJsonObject data, qintptr id) {
    QString word = data["word"].toString();
    int level = data["level"].toInt(),
        userId = data["userId"].toInt();

    bool flag = Question::addQuestion(word, level, userId);

    User user = User::findById(userId);
    int cnt = user.get("words_count").toInt() + 1;
    user.set("words_count", cnt);
    user.update();

    serverService.send(QJsonObject{
            {"type", "add_question"},
            {"status", flag}
    }, id);
}

void Server::importQuestion(QString filename) {
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        warn("File Not Exist!!!!!");
    }

    QString word, level;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        word = line.split(',').at(0);
        level = line.split(',').at(1);

        if (!Question::addQuestion(word, level.toInt(), 0)) {
            print(word + " already exists!\n");
        }
    }

    print("Import Finished!\n", RED);
    waitKey();
}