#include "getfeature.h"
#include <QDebug>
#include <QVector>
#include <QFile>
#include <QDataStream>
#include <QString>
#include <QNetworkReply>
#include <QEventLoop>
#include <QNetworkAccessManager>
using namespace cv; 
maxjudge findMax(uint* ,int);
int main()
{
    Feature feature;
    feature.getpath("://image/12.jpg");
    Mat picture = feature.getSuitSize();

    //imshow("picture",picture);
    return 0;
}
void Feature::getpath(QString paths)
{
    path = paths;
}

cv::Mat Feature::getSuitSize()
{ 
    Mat oriphoto = cv::imread(path.toStdString());
    if(!oriphoto.empty())
    {
        qDebug() << "打开成功" << endl;

    }
    Mat grayphoto;
    cvtColor(oriphoto,grayphoto,COLOR_BGR2GRAY);
    //imshow("ori",grayphoto);
    //上面是对图片进行灰度处理
    uint cols = grayphoto.cols;//232
    uint rows = grayphoto.rows;//198
    //uchar* pst = grayphoto.ptr<uchar>(0);//将图片的第一个元素地址给指针pst
    uchar flag = 0;//为0不需要加为1需要加
    uchar flag1 = 0;//初始化
    uint flag2 =0;//col中有几个元素的标志
    uchar flag3 = 0;//col是否有的标志位
    uint flag5 = 0;//记录row的值
    for(uint i = 0; i < rows ; i++)
    {
        for(uint j = 0; j < cols ; j++)//行列循环
        {
            if(grayphoto.at<uchar>(i,j) == 0)//判断这个是否为黑色
            {
                if(flag1 == 0)
                {
                    col.push_back(j);
                    flag2++;
                    flag1 = 1;
                }
                else {
                    //qDebug() << "flag2:" << flag2;
                    for(uint k = 0; k < flag2;k++)
                    {
                        if(j == uint(col[k]))
                        {

                           flag3 = 1;
                        }
                    }
                    if(flag3 == 0)
                    {
                        col.push_back(j);//如果没有相同的则加进去否则重置标志位
                        flag2++;
                    }
                    else {
                        flag3 = 0;
                    }
                }
                flag = 1;
            }
        }
        if(flag == 1)
        {
            row.push_back(i);
            flag = 0;
            flag5++;
        }

    }
    qDebug() << flag2 << "col的值：";
    qDebug() << flag5 << "row的值：";
    int vcol = col.size();
    /*
    *将图片中的黑色元素存储到vcol(列x),和vrow(行x)中
    */
    uint* p = &col[0];//帮地址存储到指针P中,方便读取
    maxjudge colstruct;
    colstruct = findMax(p,vcol);
    /*findMax函数主要是将其排列，可以改为传回两个数*/
    //uint* p1 = &row[0];
    //建立矩阵，选出需要裁剪的位置rect(x,y,width,height)
    Rect rect(colstruct.Min ,row[0],colstruct.Max - colstruct.Min + 5,row[flag5 - 1] - row[0]+ 5);
    qDebug() << "106:" << colstruct.Min << row[0] << colstruct.Max- colstruct.Min + 5 << row[flag5 - 1] << flag5;
    Mat endpicture = grayphoto(rect);
    return endpicture;
}

void Feature::Writefile(float* datasum )
{
    /*QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QString SERVER_URL = "01.txt";
    //QNetworkReply *reply = manager->post(QNetworkRequest(QUrl(SERVER_URL)), data);
    //QByteArray responseData;
    QEventLoop eventLoop;
    connect(_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    eventLoop.exec();       //block until finish
    responseData = reply->readAll();*/
    QFile file("01.txt");
    QDataStream stram(&file);
    int flag = 0;
    if(file.open(QIODevice::ReadWrite))
    {

        stram.device()->seek(0);

        while(!stram.atEnd())
        {

            flag++;
            float temp;
            stram >> temp;
            qDebug() << temp;

        }
        for(int i = 0; i< 25 ;i++)
        {

            stram << datasum[i];
            //qDebug() << datasum[i];
        }
        //stram << 0;
        qDebug() << "flag:" << flag;
        file.flush();
        file.close();

    }
    else {
        qDebug() << "打开失败";
    }
    /*if(flag == 1)
    {
        QFile file("01.txt");
        float* p = 0;
        QDataStream out(&file);
        if(file.open(QIODevice::ReadOnly))
            {
                qDebug() << "打开";
                float str ,str1;
                int i = 0;
                while(!out.atEnd())
                {
                    out >> str;
                    i++;
                    qDebug() << str;
                    if(i > 25)
                    {
                        break;
                    }
                }
*/
                //qDebug() << str << str1;
                 /*for(it = out.out.atEnd()
                {
                    qDebug() << *p;
                    p++;
                }
                qDebug() <<"关闭文件";
                file.close();
            }
    }*/
    /*if(file.open(QIODevice::ReadOnly))
    {
        uchar* p;
        QDataStream out(&file);
        out >> *p;
        while(*p != NULL)
        {
            qDebug() << *p;
            p++;
        }
        file.close();
    }*/
}

