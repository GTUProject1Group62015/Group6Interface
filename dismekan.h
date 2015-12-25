#ifndef DISMEKAN_H
#define DISMEKAN_H

#include <QDialog>
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsPixmapItem>
#include "Vertex.h"
#include "Graph.h"
#include <QPainter>
#include "Area.h"
#include <QMouseEvent>


namespace Ui {
class disMekan;
//class MyGraphicsScene;
}



/*class MyGraphicsScene : public QGraphicsScene
{
   Q_OBJECT

public:
   explicit MyGraphicsScene(QGraphicsScene *parent = 0);
   void mouseMoveEvent(QMouseEvent *event);
   ~MyGraphicsScene();
};*/


class disMekan : public QDialog
{
    Q_OBJECT

public:
    explicit disMekan(QWidget *parent = 0);
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
    Ui::disMekan *dUi;
    ~disMekan();


private slots:
    void on_pushButton_clicked();

    void on_bilMuhButton_clicked();

private:

    QGraphicsPixmapItem *planPixmap;
    QGraphicsScene *scene;


    QGraphicsEllipseItem *destinationMarker;
    QGraphicsPolygonItem *locationMarker;
    QGraphicsEllipseItem *nodeLocationsMarker;
    QList<QGraphicsItem *> drawedLines;

    Graph g;
    Vertex *locationVertex;
    Vertex *destinationVertex;

};

#endif // DISMEKAN_H
