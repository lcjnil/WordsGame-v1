//
// Created by NiL on 15/6/3.
//

#include "Console.h"
namespace Console {
    int getCols() {
        return rlutil::tcols();
    }

    int getRows() {
        return rlutil::trows();
    }

    void print(QString str) {
        rlutil::setColor(0);
        std::cerr << str.toStdString();
    }

    void print(QString str, unsigned int color) {
        rlutil::setColor(color);
        std::cerr << str.toStdString();
    }

    void print(QString str, int x, int y) {
        rlutil::setColor(BLACK);
        rlutil::locate(x, y);
        std::cerr << str.toStdString();
    }


    void print(QString str, int x, int y, int color) {
        rlutil::setColor(color);
        rlutil::locate(x, y);
        std::cerr << str.toStdString();
    }

    QString getPassword() {
        char x;
        QString password;
        while (x = getch()) {
            if (x == '\n') return password;

            password += QString(x);
            print("\b* ");
        }
    }

    void locateCenter(int length, int y) {
        int x = (getCols() - length) / 2;
        rlutil::locate(x, y);
    }

    void printCenter(QString str, int y, int color) {
        int x = (getCols() - str.length()) / 2;

        rlutil::setColor(color);
        rlutil::locate(x, y);
        std::cerr << str.toStdString();
    }

    void hideCursor() {
        rlutil::hidecursor();
    }

    void showCursor() {
        rlutil::showcursor();
    }

    void locateCursor(int x, int y) {
        rlutil::locate(x, y);
    }

    void waitKey() {
        rlutil::anykey();
    }

    void cls() {
        rlutil::cls();
    }

    void wait(unsigned int ms) {
        rlutil::msleep(ms);
    }

    char nb_getch() {
        return rlutil::nb_getch();
    }

    void warn(QString text) {
        cls();
        printCenter(text, 10, RED);
        printCenter("Press any key to continue", 13, BLACK);
        waitKey();
    }

    void info(QString text) {
        cls();
        printCenter(text, 10, GREEN);
        printCenter("Press any key to continue", 13, BLACK);
        waitKey();
    }
}
