#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T11:35:36
#
#-------------------------------------------------

QT       += core sql

QT       -= gui

TARGET = WG_V2
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    src/controller/app.cpp \
    src/model/Connection.cpp \
    src/controller/game.cpp \
    src/model/Referee.cpp \
    src/model/Player.cpp \
    src/model/Question.cpp \
    src/model/User.cpp \
    src/controller/board.cpp

HEADERS += \
    lib/rlutil.h \
    src/utils/Console.h \
    src/controller/app.h \
    src/model/Connection.h \
    src/model/Model.h \
    src/controller/game.h \
    src/model/Referee.h \
    src/model/Player.h \
    src/model/User.h \
    src/model/Question.h \
    src/controller/board.h
