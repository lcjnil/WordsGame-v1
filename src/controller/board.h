//
// Created by NiL on 15/6/14.
//

#ifndef WORDSGAME_BOARD_H
#define WORDSGAME_BOARD_H


#include <QString>
#include <vector>

class Board {

public:
    void showPlayer();
    void showReferee();

private:
    void listPlayer(QString order);
    void listReferee(QString order);
    static std::vector<QString> PlayerKeys;
    static std::vector<QString> RefereeKeys;
};


#endif //WORDSGAME_BOARD_H
