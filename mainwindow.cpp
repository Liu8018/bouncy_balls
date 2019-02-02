#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "myitem.h"
#include <QTime>
#include <QDebug>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QMouseEvent>
#include <QCheckBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //newWall->hide();

    scene1->setSceneRect(0,0,ui->graphicsView->width(),ui->graphicsView->height());
    ui->graphicsView->setScene(scene1);
    ui->graphicsView->setForegroundBrush(QColor(255,255,255,0));
    QPixmap backgroundImg("/usr/share/backgrounds/Flying_Whale_by_Shu_Le.jpg");
    backgroundImg.scaled(QSize(ui->graphicsView->width(),ui->graphicsView->height()));
    ui->graphicsView->setBackgroundBrush(backgroundImg);

    QObject::connect(timer,SIGNAL(timeout()),scene1,SLOT(advance()));
    QObject::connect(ui->run_stop_pushButton,SIGNAL(clicked(bool)),this,SLOT(on_run_stop_pushButton_toggled(bool)));
    timer->start(1000/(float)ui->spinBox->value());

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(myupdate()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_run_stop_pushButton_toggled(bool)
{
    if(timer->isActive())
        timer->stop();
    else
        timer->start();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->spinBox->setValue(value);
    timer->start(1000/(float)value);
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->horizontalSlider->setValue(arg1);
    timer->start(1000/(float)arg1);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton//如果鼠标按下的是左键
            &&event->pos().x()-ui->graphicsView->pos().x()>0
            &&event->pos().y()-ui->graphicsView->pos().y()>0
            &&event->pos().x()-ui->graphicsView->pos().x()<ui->graphicsView->width()
            &&event->pos().y()-ui->graphicsView->pos().y()<ui->graphicsView->height())
    {
        if(ui->add_wall_checkBox->isChecked())
        {
            wall_start_point.setX(event->pos().x()-ui->graphicsView->pos().x());
            wall_start_point.setY(event->pos().y()-ui->graphicsView->pos().y());
            scene1->addItem(newWall);
        }
        else if(ui->add_ball_checkBox->isChecked())
        {
            MyItem * newBall = new MyItem;
            newBall->setPos(event->pos().x()-ui->graphicsView->pos().x(),event->pos().y()-ui->graphicsView->pos().y());
            newBall->setSpeed(qrand()%20-qrand()%20,qrand()%20-qrand()%20);
            newBall->setColor(QColor(qrand()%255,qrand()%255,qrand()%255));
            scene1->addItem(newBall);
            ball_num++;
        }
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton//如果鼠标按下的是左键
            &&event->pos().x()-ui->graphicsView->pos().x()>0
            &&event->pos().y()-ui->graphicsView->pos().y()>0
            &&event->pos().x()-ui->graphicsView->pos().x()<ui->graphicsView->width()
            &&event->pos().y()-ui->graphicsView->pos().y()<ui->graphicsView->height())
    {
        if(ui->add_wall_checkBox->isChecked())
        {
            newWall->show();
            newWall->setLine(QLine(wall_start_point.x(),wall_start_point.y(),event->pos().x()-ui->graphicsView->pos().x(),event->pos().y()-ui->graphicsView->pos().y()));
        }
        else if(ui->add_ball_checkBox->isChecked())
        {

        }
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(ui->add_wall_checkBox->isChecked())
    {
        newWall->hide();
        ui->graphicsView->scene()->removeItem(newWall);
        wall_end_point.setX(event->pos().x()-ui->graphicsView->pos().x());
        wall_end_point.setY(event->pos().y()-ui->graphicsView->pos().y());
        QGraphicsLineItem * realNewWall = new QGraphicsLineItem;
        realNewWall->setLine(wall_start_point.x(),wall_start_point.y(),wall_end_point.x(),wall_end_point.y());
        realNewWall->setPen(QPen(Qt::green,5));
        scene1->addItem(realNewWall);
        wall_num++;
    }
    else if(ui->add_ball_checkBox->isChecked())
    {

    }
}

void MainWindow::on_add_wall_checkBox_stateChanged(int )
{
    if(ui->add_wall_checkBox->isChecked())
        ui->add_ball_checkBox->setChecked(false);
}

void MainWindow::on_add_ball_checkBox_stateChanged(int )
{
    if(ui->add_ball_checkBox->isChecked())
        ui->add_wall_checkBox->setChecked(false);
}

void MainWindow::myupdate()
{
    //qDebug()<<ui->graphicsView->items().length()<<endl;
    ui->ball_num_label->setNum(ball_num);
    ui->wall_num_label->setNum(wall_num);
}

void MainWindow::on_undo_pushButton_clicked()
{
    if(ui->graphicsView->items().length()==0) return;
    if(ui->graphicsView->items().first()->scenePos()!=QPoint(0,0))//移除球时
        ball_num--;
    else
        wall_num--;
    ui->graphicsView->scene()->removeItem(ui->graphicsView->items().first());
}

void MainWindow::on_clear_pushButton_clicked()
{
    ui->graphicsView->scene()->clear();
    ball_num=0;
    wall_num=0;
}
