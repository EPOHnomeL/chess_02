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
    QVector<Pos> *validMoves = new QVector<Pos>();
    QVector<Pos> *pieceMoves = rm->getValidMoves(b, p);
    for (int i = 0; i < pieceMoves->size(); i++)
    {
        if (!checkFutureCheck(b, p, pieceMoves->at(i)))
            validMoves->append(pieceMoves->at(i));
    }
    return validMoves;
}

bool CheckManager::checkFutureCheck(Piece *b[8][8], Piece *p, Pos to)
{
    Pos pos = p->getPos();
    Piece *king;
    if (p->getType() == "king")
    {
        king = p;
    }
    else
    {
        king = findKing(b, p->getColor());
    }
    prevPiece = b[to.x][to.y];
    b[to.x][to.y] = b[pos.x][pos.y];
    b[pos.x][pos.y] = nullptr;

    if (king == nullptr) // you got some problem then...
        return false;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (b[i][j] == nullptr)
                continue;
            if (b[i][j]->getColor() == king->getColor())
                continue;
            QVector<Pos> *pieceMoves = rm->getValidMoves(b, b[i][j]);
            if (p->getType() == "king")
            {
                if (pieceMoves->indexOf(to) != -1)
                {
                    attacker = b[i][j];
                    b[pos.x][pos.y] = b[to.x][to.y];
                    b[to.x][to.y] = prevPiece;
                    prevPiece = nullptr;
                    return true;
                }
            }
            else
            {
                if (pieceMoves->indexOf(king->getPos()) != -1)
                {
                    attacker = b[i][j];
                    b[pos.x][pos.y] = b[to.x][to.y];
                    b[to.x][to.y] = prevPiece;
                    prevPiece = nullptr;
                    return true;
                }
            }
        }
    }
    b[pos.x][pos.y] = b[to.x][to.y];
    b[to.x][to.y] = prevPiece;
    prevPiece = nullptr;
    return false;
}

bool CheckManager::checkCheckMate(Piece *b[8][8], bool color)
{
    QVector<Pos> *validMoves = new QVector<Pos>();
    QVector<Pos> *pieceMoves = new QVector<Pos>();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (b[i][j] == nullptr)
                continue;
            if (b[i][j]->getColor() != color)
                continue;
            delete pieceMoves;
            pieceMoves = getValidMoves(b, b[i][j]);
            for (int k = 0; k < pieceMoves->size(); k++)
            {
                if (!checkFutureCheck(b, b[i][j], pieceMoves->at(k)))
                    validMoves->append(pieceMoves->at(k));
            }
        }
    }
    return validMoves->size() == 0 ? true : false;
}

Piece *CheckManager::findKing(Piece *b[8][8], bool color)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (b[i][j] == nullptr)
                continue;
            if (b[i][j]->getType() == "king" && b[i][j]->getColor() == color)
                return b[i][j];
        }
    }
    return nullptr;
}
