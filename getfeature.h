#ifndef GETFEATURE_H
#define GETFEATURE_H
#include <QString>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QVector>
struct maxjudge{
    int Max;
    int Min;
};
class Feature
{
public:
    void getpath(QString);
    cv::Mat getSuitSize();
    void presevation(QImage);
    void Writefile(float*);
    //QVector <uchar> feature;//列
    QVector <uint> col;
    QVector <uint> row;
    int getdata(cv::Mat);
    int matchdata(float*);
   private:
    QString path;
};

#endif // GETFEATURE_H
