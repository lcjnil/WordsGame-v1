#include "game.h"
#include "../utils/Console.h"

#include <algorithm>
#include <ctime>
#include <QTime>

using namespace Console;
Game::Game(Player *player)
{
    this->player = player;
}

void Game::start() {
    printInfo();
    initQuestion();

    printCenter("Welcome to GAME!!!", 10, BLACK);
    printCenter("If you're READY! HIT any key!", 12, BLACK);
    waitKey();

    int i = 0;
    bool flag = true; //闯关成功的标识
    while (i++ < size) {
        if (!answerQuestion(i)) {
            flag = false;
            break;
        }
    }

    if (flag) {
        //闯关成功
        printInfo();
        player->addStage();

        printCenter("Congratulations! You've passed this stage!!", 10, GREEN);
        printCenter("Press any key to continue", 12, BLACK);

        waitKey();
    } else {
        //闯关失败

        printInfo();
        player->addStage();

        printCenter("Sorry! Have a nice try!", 10, RED);
        printCenter("Press any key to continue", 12, BLACK);

        waitKey();
    }
}


void Game::initQuestion() {
    list = Question::getAllQuestion();
    std::random_shuffle(list.begin(), list.end(), [](int i){return clock() % i;});
}

bool Game::answerQuestion(int i) {
    printInfo();
    print("Question ");print("No. ", RED);print(QString::number(i), RED);

    QString t(getCols(), '-');

    print(t, 0, 8, BLACK);
    print(t, 0, 16, BLACK);

    Question question = list[i];
    QString word = question.getWord();

    printCenter(word, 12, RED);
    hideCursor();

    QTime start = QTime::currentTime();

    while (true) {
        wait(1);
        if (start.msecsTo(QTime::currentTime()) >= ms) break;

        if (kbhit()) {
            char x = getch();
            print("\b ");
        }

    }

    print(QString(getCols(), '_'), 0, 12, RED);
    locateCenter(word.length(), 12);
    showCursor();

    QString answer;
    scin>>answer;

    if (answer == word) {
        // 经验值为问题等级
        bool isLevelUp = player->obtainExp(question.getLevel());
        if (isLevelUp) {
            print(QString(getCols(), ' '), 0, 12, BLACK);
            printCenter("Level Up!", 12, GREEN);
            printCenter("Press any key to continue", 13, BLACK);
            waitKey();
        }
        return true;
    } else {
        return false;
    }
}

void Game::printInfo() {
    cls();
    locateCursor(2, 0);
    print("Player:"); print(player->getName(), RED);
    print(" Exp:"); print(QString::number(player->getExp()), GREEN);
    print(" Level:"); print(QString::number(player->getLevel()), BLUE);

    locateCursor(0, 4);
}
