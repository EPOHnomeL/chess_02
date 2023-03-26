#include "rulemanager.h"
#include <QDebug>

RuleManager::RuleManager()
{
}

QVector<Pos> *RuleManager::getValidMoves(Piece *board[8][8], Piece *p)
{
    validMoves = new QVector<Pos>();
    int n = 0;
    for (int i = 0; i < 6; i++)
        if (piecesNames[i] == p->getType()){
            n = i;
            break;
        }
    switch (n)
    {
    case 0:
        getPawnMoves(board, p);
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

    // Restrict valid moves on th board i.e. white and black pieces
    return validMoves;
}

void RuleManager::getPawnMoves(Piece *b[8][8], Piece *p)
{
    Pos pos = p->getPos();
    if(p->getColor() == true)
    {
        if(pos.x == 6)
        {
            if(b[pos.x-1][pos.y] == nullptr)
                validMoves->append((Pos){pos.x-1, pos.y});
            if(b[pos.x-2][pos.y] == nullptr)
                validMoves->append((Pos){pos.x-2, pos.y});
        } else
        {
            if(pos.x == 0)
            {
                // Promote pawn!
            } else
            {
                if(b[pos.x-1][pos.y] == nullptr)
                    validMoves->append((Pos){pos.x-1, pos.y});
            }
        }
        Pos d1 = {pos.x-1, pos.y-1};
        Pos d2 = {pos.x-1, pos.y+1};

        if(b[d1.x][d1.y] != nullptr)
            if(b[d1.x][d1.y]->getColor() == false)
            {
                validMoves->append(d1);
            }
        if(b[d2.x][d2.y] != nullptr)
            if(b[d2.x][d2.y]->getColor() == false)
            {
                validMoves->append(d2);
            }
    }else
    {
        if(pos.x == 1)
        {
            if(b[pos.x+1][pos.y] == nullptr)
                validMoves->append((Pos){pos.x+1, pos.y});
            if(b[pos.x+2][pos.y] == nullptr)
                validMoves->append((Pos){pos.x+2, pos.y});
        } else
        {
            if(pos.x == 7)
            {
                // Promote pawn!
            } else
            {
                if(b[pos.x+1][pos.y] == nullptr)
                    validMoves->append((Pos){pos.x+1, pos.y});
            }
        }
        Pos d1 = {pos.x+1, pos.y-1};
        Pos d2 = {pos.x+1, pos.y+1};

        if(b[d1.x][d1.y] != nullptr)
            if(b[d1.x][d1.y]->getColor() == true)
            {
                validMoves->append(d1);
            }
        if(b[d2.x][d2.y] != nullptr)
            if(b[d2.x][d2.y]->getColor() == true)
            {
                validMoves->append(d2);
            }
    }
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
