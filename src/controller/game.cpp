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

    QTime start = QTime::currentTime(); // 开始时间

    int i = 0;
    bool flag = true; //闯关成功的标识
    while (i++ < size) {
        if (!answerQuestion(i)) {
            flag = false;
            break;
        }
    }

    QTime stop = QTime::currentTime(); // 结束时间

    if (flag) {
        int exp = getExp(start.msecsTo(stop));
        player->addStage();
        cls();
        printCenter("Congratulations! You've passed this stage!!", 10, GREEN);
        printCenter("GET EXP" + QString::number(exp), 11, RED);
        printCenter("Press any key to continue", 13, BLACK);
        waitKey();

        bool isLevelUp = player->obtainExp(exp);
        if (isLevelUp) {
            cls();
            printCenter("Level Up to " + QString::number(player->getLevel()) + " !", 10, GREEN);
            printCenter("Press any key to continue", 13, BLACK);
        }
        waitKey();
    } else {
        cls();
        player->addStage();

        printCenter("Sorry! Have a nice try!", 10, RED);
        printCenter("Press any key to continue", 12, BLACK);

        waitKey();
    }
}


void Game::initQuestion() {
    int level = player->getLevel();
    stage_time = 3000 - level * 300;
    if (stage_time <= 1000) {
        stage_time = 1000;
    }
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
        if (start.msecsTo(QTime::currentTime()) >= stage_time) break;

        print(QString(getCols(), ' '), 0, 6);
        printCenter(QString::number(stage_time - start.msecsTo(QTime::currentTime())), 6, BLUE);

        if (kbhit()) {
            char x = getch();
            print("\b ");
        }

    }

    print(QString(getCols(), ' '), 0, 6);
    print(QString(getCols(), '_'), 0, 12, RED);
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

    if (level + time > 15) {
        return 15;
    }
    if (level + time < 2) {
        return 2;
    }
    return (level + time);
}
