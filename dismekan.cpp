#include "dismekan.h"
#include "ui_dismekan.h"
#include "Graph.h"
#include <QGraphicsItemGroup>
#include "icmekan.h"
#include "ui_icmekan.h"

#define PATH "C:/Users/test/Documents/Group6Interface/disMekanYeni.png"
#define DMWIDTH 5 // Destination Marker Width

disMekan::disMekan(QWidget *parent) :
    QDialog(parent),
    dUi(new Ui::disMekan)
{
    dUi->setupUi(this);

    scene = new QGraphicsScene(this);

    dUi->disMapView->setScene(scene);

    // Add Map First
    planPixmap = scene -> addPixmap(QPixmap(PATH));
    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);
    blackPen.setWidth(6);

    destinationMarker = scene -> addEllipse(0,0,DMWIDTH,DMWIDTH,blackPen,redBrush);
    destinationMarker->setFlag(QGraphicsItem::ItemIsMovable);


}

disMekan::~disMekan()
{
    delete dUi;
}

void disMekan::on_pushButton_clicked()
{
    //destinationVertex->setVertex(destinationMarker->pos().x() + DMWIDTH/2, destinationMarker->pos().y() + DMWIDTH/2);
    //locationVertex->setVertex(locationMarker->pos().x() + 10, locationMarker->pos().y());
    //dUi->label->setText("destination vertex = " + QString::number(destinationVertex->getX()) + ", " + QString::number(destinationVertex->getY()));
    dUi->label->setText("x: " + QString::number(destinationMarker->pos().x()) +"y: " + QString::number(destinationMarker->pos().y()));

}


void disMekan::on_bilMuhButton_clicked()
{
    dUi->label->setText("Bilmuh");
    IcMekan *icmekanUi = new IcMekan(this);
    icmekanUi->exec();
}

void disMekan::mouseReleaseEvent ( QGraphicsSceneMouseEvent  * event )
{
  /*if(event->GraphicsSceneMousePress)
  {
      dUi->label->setText("Booo");
  }*/

  /*if(event->button() == Qt::LeftButton)
  {
       dUi->label->setText("Left Button Clicked");
  }*/

    dUi->label->setText("Left Button Clicked");
}

/*void QGraphicsView::mousePressEvent(QMouseEvent *event)
{
    disMekan::dUi->label->setText("Left Button Clicked");
}*/

