#include "checkmanager.h"
#include <QDebug>

CheckManager::CheckManager(QObject *parent) : QObject(parent)
{
    rm = new RuleManager();
    prevPiece = nullptr;
    attacker = nullptr;
}

QVector<Pos> *CheckManager::getValidMoves(Piece *b[8][8], Piece *p)
{
    QVector<Pos>* validMoves = new QVector<Pos>();
    QVector<Pos>* pieceMoves = rm->getValidMoves(b, p);
    for(int i=0; i<pieceMoves->size(); i++){
        if(!checkFutureCheck(b, p, pieceMoves->at(i)))
            validMoves->append(pieceMoves->at(i));
    }
    return validMoves;
}

bool CheckManager::checkCheck(Piece *b[8][8], bool turn)
{
    const Piece* king = findKing(b, turn);
    if(king == nullptr)     // you got some problem then...
        return false;

    for(int i=0; i<8;i++){
        for(int j=0; j<8; j++){
            if(b[i][j] == nullptr)
                continue;
            if(b[i][j]->getColor() == king->getColor()){
                continue;
            }

            if(rm->getValidMoves(b, b[i][j])->indexOf(king->getPos()) != -1)
            {
                attacker = b[i][j];
                return true;
            }
        }
    }
    return false;
}

bool CheckManager::checkFutureCheck(Piece *b[8][8], Piece *p, Pos to)
{
    Pos pos = p->getPos();
    prevPiece = b[to.x][to.y];
    b[to.x][to.y] = b[pos.x][pos.y];
    b[pos.x][pos.y] = nullptr;

    const Piece* king = findKing(b, p->getColor());

    if(king == nullptr)     // you got some problem then...
        return false;
    for(int i=0; i<8;i++){
        for(int j=0; j<8; j++){
            if(b[i][j] == nullptr)
                continue;
            if(b[i][j]->getColor() == king->getColor())
                continue;
            if(rm->getValidMoves(b, b[i][j])->indexOf(king->getPos()) != -1)
            {
                attacker = b[i][j];
                b[pos.x][pos.y] = b[to.x][to.y];
                b[to.x][to.y] = prevPiece;
                prevPiece = nullptr;
                return true;
            }
        }
    }
    b[pos.x][pos.y] = b[to.x][to.y];
    b[to.x][to.y] = prevPiece;
    prevPiece = nullptr;
    return false;
}

Piece* CheckManager::findKing(Piece *b[8][8], bool color)
{
    for(int i=0; i<8;i++){
        for(int j=0; j<8; j++){
            if(b[i][j] == nullptr)
                continue;
            if(b[i][j]->getType() == "king" && b[i][j]->getColor() == color)
                return b[i][j];
        }
    }
    return nullptr;
}
