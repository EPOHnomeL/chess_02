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

class ChessGame : public QObject
{
    Q_OBJECT
public:
    explicit ChessGame(QObject *parent = nullptr);

    ChessBoard *getBoard() const;

signals:
    void turnChange(QString move, bool player);
    void gameFinished(QString reason, bool player);

private slots:
    void userClickedSquare(Pos pos);
    void promotePawn(Pos pos);

private:
    bool inGame;
    const QColor selectedPiece = QColor(0, 0, 0);
    const QColor validSquare = QColor(50, 50, 50);
    Pos select;
    CheckManager *cm;
    QVector<Pos> *validMoves;
    ChessBoard *board;
    Piece *state[8][8];
    bool whitesTurn;
    bool canCastle[2];
    void checkCastle(Piece *king, Pos to);
    void setupPieces();
    void afterMove(Pos from, Pos to);
    QString getMoveNotation(Pos from, Pos to);
    Api* api;
    QNetworkAccessManager *netManager;
    QNetworkReply *netReply;
};

#endif // CHESSGAME_H