int Feature::getdata(Mat image)
{
    //qDebug() << "104进入";
    uint col = image.cols;
    uint row = image.rows;
    float datasum[25] = {0};
    /*
     * 把划分好的值付给datasum
    */

    for(uint i = 0; i < 5 ;i++)
    {
        for(uint j = 0; j < 5; j++)
        {
            //qDebug() << "115进入";
            if(i != 4 && j!=4)
            {
                float flag = 0;
                for(uint k = col / 5 * i; k < col / 5 * (i + 1) ; k++)
                    for(uint l = row /5 * j; l < row / 5 * (j +1) ; l++)
                    {

                            flag += image.at<uchar>(l,k);
                    }
                datasum[(i + 1) * ( j + 1) - 1] = flag / (float(col  * (row ))* 255);

            }


            else if ( i == 4 && j!= 4)
            {
                float flag = 0;
                for(uint k = col / 5 *i; k < col ; k++)
                    for(uint l = row / 5 *j; l < row / 5 *(j + 1); l++)
                    {
                        flag += image.at<uchar>(l,k);
                    }
                datasum[(i + 1) * (j + 1) - 1] = flag / (float((col - col / 5 * 4 ) * (row / 5)) *255);
            }
            else if ( j == 4 && i!= 4)
            {
                float flag = 0;
                for(uint k = col / 5 *i; k < col /5 * (i + 1) ; k++)
                    for(uint l = row / 5 *j; l < row ; l++)
                    {
                        flag += image.at<uchar>(l,k);
                    }
                datasum[(i + 1) * (j + 1) - 1] = flag / (float((row - row / 5 * 4 ) * (col / 5)) * 255);
            }
            else if ( j == 4 && i == 4)
            {
                float flag = 0;
                for(uint k = col / 5 * 4; k < col ; k++)
                    for(uint l = row / 5 * 4; l < row ; l++)
                    {
                        flag += image.at<uchar>(l,k);
                    }
                datasum[(i + 1) * (j + 1) - 1] = flag / (float((col - col / 5 * 4 ) * (row - row / 5 * 4))*255);
            }
        }
    }
    //Writefile(&datasum[0]);
    int result = matchdata(&datasum[0]);
    return result;
}

int Feature::matchdata(float* p)
{
    QFile file(("01.txt"));
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "252不能打开设备";
    }
    QDataStream in(&file);
    float tem[10] = {0};
    //float* data = &p;

    for(int i = 0; i < 10 ;i++)
    {
        for(int j = 0;j < 25; j++)
        {
            float temp;
            in >> temp;
            qDebug() << temp;
            //qDebug() << *(p + j);
            tem[i] += (*(p + j) - temp) * (*(p + j) - temp) ;
        }
    }
    int returndata = 0;
    for(int i = 1; i < 10 ;i++)
    {
        //qDebug() << tem[i];
        if(tem[0] > tem[i])
        {
            float temp;
            temp = tem[i];
            tem[i] = tem[0];
            tem[0] = temp;
            returndata = i;
            //qDebug() <<  "278" << i;
        }
    }
    file.close();
    //qDebug() << returndata;
    return  returndata;
}
maxjudge findMax(uint* tem ,int size)//冒泡法
{
    maxjudge twosum;
    for(int i = 0; i < size; i++)
    {
        for(int j = size - 1; j > i; j--)
        {
            if(*(tem + i) < *(tem + j))
            {
                int temp;
                temp = *(tem + j);
                *(tem + j) = *(tem + i);
                *(tem + i) = temp;
            }
        }
    }
    twosum.Max = *tem;
    twosum.Min = *(tem + size - 1);
    return twosum;
}

