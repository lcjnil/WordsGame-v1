//
// Created by NiL on 15/6/14.
//

#include "board.h"
#include "../util/Console.h"

#include <vector>
#include <QString>
#include <QJsonArray>

using namespace Console;
using namespace std;

std::vector<QString> Board::PlayerKeys {
        "userId", "name", "level", "exp", "stage_obtained"
};

std::vector<QString> Board::RefereeKeys {
        "userId", "name", "words_count", "level"
};

Board::Board() {
    connect(&clientService, SIGNAL(receiveJSON(QJsonObject)), this, SLOT(responseHandler(QJsonObject)));
}

void Board::responseHandler(QJsonObject data) {
    QString type = data["type"].toString();

    if (type == "board") {
        boardHandler(data);
    }
}

void Board::boardHandler(QJsonObject data) {
    QString type = data["data_type"].toString();

    vector<QString> *keys;

    if (type == "player") {
        keys = &PlayerKeys;
    } else {
        keys = &RefereeKeys;
    }

    cls();

    printCenter(type + " Board", 2, BLACK);
    print("Order By " + data["order_by"].toString(), 4, 4);

    locateCursor(0, 6);
    for (auto key: *keys) {
        print(key + "\t\t");
    }

    locateCursor(0, 8);

    for (auto user: data["users"].toArray()) {
        for (auto key: *keys) {
            print(user.toObject()[key].toString() + "\t\t");
        }
        print("\n");
    }

    waitKey();

    if (type == "player") {
        showPlayer();
    } else {
        showReferee();
    }
}

void Board::showPlayer() {
    cls();

    printCenter("Player Board", 2, BLACK);

    print("View Player By :", 4, 4);

    print("1. level", 4, 5);
    print("2. Exp", 4, 6);
    print("3. Stage Obtained", 4, 7);
    print("Q. Quit", 4, 8);

    QString order_by;
    switch(getch()) {
        case '1':
            order_by = "level DESC";
            break;
        case '2':
            order_by = "exp DESC";
            break;
        case '3':
            order_by = "stage_obtained DESC";
            break;
        case 'q':
            emit(finish("board_player"));
            break;
        default:
            showPlayer();
            break;
    }

    clientService.sendJSON(QJsonObject{
            {"type", "board"},
            {"data_type", "player"},
            {"order_by", order_by}
    });
}

void Board::showReferee() {
    cls();

    printCenter("Referee Board", 2, BLACK);

    print("View Player By :", 4, 4);

    print("1. words", 4, 5);
    print("1. level", 4, 6);
    print("Q. Quit", 4, 7);

    QString order_by;

    switch(getch()) {
        case '1':
            order_by = "words_count DESC";
            break;
        case '2':
            order_by = "level DESC";
            break;
        case 'q':
            emit(finish("board_referee"));
            break;
        default:
            showReferee();
            break;
    }

    clientService.sendJSON(QJsonObject{
            {"type", "board"},
            {"data_type", "referee"},
            {"order_by", order_by}
    });
}
