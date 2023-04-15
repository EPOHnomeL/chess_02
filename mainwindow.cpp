#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chessgame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    apiProcess = new QProcess(this);
    apiProcess->start("\"C:\\Program Files\\nodejs\\node.exe\"", QStringList() << "C:\\Code\\C++\\Qt\\chess_02\\chess-api\\index.js");
    ChessGame *chessGame = new ChessGame(this);
    this->setCentralWidget(chessGame->getBoard());
}

MainWindow::~MainWindow()
{
    delete ui;
}
