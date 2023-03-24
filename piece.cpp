#include "piece.h"

Piece::Piece(QString type, Pos pos, bool color, QGraphicsPixmapItem *png)
{
    this->type = type;
    this->pos = pos;
    this->color = color;
    this->png = png;
}

const Pos &Piece::getPos() const
{
    return pos;
}

void Piece::setPos(const Pos &newPos)
{
    pos = newPos;
}

bool Piece::getColor() const
{
    return color;
}

const QString &Piece::getType() const
{
    return type;
}

QGraphicsPixmapItem *Piece::getPng() const
{
    return png;
}

void Piece::clearPng()
{
    png = nullptr;
}
