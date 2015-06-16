//
// Created by NiL on 15/6/15.
//

#ifndef V3_CLIENTSERVICE_H
#define V3_CLIENTSERVICE_H

#include <QObject>
#include <QJsonObject>
#include <QTcpSocket>

class ClientService: public QObject {

    Q_OBJECT

public:
    static ClientService & getInstance() {
        static ClientService instance(0);
        return instance;
    }
    ClientService(QObject *parent) : QObject(parent) {};
    void link(QString ip);
    bool sendJSON(QJsonObject json);
    void sendJSON(QJsonObject json, bool needResponse);

signals:
    void receiveJSON(QJsonObject json);
    void connected();
    void disconnected();

private slots:
    void readData();
    void onConnected();
    void onDisConnected();
private:
    ClientService(ClientService const&);
    void operator=(ClientService const&);

    QTcpSocket * socket = new QTcpSocket();
};


#endif //V3_CLIENTSERVICE_H
