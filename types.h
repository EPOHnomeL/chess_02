#ifndef TYPES_H
#define TYPES_H

#include <QString>

struct Pos
{
    int x, y;
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
