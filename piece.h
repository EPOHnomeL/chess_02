#ifndef PIECE_H
#define PIECE_H
#include "types.h"
#include <QGraphicsPixmapItem>

class Piece
{
public:
    Piece(QString type, Pos pos, bool color, QGraphicsPixmapItem *png);
    ~Piece();
    Pos getPos();
    void setPos(Pos newPos);
    bool getColor() const;
    const QString &getType() const;

    QGraphicsPixmapItem *getPng() const;
    void clearPng();

private:
    Pos pos;
    bool color;
    QString type;
    QGraphicsPixmapItem *png;
};

#endif // PIECE_H
