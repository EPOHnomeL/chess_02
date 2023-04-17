#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chessgame.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    apiProcess = new QProcess(this);
    apiProcess->start("\"C:\\Program Files\\nodejs\\node.exe\"", QStringList() << "C:\\Code\\C++\\Qt\\chess_02\\chess-api\\index.js");
    ChessGame *chessGame = new ChessGame(this);

    connect(chessGame, &ChessGame::turnChange, this, &MainWindow::turnChange);
    connect(chessGame, &ChessGame::gameFinished, this, &MainWindow::gameFinished);
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout();
    centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(chessGame->getBoard());

    QVBoxLayout *infoLayout = new QVBoxLayout();

    turnLabel = new QLabel("Turn : ⬜");
    QFont f = QFont("MS Shell Dlg 2", 15, 2);
    f.setBold(true);
    turnLabel->setFont(f);

    te = new QTextEdit();
    te->setText("Hi\nI'Am\nJonathan\n\n\n\n\n\n\nHi\n\n\n\n\n\n\n\n\nJaaa");
    te->setReadOnly(true);
//    te->setMaximumHeight(200);

    infoLayout->addWidget(turnLabel);
    infoLayout->setAlignment(turnLabel,Qt::AlignTop);
    infoLayout->addWidget(te);
    infoLayout->setAlignment(te,Qt::AlignLeading);
    infoLayout->addItem(new QSpacerItem(250, 0));

    mainLayout->setAlignment(chessGame->getBoard(),Qt::AlignLeft);
    mainLayout->addLayout(infoLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    apiProcess->close();
    delete ui;
}

void MainWindow::turnChange(QString move, bool player)
{
    if(!player)
        turnLabel->setText("Turn : ⬜");
    else
        turnLabel->setText("Turn : ⬛");
}

void MainWindow::gameFinished(QString reason, bool player)
{
    if(reason == "Checkmate")
        turnLabel->setText(player ? "⬜ WON": "⬛ WON");
}
