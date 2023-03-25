#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsView>
#include <QLayout>
#include <QGraphicsRectItem>
#include "mygraphicsscene.h"

class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget *parent = nullptr);
    QGraphicsPixmapItem *putPieceAt(QString piece, Pos pos);

    MyGraphicsScene *getScene() const;

private:
    const QColor colors[2] = {QColor(121, 72, 57), QColor(93, 50, 49)};

    QLabel *label;
    QLayout *layout;
    QGraphicsView *view;
    MyGraphicsScene *scene;
    QGraphicsRectItem *squares[8][8];
    QGraphicsTextItem *text[8][2];

    void init();

};

#endif // CHESSBOARD_H
