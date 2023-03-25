#include "rulemanager.h"
#include <QDebug>

RuleManager::RuleManager()
{
}

QVector<Pos> *RuleManager::getValidMoves(Piece *board[8][8], Piece *p)
{
    validMoves = nullptr;
    int n = 0;
    for (int i = 0; i < 6; i++)
        if (piecesNames[i] == p->getType())
            n = i;
    switch (n)
    {
    case 0:
        getPawnMoves();
        break;
    case 1:
        getRookMoves();
        break;
    case 2:
        getBishopMoves();
        break;
    case 3:
        getKnightMoves();
        break;
    case 4:
        getQueenMoves();
        break;
    case 5:
        getKingMoves();
        break;
    default:
        break;
    }
    return validMoves;
}

void RuleManager::getPawnMoves()
{

}

void RuleManager::getRookMoves()
{

}

void RuleManager::getBishopMoves()
{

}

void RuleManager::getKingMoves()
{

}

void RuleManager::getQueenMoves()
{

}

void RuleManager::getKnightMoves()
{

}
