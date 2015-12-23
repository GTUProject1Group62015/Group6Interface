#include "dismekan.h"
#include "ui_dismekan.h"
#include "Graph.h"
#include <QGraphicsItemGroup>
#include "icmekan.h"
#include "ui_icmekan.h"

#define PATH "C:/Users/test/Documents/Group6Interface/disMekanYeni.png"

disMekan::disMekan(QWidget *parent) :
    QDialog(parent),
    dUi(new Ui::disMekan)
{
    dUi->setupUi(this);

    scene = new QGraphicsScene(this);

    dUi->disMapView->setScene(scene);

    // Add Map First
    planPixmap = scene -> addPixmap(QPixmap(PATH));
}

disMekan::~disMekan()
{
    delete dUi;
}

void disMekan::on_pushButton_clicked()
{
    dUi->label->setText("aAAAAAs");
}


void disMekan::on_bilMuhButton_clicked()
{
    dUi->label->setText("Bilmuh");
    IcMekan *icmekanUi = new IcMekan(this);
    icmekanUi->exec();
}
