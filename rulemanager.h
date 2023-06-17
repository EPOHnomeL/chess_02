#ifndef RULEMANAGER_H
#define RULEMANAGER_H
#include "piece.h"
#include "types.h"
#include <QObject>

class RuleManager : public QObject
{
    Q_OBJECT
public:
    explicit RuleManager(QObject *parent = nullptr);
    QVector<Pos> *getValidMoves(Piece *board[8][8], Piece *p);
    bool canCastle[2];

signals:

    void promotePawn(Pos pos);

private:
    QVector<Pos> *validMoves;
    void getPawnMoves(Piece *b[8][8], Piece *p);
    void getRookMoves(Piece *b[8][8], Piece *p);
    void getBishopMoves(Piece *b[8][8], Piece *p);
    void getKingMoves(Piece *b[8][8], Piece *p);
    void getQueenMoves(Piece *b[8][8], Piece *p);
    void getKnightMoves(Piece *b[8][8], Piece *p);
};

#endif // RULEMANAGER_H
