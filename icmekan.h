#ifndef ICMEKAN_H
#define ICMEKAN_H
#define MAXLINEPOSSIBILITY 50

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#ifdef _WIN64
#include <winsock2.h>
#include <windows.h>
#endif

#ifdef __gnu_linux__
#include <netdb.h>
#include <netinet/in.h>
#endif

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

/* server define*/

#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <iostream>
//#include <ws2spi.h>

#include "input.h"
#include <cstdio>

#define MAX_LINE 100
#define LINE_ARRAY_SIZE (MAX_LINE+1)

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

    void connectToServer();
    int socketDescriptor;
    ~IcMekan();

private slots:
    void on_pushButton_clicked();
    void update2();

    void on_deneme_clicked();

private:
    vector<Coor> NodeCoordinate;
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


    QTimer *time;

   /*for client-server*/

    char sendData[2];
    Input input_s;

    bool moving;
    //gidilmek istenen bolge
    int destinationRect;
    int StartRect;

};

#endif // ICMEKAN_H
