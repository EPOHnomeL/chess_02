#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "chessboard.h"
#include "piece.h"
#include "mygraphicsscene.h"
#include "checkmanager.h"
#include "rulemanager.h"
#include "api.h"
#include "networking.h"

class Networking;

class ChessGame : public QObject
{
    Q_OBJECT
public:
    explicit ChessGame(bool onePlayer, bool LAN, QObject *parent = nullptr);
    void setNetworking(Networking *n);
    ChessBoard *getBoard() const;

signals:
    void turnChange(QString move, bool player);
    void gameFinished(QString reason, bool player);
    void pieceTaken(Piece* p);

private slots:
    void userClickedSquare(Pos pos);
    void promotePawn(Pos pos);
    void receive(QByteArray data);

private:
    bool inGame;
    bool onePlayer, LAN, canMove;
    bool aiTurn;
    const QColor selectedPiece = QColor(0, 0, 0);
    const QColor validSquare = QColor(50, 50, 50);
    Pos select;
    CheckManager *cm;
    Networking *n;
    QVector<Pos> *validMoves;
    ChessBoard *board;
    Piece *state[8][8];
    bool whitesTurn;
    bool canCastle[2];
    void checkCastle(Piece *king, Pos to);
    void setupPieces();
    void afterMoveForAI(Pos from, Pos to);
    void afterMoveForLAN(Pos from, Pos to);
    QString getMoveNotation(Pos from, Pos to);
    Move recursivlyAskForAIMove();
    Move stringToMove(QString str);
    QString posToString(Pos p);
    Api* api;
    QNetworkAccessManager *netManager;
    QNetworkReply *netReply;
};

#endif // CHESSGAME_H
