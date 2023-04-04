#include "piece.h"

Piece::Piece(QString type, Pos pos, bool color, QGraphicsPixmapItem *png)
{
    this->type = type;
    this->pos = pos;
    this->color = color;
    this->png = png;
}

Piece::~Piece()
{
    png->~QGraphicsPixmapItem();
}

Pos Piece::getPos()
{
    return pos;
}

void Piece::setPos(Pos newPos)
{
    pos = newPos;
    png->setPos(17 + (pos.y * 100), 13 + (pos.x * 100));
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
