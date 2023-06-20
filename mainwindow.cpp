#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QPushButton>

MainWindow::MainWindow(int gameType, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    LAN = false;
    onePlayer = false;
    ui->setupUi(this);
    switch (gameType) {
    case 0: onePlayer = true;
        break;
    case 2 : LAN = true;
        break;
    default:
        break;
    }
    if(onePlayer)
    {
        apiProcess = new QProcess(this);
        apiProcess->start("\"node\"", QStringList() << "C:\\Code\\C++\\Qt\\chess_02\\chess-api\\index.js");
    }

    takenPieces = new QVector<Piece*>();

    chessGame = new ChessGame(onePlayer, LAN, this);
    moveCount = 1;
    z = 0;

    connect(chessGame, &ChessGame::turnChange, this, &MainWindow::turnChange);
    connect(chessGame, &ChessGame::gameFinished, this, &MainWindow::gameFinished);
    connect(chessGame, &ChessGame::pieceTaken, this, &MainWindow::pieceTaken);

    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout();
    centralWidget->setLayout(mainLayout);
    mainLayout->addWidget(chessGame->getBoard());

    QVBoxLayout *infoLayout = new QVBoxLayout();

    QFont f = QFont("MS Shell Dlg 2", 15, 2);
    f.setBold(true);
    turnLabel = new QLabel(QString("White's Turn"));
    turnLabel->setFont(f);
    user1 = new QLabel(QString("Piet Snoek"));
    user1->setFont(f);
    user2 = new QLabel(QString("Gerrie Kerrie"));
    user2->setFont(f);
    piecesLostView = new QGraphicsView();
    scene = new QGraphicsScene();
    piecesLostView->setScene(scene);
    piecesLostView->setMinimumHeight(380);

    te = new QTextEdit();
    te->setReadOnly(true);
    te->setMinimumHeight(380);

    hs = new highscore(this);

    infoLayout->addWidget(user1);
    infoLayout->setAlignment(user1,Qt::AlignTop);
    infoLayout->addWidget(te);
    infoLayout->setAlignment(te,Qt::AlignBottom);
    infoLayout->addWidget(turnLabel);
    infoLayout->setAlignment(turnLabel,Qt::AlignHCenter);
    infoLayout->addWidget(piecesLostView);
    infoLayout->setAlignment(piecesLostView,Qt::AlignTop);
    infoLayout->addItem(new QSpacerItem(250, 0));
    infoLayout->addWidget(user2);
    infoLayout->setAlignment(user2,Qt::AlignTop);

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

void MainWindow::setNetworking(Networking *n)
{
    chessGame->setNetworking(n);
    setUsernames(n->getUsername(0), n->getUsername(1));
}

void MainWindow::setUsernames(QString two, QString one)
{
    usernames[0] = one;
    usernames[1] = two;
    user1->setText(one);
    user2->setText(two);
}

void MainWindow::turnChange(QString move, bool player)
{
    if(player)
    {
        turnLabel->setText("Black's Turn");
        turnLabel->setStyleSheet("QLabel { background-color : black; color : white; }");
        te->setText(te->toPlainText() + QString("%1. ").arg(moveCount) + move);
        moveCount++;
    }
    else
    {
        turnLabel->setStyleSheet("QLabel { background-color : white; color : black; }");
        turnLabel->setText("White's Turn");
        te->setText(te->toPlainText() + "\t" + move + "\n");
    }
}

void MainWindow::pieceTaken(Piece *p)
{

    QImage *image = new QImage(QString(":img/%1_%2.png").arg(p->getColor() ? "w": "b").arg(p->getType()));
    QPixmap pix = QPixmap::fromImage(*image).scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *png = scene->addPixmap(pix); // Add pointer to array
    takenPieces->append(p);
    int b = 0;
    int w = 0;
    for (int i=0; i<takenPieces->length()-1 ; i++) {
        if(takenPieces->at(i)->getColor()){
            w++;
        }else{
            b++;
        }
    }
    png->setPos(17 + ((p->getColor() ? w : b) * 20), 13 + ((p->getColor() ? 0 : 200)));
}

void MainWindow::gameFinished(QString reason, bool player)
{
    if(reason == "Checkmate"){
        turnLabel->setText(player ? "WHITE WON": "BLACK WON");
        chessGame->getBoard()->setSquaresColors();
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(timertick()));
        timer->setInterval(1);
        timer->start();

        // Log high scores into textfile
        QString gameScore = QString("%1 1,%2 0").arg(usernames[player]).arg(usernames[!player]);
        hs->writeFile("score.txt", gameScore);
    }
}

void MainWindow::timertick()
{
    z++;
    chessGame->getBoard()->changeSquaresColors();
    if(z == 750){
     z = 0;
     chessGame->getBoard()->setSquaresColors();
    }
}
