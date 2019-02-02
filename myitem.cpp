#include "myitem.h"
#include <QPainter>
#include <QApplication>
#include <QTime>
#include <QDebug>
#include <math.h>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPainterPath>
#include <QPainter>

MyItem::MyItem()//构造函数
{

}

QRectF MyItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(position.x() - penWidth/2, position.y() - penWidth/2, 20 + penWidth, 20 + penWidth);
}
void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(color);
    painter->drawEllipse(position.x(), position.y(), 20, 20);

}

QPointF changedSpeed(QPointF speed,QRectF rect,QPointF p1,QPointF j_p1,QPointF j_p2)
{
    //qDebug() <<"speed1:"<<speed<<endl;
    float k;
    float x1=speed.x();
    float y1=speed.y();
    if(j_p1.x()==-0.5&&j_p1.y()==-0.5)//跟球碰撞的情况
    {
        /*qDebug()<<rect<<endl;
        float x0=p1.x();
        float y0=p1.y();
        float x2=rect.x()+rect.width()/2.0;
        float y2=rect.y()+rect.height()/2.0;
        qDebug()<<x0<<","<<y0<<endl;
        qDebug()<<x2<<","<<y2<<endl;
        k=(x2-x0)/(y0-y2);
        qDebug()<<"k:"<<k<<endl;*/return -speed;
    }
    else//跟墙碰撞的情况
    {
        k=(j_p1.y()-j_p2.y())/(j_p1.x()-j_p2.x());
    }
    float xp=(2*k*y1+x1-k*k*x1)/(1+k*k);
    float yp=(2*k*x1+k*k*y1-y1)/(1+k*k);

    QPointF changedspeed;
    changedspeed.setX(xp);
    changedspeed.setY(yp);

    //qDebug() <<"speed2:"<<changedspeed<<endl;
    return changedspeed;

}
void MyItem::advance(int phase)
{
    //if(!phase)
    //    return ;

    if(!collidingItems().isEmpty())//如果碰撞
    {
        QPointF speed2=changedSpeed(speed,
                                    collidingItems().first()->sceneBoundingRect(),
                                    QPointF(x()+10,y()+10),
                                    collidingItems().first()->shape().elementAt(0),
                                    collidingItems().first()->shape().elementAt(1));

        //qDebug() <<"boundingRect():"<<collidingItems().first()->boundingRect()<<endl;
        //qDebug() <<"matrix():"<<collidingItems().first()->matrix()<<endl;
        //qDebug() <<"sceneBoundingRect():"<<collidingItems().first()->sceneBoundingRect()<<endl;
        //qDebug() <<"scenePos():"<<collidingItems().first()->scenePos()<<endl;
        speed.setX(speed2.x());
        speed.setY(speed2.y());
    }
    int value = qrand()%100;
    int rand_level=3;
    if(value<25)
    {
        moveBy(qrand()%rand_level,qrand()%rand_level);
    }
    else if(value<50)
    {
        moveBy(-qrand()%rand_level,-qrand()%rand_level);
    }
    else if(value<75)
    {
        moveBy(-qrand()%rand_level,qrand()%rand_level);
    }
    else
    {
        moveBy(qrand()%rand_level,-qrand()%rand_level);
    }
    moveBy(speed.x(),speed.y());
    if(x()<=10||x()>=scene()->width()-30)
    {
        speed.setX(-speed.x());
    }
    if(y()<=5||y()>=scene()->height()-20)
    {
        speed.setY(-speed.y());
    }
}

