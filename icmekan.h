#ifndef ICMEKAN_H
#define ICMEKAN_H
#define MAXLINEPOSSIBILITY 50


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
class IcMekan;
}

class IcMekan : public QDialog
{
    Q_OBJECT

public:
    int FindArea();
    void seekLocation(); // Get User Location from hardware
    void clearLines(); // Clear all drawed lines
    QGraphicsLineItem *drawLine(Vertex &c1, Vertex &c2, QPen pen); // Draw A line between 2 coordinates
    explicit IcMekan(QWidget *parent = 0);
    ~IcMekan();

private slots:
    void on_pushButton_clicked();

private:
    vector<Area> colorAreaPoint;
    Ui::IcMekan *Iui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *destinationMarker;
    QGraphicsPolygonItem *locationMarker;
    QGraphicsEllipseItem *nodeLocationsMarker;
    QList<QGraphicsItem *> drawedLines;
    QGraphicsPixmapItem *planPixmap;
    Graph g;
    Vertex *locationVertex;
    Vertex *destinationVertex;

    int xTransRect=0;
    int yTransRect=0;
    int widthTransRect=0;
    int heightTransRect=0;
    QRect rect;

};

#endif // ICMEKAN_H
