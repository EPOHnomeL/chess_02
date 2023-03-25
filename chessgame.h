#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include "chessboard.h"
#include "piece.h"
#include "mygraphicsscene.h"
#include "rulemanager.h"

class ChessGame : public QObject
{
    Q_OBJECT
public:
    explicit ChessGame(QObject *parent = nullptr);

    ChessBoard *getBoard() const;

private slots:
    void userClickedSquare(Pos pos);

private:
    Pos select;
    RuleManager *rm;
    QVector<Pos> *validMoves;
    ChessBoard *board;
    Piece *state[8][8];
    bool whitesTurn;
    void setupPieces();
};

#endif // CHESSGAME_H
