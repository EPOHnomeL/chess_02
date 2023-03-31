#include "rulemanager.h"
#include <QDebug>
#include <math.h>

RuleManager::RuleManager()
{
}

QVector<Pos> *RuleManager::getValidMoves(Piece *board[8][8], Piece *p)
{
    validMoves = new QVector<Pos>();
    int n = 0;
    for (int i = 0; i < 6; i++)
        if (piecesNames[i] == p->getType())
        {
            n = i;
            break;
        }

    switch (n)
    {
    case 0:
        getPawnMoves(board, p);
        break;
    case 1:
        getRookMoves(board, p);
        break;
    case 2:
        getBishopMoves(board, p);
        break;
    case 3:
        getKnightMoves(board, p);
        break;
    case 4:
        getQueenMoves(board, p);
        break;
    case 5:
        getKingMoves(board, p);
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
    if (p->getColor() == true)
    {
        if (pos.x == 6)
        {
            if (b[pos.x - 1][pos.y] == nullptr)
                validMoves->append((Pos){pos.x - 1, pos.y});
            if (b[pos.x - 2][pos.y] == nullptr)
                validMoves->append((Pos){pos.x - 2, pos.y});
        }
        else
        {
            if (pos.x == 0)
            {
                // Promote pawn!
            }
            else
            {
                if (b[pos.x - 1][pos.y] == nullptr)
                    validMoves->append((Pos){pos.x - 1, pos.y});
            }
        }
        Pos d1 = {pos.x - 1, pos.y - 1};
        Pos d2 = {pos.x - 1, pos.y + 1};

        if (b[d1.x][d1.y] != nullptr)
            if (b[d1.x][d1.y]->getColor() == false)
            {
                validMoves->append(d1);
            }
        if (b[d2.x][d2.y] != nullptr)
            if (b[d2.x][d2.y]->getColor() == false)
            {
                validMoves->append(d2);
            }
    }
    else
    {
        if (pos.x == 1)
        {
            if (b[pos.x + 1][pos.y] == nullptr)
                validMoves->append((Pos){pos.x + 1, pos.y});
            if (b[pos.x + 2][pos.y] == nullptr)
                validMoves->append((Pos){pos.x + 2, pos.y});
        }
        else
        {
            if (pos.x == 7)
            {
                // Promote pawn!
            }
            else
            {
                if (b[pos.x + 1][pos.y] == nullptr)
                    validMoves->append((Pos){pos.x + 1, pos.y});
            }
        }
        Pos d1 = {pos.x + 1, pos.y - 1};
        Pos d2 = {pos.x + 1, pos.y + 1};

        if (b[d1.x][d1.y] != nullptr)
            if (b[d1.x][d1.y]->getColor() == true)
            {
                validMoves->append(d1);
            }
        if (b[d2.x][d2.y] != nullptr)
            if (b[d2.x][d2.y]->getColor() == true)
            {
                validMoves->append(d2);
            }
    }
}

void RuleManager::getRookMoves(Piece *b[8][8], Piece *p)
{
    Pos pos = p->getPos();
    for (int up = pos.y + 1; up < 8; up++)
    {
        if (b[pos.x][up] != nullptr)
        {
            if (b[pos.x][up]->getColor() == p->getColor())
            {
                break;
            }
            else
            {
                validMoves->append({pos.x, up});
                break;
            }
        }
        validMoves->append({pos.x, up});
    }

    for (int down = pos.y - 1; down >= 0; down--)
    {
        if (b[pos.x][down] != nullptr)
        {
            if (b[pos.x][down]->getColor() == p->getColor())
            {
                break;
            }
            else
            {
                validMoves->append({pos.x, down});
                break;
            }
        }
        validMoves->append({pos.x, down});
    }

    for (int left = pos.x + 1; left < 8; left++)
    {
        if (b[left][pos.y] != nullptr)
        {
            if (b[left][pos.y]->getColor() == p->getColor())
            {
                break;
            }
            else
            {
                validMoves->append({left, pos.y});
                break;
            }
        }
        validMoves->append({left, pos.y});
    }

    for (int right = pos.x - 1; right >= 0; right--)
    {
        if (b[right][pos.y] != nullptr)
        {
            if (b[right][pos.y]->getColor() == p->getColor())
            {
                break;
            }
            else
            {
                validMoves->append({right, pos.y});
                break;
            }
        }
        validMoves->append({right, pos.y});
    }
}

void RuleManager::getBishopMoves(Piece *b[8][8], Piece *p)
{
    Pos pos = p->getPos();
    for (int ne = 1; ne < 8; ne++)
    {
        if ((pos.x + ne >= 8) || (pos.y + ne >= 8))
            break;

        if (b[pos.x + ne][pos.y + ne] != nullptr)
        {
            if (b[pos.x + ne][pos.y + ne]->getColor() == p->getColor())
            {
                break;
            }
            else
            {
                validMoves->append({pos.x + ne, pos.y + ne});
                break;
            }
        }
        validMoves->append({pos.x + ne, pos.y + ne});
    }

    for (int sw = 1; sw < 8; sw++)
    {
        if ((pos.x - sw < 0) || (pos.y - sw < 0))
            break;

        if (b[pos.x - sw][pos.y - sw] != nullptr)
        {
            if (b[pos.x - sw][pos.y - sw]->getColor() == p->getColor())
            {
                break;
            }
            else
            {
                validMoves->append({pos.x - sw, pos.y - sw});
                break;
            }
        }
        validMoves->append({pos.x - sw, pos.y - sw});
    }

    for (int nw = 1; nw < 8; nw++)
    {
        if ((pos.x - nw < 0) || (pos.y + nw >= 8))
            break;
        if (b[pos.x - nw][pos.y + nw] != nullptr)
        {
            if (b[pos.x - nw][pos.y + nw]->getColor() == p->getColor())
            {
                break;
            }
            else
            {
                validMoves->append({pos.x - nw, pos.y + nw});
                break;
            }
        }
        validMoves->append({pos.x - nw, pos.y + nw});
    }

    for (int se = 1; se < 8; se++)
    {
        if ((pos.x + se >= 8) || (pos.y - se < 0))
            break;
        if (b[pos.x + se][pos.y - se] != nullptr)
        {
            if (b[pos.x + se][pos.y - se]->getColor() == p->getColor())
            {
                break;
            }
            else
            {
                validMoves->append({pos.x + se, pos.y - se});
                break;
            }
        }
        validMoves->append({pos.x + se, pos.y - se});
    }
}

void RuleManager::getKingMoves(Piece *b[8][8], Piece *p)
{
    Pos pos = p->getPos();
    for (int i = pos.x - 1; i < 2 + pos.x; i++)
    {
        if (i < 0 || i > 7)
            continue;
        for (int j = pos.y - 1; j < 2 + pos.y; j++)
        {
            if (j < 0 || j > 7)
                continue;
            if (b[i][j] == nullptr)
            {
                validMoves->append({i, j});
            }
            else
            {
                if (b[i][j]->getColor() == p->getColor())
                {
                    continue;
                }
                else
                {
                    validMoves->append({i, j});
                }
            }
        }
    }
    // Add castling...
}

void RuleManager::getQueenMoves(Piece *b[8][8], Piece *p)
{
    getRookMoves(b, p);
    getBishopMoves(b, p);
}

void RuleManager::getKnightMoves(Piece *b[8][8], Piece *p)
{
    Pos pos = p->getPos();
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            int x = abs(pos.x - i);
            int y = abs(pos.y - j);
            if (x * y == 2)
            {
                if (b[i][j] == nullptr)
                {
                    validMoves->append({i, j});
                    continue;
                }
                if (b[i][j]->getColor() != p->getColor())
                    validMoves->append({i, j});
            }
        }
    }
}
