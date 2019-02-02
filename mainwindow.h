#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "myitem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGraphicsScene *scene1 = new QGraphicsScene;

private:
    Ui::MainWindow *ui;

    QTimer *timer = new QTimer(this);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    QGraphicsLineItem * newWall = new QGraphicsLineItem();
    QPoint wall_start_point;
    QPoint wall_end_point;

    int ball_num=0;
    int wall_num=0;

private slots:
    void on_run_stop_pushButton_toggled(bool);

    void on_horizontalSlider_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

    void on_add_wall_checkBox_stateChanged(int);

    void on_add_ball_checkBox_stateChanged(int);

    void myupdate();
    void on_undo_pushButton_clicked();
    void on_clear_pushButton_clicked();
};

#endif // MAINWINDOW_H
