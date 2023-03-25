#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <QObject>
#include <QWidget>
#include "chessboard.h"
#include "piece.h"
#include "mygraphicsscene.h"

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
    ChessBoard *board;
    Piece *state[8][8];
    bool whitesTurn;
    void setupPieces();
    void TryMovePiece(Piece *p, Pos to);
};

#endif // CHESSGAME_H
