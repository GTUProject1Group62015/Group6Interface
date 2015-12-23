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

namespace Ui {
class disMekan;
}

class disMekan : public QDialog
{
    Q_OBJECT

public:
    explicit disMekan(QWidget *parent = 0);
    ~disMekan();

private slots:
    void on_pushButton_clicked();

    void on_bilMuhButton_clicked();

private:
    Ui::disMekan *dUi;
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
