#include "lobby.h"
#include "ui_lobby.h"
#include "QTcpSocket"
#include "QHostAddress"
#include <QInputDialog>

Lobby::Lobby(QWidget *parent) : QMainWindow(parent), ui(new Ui::Lobby)
{
    ui->setupUi(this);
    clientButton = ui->client;
    hostButton = ui->host;
    info = ui->info;
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
    QTcpSocket socket;
    socket.connectToHost("8.8.8.8", 53); // google DNS, or something else reliable
    if (socket.waitForConnected()) {
        info->setText(QString("Waiting for players to connect to %1...").arg(socket.localAddress().toString()));
    } else {
        qWarning()
            << "could not determine local IPv4 address:"
            << socket.errorString();
    }
    server = new Server;
    connect(server, SIGNAL(dataReceived(QByteArray)), this, SLOT(receive(QByteArray)));
}

void Lobby::clientOnClick()
{
    hostButton->hide();
    clientButton->hide();
    bool ok;
    QString text = QInputDialog::getText(0, "Input IP", "Input Host IP Address:", QLineEdit::Normal,"", &ok);
     info->setText(QString("Connecting to %1...").arg(text));

     client = new Client;
     connect(client, SIGNAL(dataReceived(QByteArray)), this, SLOT(receive(QByteArray)));
     if (!client->connectToHost(text))
     {
         client->deleteLater();
         return;
     }
}

void Lobby::clientSend()
{
    client->writeData(input->toPlainText().toUtf8());
}

void Lobby::receive(QByteArray data)
{
    if (output)
        output->setText(output->text() + "\n" + data);
}

