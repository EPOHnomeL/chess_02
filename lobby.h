#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>
#include <QPushButton>
#include "mainwindow.h"

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

private:
    MainWindow *m;
    Ui::Lobby *ui;
    QPushButton *host, *client;
    QLabel *info;

};

#endif // MAINMENU_H
