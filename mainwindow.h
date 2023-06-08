#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QLabel>
#include <QTextEdit>
#include <QGraphicsView>
#include "chessgame.h"
#include "networking.h"

class Networking;
class ChessGame;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int gameType, QWidget *parent = nullptr);
    ~MainWindow();
    void setNetworking(Networking *n);

private slots:
    void turnChange(QString move, bool player);
    void pieceTaken(Piece *p);
    void gameFinished(QString reason, bool player);
    void timertick();

private:
    Ui::MainWindow *ui;
    int moveCount, z;
    bool onePlayer, LAN;
    Networking *n;
    ChessGame *chessGame;
    QProcess *apiProcess;
    QProcess *dbProcess;
    QLabel *turnLabel, *user1, *user2;
    QVector<Piece*> *takenPieces;
    QTextEdit *te;
    QGraphicsScene *scene;
    QTimer *timer;
    QGraphicsView *piecesLostView;
};
#endif // MAINWINDOW_H
