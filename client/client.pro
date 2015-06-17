#-------------------------------------------------
#
# Project created by QtCreator 2015-06-15T21:25:35
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = client
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    src/controller/app.cpp \
    src/service/ClientService.cpp \
    src/controller/game.cpp \
    src/model/Model.cpp \
    src/model/Player.cpp \
    src/model/Question.cpp \
    src/model/User.cpp \
    src/controller/board.cpp \
    src/util/Console.cpp

HEADERS += \
    src/controller/app.h \
    src/service/ClientService.h \
    src/util/rlutil.h \
    src/util/Console.h \
    src/controller/game.h \
    src/model/Model.h \
    src/model/Player.h \
    src/model/Question.h \
    src/model/User.h \
    src/controller/board.h
