#include "icmekanbutton.h"
#include "ui_icmekanbutton.h"
#include <iostream>

icMekanButton::icMekanButton(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::icMekanButton)
{

    ui->setupUi(this);
    array.push_back(ui->pushButton);

    array.at(0)->setAutoFillBackground(true);

    array.at(0)->setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
    std::cerr<<array.at(0)->x();
    //array.at(0)->styleSheet("background-color: rgba(255, 255, 255, 70) color: rgba(255, 255, 255,0)");



}

icMekanButton::~icMekanButton()
{
    delete ui;
}
