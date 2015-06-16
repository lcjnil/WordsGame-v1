//
// Created by NiL on 15/6/15.
//

#include <QHostAddress>
#include <QJsonDocument>
#include <QDebug>
#include "ClientService.h"

void ClientService::link(QString ip) {
    if (ip == "") {
        socket->connectToHost(QHostAddress::LocalHost, 8080);
    } else {
        socket->connectToHost(QHostAddress(ip), 8080);
    }

    connect(socket, SIGNAL(connected()), this, SLOT(onConnected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisConnected()));
}

void ClientService::onConnected() {
    emit(connected());
}

void ClientService::onDisConnected() {
    emit(disconnected());
}

void ClientService::readData() {
    QJsonDocument jsonDocument = QJsonDocument::fromJson(socket->readLine());
    emit(receiveJSON(jsonDocument.object()));
}

bool ClientService::sendJSON(QJsonObject json) {
    socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    socket->waitForBytesWritten();
    if (socket->waitForReadyRead()) {
        readData();
        return true;
    } else {
        return false;
    }
}

void ClientService::sendJSON(QJsonObject json, bool needResponse) {
    socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    socket->waitForBytesWritten();
    if (needResponse && socket->waitForReadyRead()) {
        readData();
    }
}
