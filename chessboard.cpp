#include "chessboard.h"

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    scene = new MyGraphicsScene();
    view = new QGraphicsView(this);
    layout = new QGridLayout(this);
    label = new QLabel(this);

    layout->addWidget(view);
    layout->addWidget(label);

    this->setLayout(layout);
    view->setScene(scene);

    init();

    view->setFixedSize(802, 803);
    view->show();
}

void ChessBoard::init()
{
    scene->clear();
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            squares[i][j] = new QGraphicsRectItem(i * 100, j * 100, 100, 100);
            squares[i][j]->setPen(Qt::NoPen);
            squares[i][j]->setBrush(QBrush(((i + j) % 2 == 0) ? colors[0]: colors[1]));
            scene->addItem(squares[i][j]);
            if (j == 0)
            {
                text[i][0] = scene->addText(QString::number(8 - i));
                text[i][0]->setPos(2, 100 * (i));
            }
        }
        if (i == 7)
        {
            for (int k = 0; k < 8; ++k)
            {
                text[k][1] = scene->addText(QString(QChar(k + 65)));
                text[k][1]->setPos(100 * (k) + 3, 100 * i + 79);
            }
        }
    }
}

QGraphicsPixmapItem* ChessBoard::putPieceAt(QString piece, Pos pos)
{
    QImage *image = new QImage(":img/" + piece + ".png");
    QPixmap p = QPixmap::fromImage(*image).scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *png = scene->addPixmap(p); // Add pointer to array
    png->setPos(17 + (pos.y * 100), 13 + (pos.x * 100));
    return png;
}

MyGraphicsScene *ChessBoard::getScene() const
{
    return scene;
}
