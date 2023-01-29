#include "mypushbutton.h"
#include <QPropertyAnimation>
MyPushButton::MyPushButton(QWidget *parent, QString file, int x,int y, int width, int height)
    : QPushButton(parent)
{
    this->file = file;
    this->setGeometry(x, y, width, height);
    QImage* img=new QImage;
    if(!img->load(file))
    {
        qDebug() << "No such img" << Qt::endl;
    }
    *img = img->scaled(this->width(),this->height());
    this->x = x;
    this->y = y;

    this->setStyleSheet("QPushButton{border:0px;}");

    this->setIcon(QPixmap::fromImage(*img));
    this->setIconSize(QSize(width, height));
}

bool MyPushButton::zoom1()
{
    QPropertyAnimation* this_move1 = new QPropertyAnimation(this, "geometry");
    this_move1->setDuration(200);
    this_move1->setStartValue(QRect(this->x,this->y,this->width(),this->height()));
    this_move1->setEndValue(QRect(this->x,this->y + 20,this->width(),this->height()));
    this_move1->setEasingCurve(QEasingCurve::Linear);
    this_move1->start();
    qDebug() <<"zoom1" << this->x << this -> y<< Qt::endl;
    return true;
}

void MyPushButton::zoom2()
{
    QPropertyAnimation* this_move2 = new QPropertyAnimation(this, "geometry");
    this_move2->setDuration(200);
    this_move2->setStartValue(QRect(this->x,this->y + 20,this->width(),this->height()));
    this_move2->setEndValue(QRect(this->x,this->y,this->width(),this->height()));
    this_move2->setEasingCurve(QEasingCurve::Linear);
    this_move2->start();
    qDebug() <<"zoom2" << Qt::endl;
}

void MyPushButton::move(int end_x, int end_y)
{
    QPropertyAnimation* this_move2 = new QPropertyAnimation(this, "geometry");
    this_move2->setDuration(200);
    this_move2->setStartValue(QRect(this->x,this->y,this->width(),this->height()));
    this_move2->setEndValue(QRect(end_x,end_y,this->width(),this->height()));
    this->x = end_x;
    this->y = end_y;
    this_move2->setEasingCurve(QEasingCurve::Linear);
    this_move2->start();
}

void MyPushButton::setLevel(int level)
{
    this->level = level;
}

void MyPushButton::mousePressEvent(QMouseEvent *event)
{
    emit clicked(this->level);
    emit clicked();
}
