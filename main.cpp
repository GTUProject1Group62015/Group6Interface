#include "mainwindow.h"
#include <QApplication>
#include "icmekanbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /*icMekanButton a;

    a.show();*/
    return a.exec();
}
