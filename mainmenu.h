#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QPushButton>
#include "mainwindow.h"
#include "lobby.h"
#include "highscore.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainMenu;
}
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

public slots:
    void singlePlayerOnClick();
    void localGameOnClick();
    void lanGameOnClick();
    void hsClick();

private:
    bool showHS;
    MainWindow *m;
    Lobby *l;
    highscore *score;
    QProcess *dbProcess;
    Ui::MainMenu *ui;
    QPushButton *single, *local, *lan, *hs;

};

#endif // MAINMENU_H
