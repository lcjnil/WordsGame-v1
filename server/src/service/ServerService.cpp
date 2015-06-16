//
// Created by NiL on 15/6/15.
//

#include "ServerService.h"
#include <QDebug>
#include <QJsonDocument>
#include <QTcpSocket>

void ServerService::start() {
    server = new QTcpServer(0);
    server->listen(QHostAddress::LocalHost, 8080);
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
