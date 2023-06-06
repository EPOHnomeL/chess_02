#include "lobby.h"
#include "ui_lobby.h"

Lobby::Lobby(QWidget *parent) : QMainWindow(parent), ui(new Ui::Lobby)
{
    ui->setupUi(this);
    single = ui->single;
    local = ui->local;
    lan = ui->lan;
    connect(single, &QPushButton::clicked, this, &Lobby::singlePlayerOnClick);
    connect(local, &QPushButton::clicked, this, &Lobby::localGameOnClick);
    connect(lan, &QPushButton::clicked, this, &Lobby::lanGameOnClick);
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::singlePlayerOnClick()
{
    this->hide();
    m = new MainWindow(0);
    m->show();
}

void Lobby::localGameOnClick()
{
    this->hide();
    m = new MainWindow(1);
    m->show();
}

void Lobby::lanGameOnClick()
{
    this->hide();
    m = new MainWindow(2);
    m->show();
}
