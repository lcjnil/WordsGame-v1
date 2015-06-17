#include "game.h"
#include "../util/Console.h"

#include <algorithm>
#include <ctime>
#include <QTime>

#include <QJsonArray>

using namespace Console;
Game::Game() {
    connect(&clientService, SIGNAL(receiveJSON(QJsonObject)), this, SLOT(responseHandler(QJsonObject)));
}

void Game::start(Player *p) {
    player = p;

    printInfo();

    printCenter("Welcome to GAME!!!", 2, 4);
    printCenter("Please input ROOM (Number) :", 4, 4);

    int room;
    scin >> room;

    bool flag = clientService.sendJSON(QJsonObject{
            {"type", "game_start"},
            {"userId", player->getId()},
            {"room", room}
    });

    cls();
    printCenter("Wait another player to be connected", 10, RED);

    if (!flag) {
        warn("No one connect to your room!");
        emit(finish("game"));
    }
}

void Game::responseHandler(QJsonObject data) {
    list.clear();
    QString type = data["type"].toString();
    if (type == "game_start") {

        QJsonArray array = data["questions"].toArray();
        for (auto question: array) {
            list.push_back(Question(question.toObject()));
        }

        size = list.size();
        stage_time = data["stage_time"].toInt();
        gameStartHandler();
    } else if (type == "game_over") {
        gameOverController(data);
    }
}

void Game::gameStartHandler() {
    QTime start = QTime::currentTime(); // 开始时间

    bool flag = true; //闯关成功的标识
    for (int i = 0; i < size; i++) {
        if (!answerQuestion(i)) {
            flag = false;
            break;
        }
    }

    QTime stop = QTime::currentTime(); // 结束时间
    bool finished = true;
    if (flag) {
        int exp = getExp(start.msecsTo(stop));
        player->addStage();
        bool isLevelUp = player->obtainExp(exp);

        cls();
        printCenter("Congratulations! You've passed this stage!!", 10, GREEN);
        printCenter("GET EXP" + QString::number(exp), 11, RED);
        if (isLevelUp) {
            printCenter("Level Up to " + QString::number(player->getLevel()) + " !", 12, GREEN);
        }
        printCenter("Wait another player......", 14, BLACK);

    } else {
        finished = false;
        cls();

        printCenter("Sorry! Have a nice try!", 10, RED);
        printCenter("Wait another player......", 12, BLACK);
    }

    bool res = clientService.sendJSON(QJsonObject{
            {"type", "game_over"},
            {"userId", player->getId()},
            {"exp", player->getExp()},
            {"level", player->getLevel()},
            {"stage_obtained", player->getStage()},
            {"finished", finished}
    });

    if (!res) {
        info("Something wrong happened...");
        emit(finish("game"));
    }
}

void Game::gameOverController(QJsonObject data) {
    bool win = data["win"].toBool();
    if (win) {
        info("Win!!!!!");
    } else {
        warn("Lose!!!!!");
    }

    emit(finish("game"));
}

bool Game::answerQuestion(int i) {
    printInfo();
    print("Question ");print("No. ", RED);print(QString::number(i+1), RED);


    Question question = list[i];
    QString word = question.getWord();

    printCenter(word, 12, BLUE);
    hideCursor();

    QTime start = QTime::currentTime();

    while (true) {
        wait(1);
        if (start.msecsTo(QTime::currentTime()) >= stage_time) break;

        print(QString(getCols(), ' '), 0, 6);
        printCenter(QString::number(stage_time - start.msecsTo(QTime::currentTime())), 6, BLUE);

        if (kbhit()) {
            char x = getch();
            print("\b ");
        }

    }

    print(QString(getCols(), ' '), 0, 6);
    print(QString(getCols(), ' '), 0, 12, RED);
    printCenter(QString(word.length(), '_'), 12, RED);
    locateCenter(word.length(), 12);
    showCursor();

    QString answer;
    scin>>answer;

    return answer == word;
}

void Game::printInfo() {
    cls();
    locateCursor(2, 0);
    print("Player:"); print(player->getName(), RED);
    print(" Exp:"); print(QString::number(player->getExp()), GREEN);
    print(" Level:"); print(QString::number(player->getLevel()), BLUE);

    locateCursor(0, 4);
}

int Game::getExp(int time) {
    time /= size;
    time -= stage_time;
    // 低于三秒加分，高于三秒扣分
    time -= 3000;
    time = -time / 100;
    int level = 0;
    for (auto question: list) {
        level += question.getLevel();
    }

    level /= list.size();

    if (level + time > 15) {
        return 15;
    }
    if (level + time < 2) {
        return 2;
    }
    return (level + time);
}
