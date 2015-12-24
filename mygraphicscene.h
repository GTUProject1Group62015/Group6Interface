#ifndef MYGRAPHICSCENE_H
#define MYGRAPHICSCENE_H


class myGraphicScene : public QGraphicsView
{
Q_OBJECT

protected:
   void mouseMoveEvent(QMouseEvent *event);
public:
    myGraphicScene();
};

#endif // MYGRAPHICSCENE_H
