#ifndef RULEMANAGER_H
#define RULEMANAGER_H
#include "piece.h"
#include "types.h"

class RuleManager
{
public:
    RuleManager();
    QVector<Pos> *getValidMoves(Piece *board[8][8], Piece *p);

private:
    QVector<Pos> *validMoves;
    Piece *state[8][8];
    void getPawnMoves(Piece *b[8][8], Piece *p);
    void getRookMoves(Piece *b[8][8], Piece *p);
    void getBishopMoves(Piece *b[8][8], Piece *p);
    void getKingMoves(Piece *b[8][8], Piece *p);
    void getQueenMoves(Piece *b[8][8], Piece *p);
    void getKnightMoves(Piece *b[8][8], Piece *p);
};

#endif // RULEMANAGER_H
