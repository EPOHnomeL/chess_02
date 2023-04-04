#ifndef CHECKMANAGER_H
#define CHECKMANAGER_H
#include "piece.h"
#include "types.h"
#include "rulemanager.h"
#include <QObject>

class CheckManager : public QObject
{
    Q_OBJECT
public:
    explicit CheckManager(QObject *parent = nullptr);
    QVector<Pos> *getValidMoves(Piece *b[8][8], Piece *p);
    bool checkFutureCheck(Piece *b[8][8], Piece *p, Pos to);
    bool checkCheckMate(Piece *b[8][8], bool color);

    RuleManager *getRm() const;

private:
    Piece *findKing(Piece *b[8][8], bool turn);
    Piece *attacker = nullptr;
    RuleManager *rm;
    Piece *prevPiece;
};

#endif // CHECKMANAGER_H
