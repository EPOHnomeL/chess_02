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
    void getPawnMoves();
    void getRookMoves();
    void getBishopMoves();
    void getKingMoves();
    void getQueenMoves();
    void getKnightMoves();

};

#endif // RULEMANAGER_H