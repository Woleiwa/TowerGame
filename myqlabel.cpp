#include "myqlabel.h"
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include <QTimer>
MyQLabel::MyQLabel(QWidget *parent, QString file, int x, int y, int width, int height)
    : QLabel(parent)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->file = file;
    this->setGeometry(x, y, width, height);  
    if(file != "")
    {
        QImage* img=new QImage;
        img->load(file);
        *img = img->scaled(this->width,this->height);
        this->setPixmap(QPixmap::fromImage(*img));
    }
}

void MyQLabel::comeOut()
{
    QPropertyAnimation* this_move = new QPropertyAnimation(this, "geometry");
    this_move->setDuration(1800);
    this_move->setStartValue(QRect(this->x,this->y,this->width,this->height));
    this_move->setEndValue(QRect(this->x,this->y + 100,this->width,this->height));
    this_move->setEasingCurve(QEasingCurve::OutBounce);
    this_move->start();
}

void MyQLabel::mousePressEvent(QMouseEvent *event)
{
    if(!this->disappearflag)
    {
        emit clicked();
        emit clicked(this->i);
    }
}

void MyQLabel::disappear()
{
    this->timer = new QTimer;
    this->timer->setInterval(10);
    timer->start();
    this->opacity = 1;
    this->disappearflag = true;
    connect(timer,SIGNAL(timeout()),this,SLOT(fadeout()));
}

void MyQLabel::appear()
{
    this->timer = new QTimer;
    this->timer->setInterval(10);
    this->apopacity = 0;
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(appearin()));
}

void MyQLabel::fadeout()
{
    if(opacity<=0.0)
    {
        this->hide();
        timer->stop();//定时器停止
    }
    else
    {
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
        effect->setOpacity(opacity);
        this->setGraphicsEffect(effect);
        opacity-=0.05;
    }
}

void MyQLabel::appearin()
{
    if(apopacity>=1.0)
    {
        timer->stop();//定时器停止
    }
    else
    {
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
        effect->setOpacity(apopacity);
        this->setGraphicsEffect(effect);
        apopacity+=0.05;
    }
}

void MyQLabel::zoom1()
{
    QPropertyAnimation* this_move1 = new QPropertyAnimation(this, "geometry");
    this_move1->setDuration(200);
    this_move1->setStartValue(QRect(this->x,this->y,this->width,this->height));
    this_move1->setEndValue(QRect(this->x,this->y + 20,this->width,this->height));
    this_move1->setEasingCurve(QEasingCurve::Linear);
    this_move1->start();
    qDebug() <<"zoom1" << this->x << this -> y<< Qt::endl;
}

void MyQLabel::zoom2()
{
    QPropertyAnimation* this_move2 = new QPropertyAnimation(this, "geometry");
    this_move2->setDuration(200);
    this_move2->setStartValue(QRect(this->x,this->y + 20,this->width,this->height));
    this_move2->setEndValue(QRect(this->x,this->y,this->width,this->height));
    this_move2->setEasingCurve(QEasingCurve::Linear);
    this_move2->start();
    qDebug() <<"zoom2" << Qt::endl;
}

void MyQLabel::switchPicture(QString newfile)
{
    QImage* img=new QImage;
    this->file = newfile;
    img->load(newfile);
    *img = img->scaled(this->width,this->height);
    this->setGeometry(x, y, width, height);
    this->setPixmap(QPixmap::fromImage(*img));
}

void MyQLabel::test()
{
    qtimer = new QTimer;
    qtimer->setInterval(100);
    connect(qtimer,SIGNAL(timeout()),this,SLOT(slottest()));
    qtimer->start();

}

void MyQLabel::slottest()
{
    QString newfile[4];

    newfile[0] = ":/new/prefix1/monster/blue_dragon/front_1.png";
    newfile[1] = ":/new/prefix1/monster/blue_dragon/front_2.png";
    newfile[2] = ":/new/prefix1/monster/blue_dragon/front_3.png";
    newfile[3] = ":/new/prefix1/monster/blue_dragon/front_4.png";
    this->i++;
    this->i %= 4;
    switchPicture(newfile[i]);
}

void MyQLabel::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    this->setGeometry(x,y,width,height);
}
