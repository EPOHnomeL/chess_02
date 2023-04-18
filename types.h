#ifndef TYPES_H
#define TYPES_H

#include <QString>

struct Pos
{
    int x, y;
    bool operator==(const Pos &a)
    {
        if (x == a.x && y == a.y)
            return true;
        else
            return false;
    }
    QString toString(){
        return QString(char((y)+97)) + char((8-x)+48);
    }
};

struct Move
{
    Pos from;
    Pos to;
    QString toJsonString(){
        return QString("{\"from\":\"%1\",\"to\":\"%2\"}").arg(from.toString()).arg(to.toString());
    }
};

const QString piecesNames[6] =
    {
        "pawn",
        "rook",
        "bishop",
        "knight",
        "queen",
        "king"};

const QString w_starting[2][8] = {
    {"pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn"},
    {"rook", "knight", "bishop", "queen", "king", "bishop", "knight", "rook"}};

const QString b_starting[2][8] = {
    {"rook", "knight", "bishop", "queen", "king", "bishop", "knight", "rook"},
    {"pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn", "pawn"}};

#endif // TYPES_H
