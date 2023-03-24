#include "mygraphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <QString>

MyGraphicsScene::MyGraphicsScene(QObject *parent) : QGraphicsScene(parent)
{
}

MyGraphicsScene::~MyGraphicsScene()
{
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    if (mouseEvent->button() == Qt::LeftButton)
    {
        int irow = (int)mouseEvent->scenePos().y() / 100;
        int icol = (int)mouseEvent->scenePos().x() / 100;
        emit MyGraphicsScene::userClick({irow, icol});
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}
