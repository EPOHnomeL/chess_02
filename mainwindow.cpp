#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "chessgame.h"
#include <QPushButton>

MainWindow::MainWindow(int gameType, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    switch (gameType) {
    case 0: onePlayer = true;
        break;
    case 1: onePlayer = false;
        break;
    case 2 : {onePlayer = false;
              LAN = true;}
        break;
    default:
        break;
    }
    if(onePlayer)
    {
        apiProcess = new QProcess(this);
        apiProcess->start("\"C:\\Program Files\\nodejs\\node.exe\"", QStringList() << "C:\\Code\\C++\\Qt\\chess_02\\chess-api\\index.js");
    }
    ChessGame *chessGame = new ChessGame(onePlayer, LAN, this);
    moveCount = 1;

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

    piecesLostView = new QGraphicsView();
    piecesLostView->setScene(new QGraphicsScene());
    piecesLostView->setMinimumHeight(280);

    te = new QTextEdit();
    te->setReadOnly(true);
    te->setMinimumHeight(0);

    infoLayout->addWidget(turnLabel);
    infoLayout->setAlignment(turnLabel,Qt::AlignTop);
    infoLayout->addWidget(te);
    infoLayout->setAlignment(te,Qt::AlignTrailing);
    infoLayout->addWidget(piecesLostView);
    infoLayout->setAlignment(piecesLostView,Qt::AlignVCenter);
    infoLayout->addItem(new QSpacerItem(250, 200));

    mainLayout->setAlignment(chessGame->getBoard(),Qt::AlignLeft);
    mainLayout->addLayout(infoLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    if(onePlayer)
    {
        apiProcess->terminate();
        apiProcess->kill();
        apiProcess->close();
    }
    delete ui;
}

void MainWindow::turnChange(QString move, bool player)
{
    if(player)
    {
        turnLabel->setText("Turn : ⬛");
        te->setText(te->toPlainText() + QString("%1. ").arg(moveCount) + move);
        moveCount++;
    }
    else
    {
        turnLabel->setText("Turn : ⬜");
        te->setText(te->toPlainText() + "\t" + move + "\n");
    }
}

void MainWindow::gameFinished(QString reason, bool player)
{
    if(reason == "Checkmate")
        turnLabel->setText(player ? "⬜ WON": "⬛ WON");
}
