#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_icmekan.h"
#include "icmekan.h"
#include "dismekan.h"
#include "ui_dismekan.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
