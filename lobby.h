#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>
#include <QPushButton>
#include "mainwindow.h"
#include "server.h"
#include "client.h"

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
    void makeClient();
    void makeServer();
    void clientSend();
    void receive(QByteArray);

private:
    Server *server;
    Client *client;
    QTextEdit *input;
    QLabel *output;

    MainWindow *m;
    Ui::Lobby *ui;
    QPushButton *hostButton, *clientButton;
    QLabel *info;

};

#endif // MAINMENU_H
