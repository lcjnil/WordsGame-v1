//
// Created by NiL on 15/6/14.
//

#include "board.h"
#include "../model/User.h"
#include "../utils/Console.h"

#include <vector>
#include <QString>

using namespace Console;
using namespace std;

std::vector<QString> Board::PlayerKeys {
        "userId", "name", "level", "exp", "stage_obtained"
};

std::vector<QString> Board::RefereeKeys {
        "userId", "name", "words_count", "level"
};

void Board::showPlayer() {
    cls();

    printCenter("Player Board", 2, BLACK);

    print("View Player By :", 4, 4);

    print("1. level", 4, 5);
    print("2. Exp", 4, 6);
    print("3. Stage Obtained", 4, 7);
    print("Q. Quit", 4, 8);

    switch(getch()) {
        case '1':
            listPlayer("level DESC");
            showPlayer();
            break;
        case '2':
            listPlayer("exp DESC");
            showPlayer();
            break;
        case '3':
            listPlayer("stage_obtained DESC");
            showPlayer();
            break;
        case 'q':
            break;
        default:
            showPlayer();
            break;
    }
}

void Board::showReferee() {
    cls();

    printCenter("Referee Board", 2, BLACK);

    print("View Player By :", 4, 4);

    print("1. words", 4, 5);
    print("1. level", 4, 6);
    print("Q. Quit", 4, 7);

    switch(getch()) {
        case '1':
            listReferee("words_count DESC");
            showReferee();
            break;
        case '2':
            listReferee("level DESC");
            showReferee();
            break;
        case 'q':
            break;
        default:
            showReferee();
            break;
    }
}

void Board::listPlayer(QString order) {
    cls();
    printCenter("Player Board", 2, BLACK);
    print("Order By " + order, 4, 4);

    vector<User> users = User::findAllWithOrder(order);

    locateCursor(0, 6);
    for (auto key: PlayerKeys) {
        print(key + "\t\t");
    }

    locateCursor(0, 8);
    for (auto user: users) {
        if (user.getType() == "referee") {
            continue;
        }
        for (auto key: PlayerKeys) {
            print(user.get(key) + "\t\t");
        }
        print("\n");
    }

    waitKey();
}

void Board::listReferee(QString order) {
    cls();
    printCenter("Referee Board", 2, BLACK);
    print("Order By " + order, 4, 4);

    vector<User> users = User::findAllWithOrder(order);

    locateCursor(0, 6);
    for (auto key: RefereeKeys) {
        print(key + "\t\t");
    }

    locateCursor(0, 8);
    for (auto user: users) {
        if (user.getType() == "player") {
            continue;
        }
        for (auto key: RefereeKeys) {
            print(user.get(key) + "\t\t");
        }
        print("\n");
    }

    waitKey();
}
