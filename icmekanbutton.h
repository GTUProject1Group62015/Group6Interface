#ifndef ICMEKANBUTTON_H
#define ICMEKANBUTTON_H

#include <QMainWindow>
#include <QList>
#include <QPushButton>

namespace Ui {
class icMekanButton;
}

class icMekanButton : public QMainWindow
{
    Q_OBJECT

public:
    explicit icMekanButton(QWidget *parent = 0);
    ~icMekanButton();

private:
    QList<QPushButton*> array;

    Ui::icMekanButton *ui;
};

#endif // ICMEKANBUTTON_H
