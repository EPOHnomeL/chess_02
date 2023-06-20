#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "lobby.h"
#include <QInputDialog>

MainMenu::MainMenu(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    single = ui->single;
    local = ui->local;
    lan = ui->lan;
    hs = ui->HighScores;

    score = new highscore(this);
    score->move(280,265);
    score->setFixedSize(200,200);
    score->hide();
    score->setText(score->buatify(score->findMostWins(score->readFile("score.txt"))));

    showHS = false;
    connect(single, &QPushButton::clicked, this, &MainMenu::singlePlayerOnClick);
    connect(local, &QPushButton::clicked, this, &MainMenu::localGameOnClick);
    connect(lan, &QPushButton::clicked, this, &MainMenu::lanGameOnClick);
    connect(hs, &QPushButton::clicked, this, &MainMenu::hsClick);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::singlePlayerOnClick()
{
    bool ok;
    QString username = QInputDialog::getText(0, "CHAESS", "Input username(no spaces or commas):", QLineEdit::Normal,"", &ok);
    this->hide();
    m = new MainWindow(0);
    m->setUsernames(username, "AI-Player");
    m->show();
}

void MainMenu::localGameOnClick()
{
    bool ok;
    QString username = QInputDialog::getText(0, "CHAESS", "Input username for player 1 (no spaces or commas):", QLineEdit::Normal,"", &ok);
    bool ok1;
    QString username1 = QInputDialog::getText(0, "CHAESS", "Input username for player 2(no spaces or commas):", QLineEdit::Normal,"", &ok1);
    this->hide();
    m = new MainWindow(1);
    m->setUsernames(username, username1);
    m->show();
}

void MainMenu::lanGameOnClick()
{
    this->hide();
    l = new Lobby();
    l->show();
}

void MainMenu::hsClick()
{
    if(!showHS){
        score->show();
        single->hide();
        lan->hide();
        local->hide();
    } else {
        score->hide();
        single->show();
        lan->show();
        local->show();
    }
    showHS = !showHS;
}
