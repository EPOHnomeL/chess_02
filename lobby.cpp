#include "lobby.h"
#include "ui_lobby.h"
#include "QTcpSocket"
#include "QHostAddress"
#include <QInputDialog>

Lobby::Lobby(QWidget *parent) : QMainWindow(parent), ui(new Ui::Lobby)
{
    ui->setupUi(this);
    client = ui->client;
    host = ui->host;
    info = ui->info;
    connect(host, &QPushButton::clicked, this, &Lobby::hostOnClick);
    connect(client, &QPushButton::clicked, this, &Lobby::clientOnClick);
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::hostOnClick()
{
    host->hide();
    client->hide();
    QTcpSocket socket;
    socket.connectToHost("8.8.8.8", 53); // google DNS, or something else reliable
    if (socket.waitForConnected()) {
        info->setText(QString("Waiting for players to connect to %1...").arg(socket.localAddress().toString()));
    } else {
        qWarning()
            << "could not determine local IPv4 address:"
            << socket.errorString();
    }
}

void Lobby::clientOnClick()
{
    host->hide();
    client->hide();
    bool ok;
    QString text = QInputDialog::getText(0, "Input IP", "Input Host IP Address:", QLineEdit::Normal,"", &ok);
     info->setText(QString("Connecting to %1...").arg(text));
}

