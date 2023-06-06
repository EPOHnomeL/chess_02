#include "mainmenu.h"
#include "ui_mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainMenu)
{
    ui->setupUi(this);
    single = ui->single;
    local = ui->local;
    lan = ui->lan;
    connect(single, &QPushButton::clicked, this, &MainMenu::singlePlayerOnClick);
    connect(local, &QPushButton::clicked, this, &MainMenu::localGameOnClick);
    connect(lan, &QPushButton::clicked, this, &MainMenu::lanGameOnClick);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::singlePlayerOnClick()
{
    this->hide();
    m = new MainWindow(0);
    m->show();
}

void MainMenu::localGameOnClick()
{
    this->hide();
    m = new MainWindow(1);
    m->show();
}

void MainMenu::lanGameOnClick()
{
    this->hide();
    m = new MainWindow(2);
    m->show();
}
