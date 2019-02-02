#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>

class MyItem : public QGraphicsItem
{
public:
    MyItem();
    void advance(int phase);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setSpeed(int x,int y)
    {
        speed.setX(x);
        speed.setY(y);
    }
    void setColor(QColor value)
    {
        color=value;
    }


private:
    QColor color;
    QPointF speed;
    QPoint position;//初始位置


};

#endif // MYITEM_H
