//
// Created by NiL on 15/6/15.
//

#include "ServerService.h"
#include <QDebug>
#include <QJsonDocument>
#include <QTcpSocket>

void ServerService::start() {
    server = new QTcpServer(0);
    server->listen(QHostAddress("0.0.0.0"), 8080);
    connect(server, SIGNAL(newConnection()), this, SLOT(addClient()));
}

void ServerService::addClient() {
    QTcpSocket * socket = server->nextPendingConnection();
    sockets.push_back(socket);
    qDebug() << "New Client!";

    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisConnected()));
}

void ServerService::onDisConnected() {
    QTcpSocket * socket = dynamic_cast<QTcpSocket*>(sender());
    sockets.removeOne(socket);
    removeFromRoom(socket->socketDescriptor());
}

void ServerService::readData() {
    QTcpSocket * socket = dynamic_cast<QTcpSocket*>(sender());
    QJsonDocument jsonDocument = QJsonDocument::fromJson(socket->readLine());
    qDebug() << jsonDocument;
    emit(receiveJSON(jsonDocument.object(), socket->socketDescriptor()));
}

void ServerService::send(QJsonObject json, qintptr id) {
    qDebug() << "send";
    QTcpSocket *socket = findSocketById(id);
    socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
}

QTcpSocket* ServerService::findSocketById(qintptr id) {
    for (auto socket: sockets) {
        if (socket->socketDescriptor() == id) {
            return socket;
        }
    }
}

bool ServerService::addToRoom(int roomId, qintptr id) {
    qDebug() << room[roomId].size();
    switch (room[roomId].size()) {
        case 0:
            room[roomId].push_back(id);
            roomNumber[id] = roomId;
            emit(addRoom(roomId, 1));
            break;
        case 1:
            room[roomId].push_back(id);
            roomNumber[id] = roomId;
            emit(addRoom(roomId, 2));
        case 2:
            return false;
    }
    return true;
}

bool ServerService::removeFromRoom(qintptr id) {
    room[roomNumber[id]].removeAll(id);
    roomNumber[id] = 0;
}

void ServerService::multicast(int roomId, QJsonObject data) {
    for (auto id: room[roomId]) {
        send(data, id);
    }
}

