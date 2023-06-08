#include "networking.h"
#include "QTcpSocket"
#include "QHostAddress"
#include <QInputDialog>

Networking::Networking(QWidget *parent)
{
    isServer = false;
}

Networking::~Networking()
{
    if (client)
        client->deleteLater();

    if (server)
        server->deleteLater();
}

QString Networking::createServer()
{
    QString s;
    QTcpSocket socket;
    socket.connectToHost("8.8.8.8", 53); // google DNS, or something else reliable
    if (socket.waitForConnected()) {
        s =socket.localAddress().toString();
    } else {
        s = "127.0.0.1";
    }
    server = new Server();
    isServer = true;
    return s;
}

bool Networking::createClient(QString ip)
{
    client = new Client();
    isServer = false;
     if (!client->connectToHost(ip))
     {
         client->deleteLater();
         return false;
     }
     return true;
}

bool Networking::clientSend(QString send)
{
     return client->writeData(send.toUtf8());
}

bool Networking::serverSend(QString send){
    return server->writeData(send.toUtf8());
}

Server *Networking::getServer() const
{
    return server;
}

Client *Networking::getClient() const
{
    return client;
}

void Networking::setUsernames(QString name1, QString name2)
{
    usernames[0] = name1;
    usernames[1] = name2;
}

QString Networking::getUsername(int i)
{
    return usernames[i];
}

