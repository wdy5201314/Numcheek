#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMouseEvent>
#include<QPaintEvent>
#include <QVector>
#include "getfeature.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void init();
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void slotGrabWidget();
    void paintEvent(QPaintEvent* paint);
    ~Widget();
    int startX;
    int startY;
    int endX;
    int endY;
    QPainter *painter;
    QVector <QPoint> start;
    QVector <QPoint> end;
    Feature feature;
    QString filePathName;


private slots:

    void on_pushshow_clicked();


    void on_pushclear_clicked();

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
