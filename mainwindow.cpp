#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_icmekan.h"
#include "icmekan.h"
#include "dismekan.h"
#include "ui_dismekan.h"
#include "icmekanbutton.h"

#define PATH "C:/Users/test/Documents/Github/Group6Interface/indir.jpg"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene -> addPixmap(QPixmap(PATH));

    ui->graphicsView->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_icMekanButton_clicked()
{
    IcMekan *icmekanUi = new IcMekan(this);
    icmekanUi->exec();

}

void MainWindow::on_disMekanButton_clicked()
{
    disMekan *disMekanUi = new disMekan(this);
    disMekanUi->exec();
}

void MainWindow::on_pushButton_clicked()
{
    icMekanButton *icMekanUi = new icMekanButton(this);
    icMekanUi->showMaximized();
}
