#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chessgame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ChessGame *chessGame = new ChessGame(this);

    this->setCentralWidget(chessGame->getBoard());
}

MainWindow::~MainWindow()
{
    delete ui;
}

