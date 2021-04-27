#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QImage>
#include <QPicture>
#include <QLabel>
#include <QDebug>
#include <QPainter>
#include <QPen>
#include <QVector>
using namespace cv;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //QPicture image;
    //image.load("D:\\qt1\\numberDis\\image/0.jpg");

    init();
    painter = new QPainter();
    Feature feature;

        //int j = 9;
        //QString str = QString("D:\\qt1\\numberDis\\image/Template/%1/0.png").arg(j);

}

void Widget::init()
{
    startX = 0;
    startY = 0;
    endX = 0;
    endY = 0;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    startX = event->x();
    startY = event->y();
    //qDebug() << startX << startY;

}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
        start.push_back(QPoint(startX,startY));
        //qDebug() << "开始"<<startX << startY;
        endX = event->x();
        endY = event->y();
        startX = endX;
        startY = endY;


        end.push_back(QPoint(endX,endY));
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    init();

}

void Widget::slotGrabWidget()
{
    QRect rect = ui->label->geometry();
    QPixmap p = this->grab(rect);
    filePathName = "D:\\qt1\\numberDis\\widget.png";
    p.save(filePathName);
    //Mat p1 = imread(filePathName.toStdString());
    //imshow("p1",p1);

}

void Widget::paintEvent(QPaintEvent *paint)
{
    QPen pen;
    pen.setColor(qRgb(0,0,0));
    pen.setWidth(5);
    painter->begin(this);
    painter->setPen(pen);
    for(int t = 1; t < start.size();t++)
    {
        painter->drawLine(start[t],end[t]);
    }
    painter->end();
    update();
}

Widget::~Widget()
{
    delete ui;

}

void Widget::on_pushshow_clicked()
{
    QImage image("://image/12.jpg");
    image = image.rgbSwapped();
    image.setText("11","sdf");
    image = image.scaled(360,240);
    //ui->label1->setPixmap(QPixmap::fromImage(image));
    qDebug() << "已完成";
    slotGrabWidget();
    feature.getpath(filePathName);
     Mat picture = feature.getSuitSize();
    qint64 result = qint64(feature.getdata(picture));
    //imshow("picture",picture);
    ui->labelresult->setText(QString("结果为%1").arg(result));
     //waitKey(0);
}

void Widget::on_pushclear_clicked()
{
    for(auto iter = start.begin();iter != start.end();)
    {
        start.erase(iter);
    }
    for(auto iter = end.begin();iter != end.end();)
    {
        end.erase(iter);
    }
    qDebug() << start.size() << end.size();
}
