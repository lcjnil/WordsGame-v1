#-------------------------------------------------
#
# Project created by QtCreator 2015-06-15T21:25:13
#
#-------------------------------------------------

QT       += core network sql

QT       -= gui

TARGET = server
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    src/controller/Server.cpp \
    src/model/Connection.cpp \
    src/model/Player.cpp \
    src/model/Question.cpp \
    src/model/Referee.cpp \
    src/model/User.cpp \
    src/service/ServerService.cpp

HEADERS += \
    src/controller/Server.h \
    src/model/Connection.h \
    src/model/Model.h \
    src/model/Player.h \
    src/model/Question.h \
    src/model/Referee.h \
    src/model/User.h \
    src/service/ServerService.h \
    src/util/Console.h \
    src/util/rlutil.h
