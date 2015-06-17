//
// Created by NiL on 15/6/3.
//

#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <QTextStream>
#include <QString>
#include "rlutil.h"

#define BLACK 15
#define BLUE 1
#define RED 4
#define GREEN 2
#define WHITE 0


namespace Console {

     static QTextStream scin(stdin);

     int getCols();

     int getRows();

     void print(QString str);

     void print(QString str, unsigned int color);

     void print(QString str, int x, int y);
    
     void print(QString str, int x, int y, int color);

     QString getPassword();

     void locateCenter(int length, int y);

     void printCenter(QString str, int y, int color);

     void hideCursor();

     void showCursor();

     void locateCursor(int x, int y);

     void waitKey();

     void cls();

     void wait(unsigned int ms);

     char nb_getch();

     void warn(QString text);

     void info(QString text);

}

#endif //CONSOLE_H
