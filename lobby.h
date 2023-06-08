#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>
#include <QPushButton>
#include "mainwindow.h"
#include "server.h"
#include "client.h"
#include "networking.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Lobby;
}
QT_END_NAMESPACE

class Lobby : public QMainWindow
{
    Q_OBJECT
public:
    explicit Lobby(QWidget *parent = nullptr);
    ~Lobby();

public slots:
    void hostOnClick();
    void clientOnClick();

private slots:
    void serverReceive(QByteArray);
    void clientReceive(QByteArray);

private:
    Server *server;
    Client *client;
    QString username;
    Networking *n;

    MainWindow *m;
    Ui::Lobby *ui;
    QPushButton *hostButton, *clientButton;
    QLabel *info;

};

#endif // MAINMENU_H
