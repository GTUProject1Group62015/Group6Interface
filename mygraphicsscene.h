#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>

class myGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myGraphicsScene(QGraphicsScene *parent = 0);
    void mouseMoveEvent(QMouseEvent *event);

signals:

public slots:
};

#endif // MYGRAPHICSSCENE_H
