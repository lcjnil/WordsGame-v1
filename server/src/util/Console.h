//
// Created by NiL on 15/6/3.
//

#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <QTextStream>
#include <QString>
#include "rlutil.h"

#define BLACK 0
#define BLUE 1
#define RED 4
#define GREEN 2
#define WHITE 15


namespace Console {

    static QTextStream scin(stdin);

    static int getCols() {
        return rlutil::tcols();
    }

    static int getRows() {
        return rlutil::trows();
    }

    static void print(QString str) {
        rlutil::setColor(0);
        std::cerr << str.toStdString();
    }

    static void print(QString str, unsigned int color) {
        rlutil::setColor(color);
        std::cerr << str.toStdString();
    }

    static void print(QString str, int x, int y) {
        rlutil::setColor(BLACK);
        rlutil::locate(x, y);
        std::cerr<<str.toStdString();
    }


    static void print(QString str, int x, int y, int color) {
        rlutil::setColor(color);
        rlutil::locate(x, y);
        std::cerr<<str.toStdString();
    }

    static QString getPassword() {
        char x;
        QString password;
        while (x = getch()) {
            if (x == '\n') return password;

            password += QString(x);
            print("\b* ");
        }
    }

    static void locateCenter(int length, int y) {
        int x = (getCols() - length) / 2;
        rlutil::locate(x, y);
    }

    static void printCenter(QString str, int y, int color) {
        int x = (getCols() - str.length()) / 2;

        rlutil::setColor(color);
        rlutil::locate(x, y);
        std::cerr<<str.toStdString();
    }

    static void hideCursor() {
        rlutil::hidecursor();
    }

    static void showCursor() {
        rlutil::showcursor();
    }

    static void locateCursor(int x, int y) {
        rlutil::locate(x, y);
    }

    static void waitKey() {
        rlutil::anykey();
    }

    static void cls() {
        rlutil::cls();
    }

    static void wait(unsigned int ms) {
        rlutil::msleep(ms);
    }

    static char nb_getch() {
        return rlutil::nb_getch();
    }

    static void warn(QString text) {
        cls();
        printCenter(text, 10, RED);
        printCenter("Press any key to continue", 13, BLACK);
        waitKey();
    }

    static void info(QString text) {
        cls();
        printCenter(text, 10, GREEN);
        printCenter("Press any key to continue", 13, BLACK);
        waitKey();
    }

}

#endif //CONSOLE_H
