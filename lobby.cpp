#include "lobby.h"
#include "ui_lobby.h"
#include "QTcpSocket"
#include "QHostAddress"
#include <QInputDialog>

Lobby::Lobby(QWidget *parent) : QMainWindow(parent), ui(new Ui::Lobby)
{
    n = new Networking(this);
    ui->setupUi(this);
    clientButton = ui->client;
    hostButton = ui->host;
    info = ui->info;
//    bool ok;
    username = "SAMENAME";//QInputDialog::getText(0, "CHAESS", "Input username:", QLineEdit::Normal,"", &ok);
    connect(hostButton, &QPushButton::clicked, this, &Lobby::hostOnClick);
    connect(clientButton, &QPushButton::clicked, this, &Lobby::clientOnClick);
}

Lobby::~Lobby()
{
    delete ui;
    if (client)
        client->deleteLater();

    if (server)
        server->deleteLater();
}

void Lobby::hostOnClick()
{
    hostButton->hide();
    clientButton->hide();
    QString ip = n->createServer();
    info->setText(QString("Waiting for player to connect to %1").arg(ip));
    connect(n->getServer(), SIGNAL(dataReceived(QByteArray)), this, SLOT(serverReceive(QByteArray)));
}

void Lobby::clientOnClick()
{
//    bool ok;
    QString text = "192.168.1.21";//QInputDialog::getText(0, "Input IP", "Input Host IP Address:", QLineEdit::Normal,"", &ok);
     info->setText(QString("Connecting to %1...").arg(text));
     // Create client and connect to input
     if(!n->createClient(text)){
         qWarning() << "That did'nt work";
     }
     hostButton->hide();
     clientButton->hide();
     connect(n->getClient(), SIGNAL(dataReceived(QByteArray)), this, SLOT(clientReceive(QByteArray)));
     // Send data through client
     n->clientSend(username);
}

void Lobby::serverReceive(QByteArray data)
{
    info->setText("Users conneted: \n" + username + " (host)\n" + data + " (client) ");
    n->setUsernames(username, data);
    n->serverSend(username.toUtf8());
    m = new MainWindow(2, this);
    m->setNetworking(n);
    m->show();
    this->hide();
    disconnect(n->getServer(), SIGNAL(dataReceived(QByteArray)), this, SLOT(serverReceive(QByteArray)));
}

void Lobby::clientReceive(QByteArray data)
{
    info->setText("Users conneted: \n" + data + " (host)\n" + username + " (client)");
        n->setUsernames(data, username);
    m = new MainWindow(2, this);
    m->setNetworking(n);
    m->show();
    this->hide();
    disconnect(n->getClient(), SIGNAL(dataReceived(QByteArray)), this, SLOT(clientReceive(QByteArray)));
}

