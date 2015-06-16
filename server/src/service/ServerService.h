//
// Created by NiL on 15/6/15.
//

#ifndef V3_SERVERSERVICE_H
#define V3_SERVERSERVICE_H

#include <QObject>
#include <QJsonObject>
#include <QTcpServer>
#include <QTcpSocket>


class ServerService: public QObject {

Q_OBJECT

public:
    static ServerService & getInstance() {
        static ServerService instance(0);
        return instance;
    }

    ServerService(QObject *parent = 0): QObject(parent) {};
    void start();
    void send(QJsonObject json, qintptr id);

signals:
    void receiveJSON(QJsonObject json, qintptr id);

private:
    //singleton
    ServerService(ServerService const&);
    void operator=(ServerService const&);

    QTcpServer *server;
    QList<QTcpSocket* > sockets;

    QTcpSocket* findSocketById(qintptr id);

private slots:
    void addClient();
    void readData();
    void onDisConnected();

};


#endif //V3_SERVERSERVICE_H