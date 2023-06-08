#ifndef NETWORKING_H
#define NETWORKING_H

#include <QMainWindow>
#include <QPushButton>
#include "mainwindow.h"
#include "server.h"
#include "client.h"

class Networking : QObject
{
    Q_OBJECT
public:
    explicit Networking(QWidget *parent = nullptr);
    ~Networking();
    QString createServer();
    bool createClient(QString ip);
    bool clientSend(QString send);
    bool serverSend(QString send);
    bool isServer;

    Server *getServer() const;
    Client *getClient() const;
    void setUsernames(QString server, QString client);
    QString getUsername(int i);

private:
    Server *server;
    Client *client;
    QString usernames[2];

};

#endif // NETWORKING_H
