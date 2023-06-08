#include "chessboard.h"

ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    scene = new MyGraphicsScene();
    view = new QGraphicsView(this);
    layout = new QGridLayout(this);
    layout->addWidget(view);
    this->setLayout(layout);
    view->setScene(scene);

    init();

    view->setFixedSize(802, 803);
    view->setMinimumSize(802, 803);
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
            squares[i][j]->setBrush(QBrush(((i + j) % 2 == 0) ? colors[0] : colors[1]));
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

QGraphicsPixmapItem *ChessBoard::putPieceAt(QString piece, Pos pos)
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

void ChessBoard::SetInfoText(QString s)
{
    label->setText(s);
}

void ChessBoard::changeSquaresColors()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            QString s = squares[i][j]->brush().color().name();
            s.remove('#');
            bool bStatus = false;
            uint64_t val = s.toUInt(&bStatus, 16);
            squares[i][j]->setBrush(QBrush(val + 1));
        }
    }
}

void ChessBoard::setSquaresColors()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            squares[i][j]->setBrush(QBrush((rand()*rand()*rand())));
        }
    }
}

void ChessBoard::toggleSquare(Pos _pos, bool isSelect)
{
    Pos pos = {_pos.y, _pos.x};
    if (!isSelect)
    {
        if (squares[pos.x][pos.y]->brush().color() == active[0] || squares[pos.x][pos.y]->brush().color() == active[1])
        {
            squares[pos.x][pos.y]->setBrush(QBrush(((pos.x + pos.y) % 2 == 0) ? colors[0] : colors[1]));
        }
        else
        {
            squares[pos.x][pos.y]->setBrush(QBrush(((pos.x + pos.y) % 2 == 0) ? active[0] : active[1]));
        }
    }
    else
    {
        if (squares[pos.x][pos.y]->brush().color() == select)
        {
            squares[pos.x][pos.y]->setBrush(QBrush(((pos.x + pos.y) % 2 == 0) ? colors[0] : colors[1]));
        }
        else
        {
            squares[pos.x][pos.y]->setBrush(QBrush(select));
        }
    }
}
