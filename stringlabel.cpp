#include "stringlabel.h"
#include <QGraphicsEffect>
StringLabel::StringLabel(QWidget *parent, QString content, int x, int y, int width, int height)
: QLabel(content,parent)
{
    this->content = content;
    this->setGeometry(x, y, width, height);
}

void StringLabel::disappear()
{
    this->timer = new QTimer;
    this->timer->setInterval(10);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(fadeout()));
}

void StringLabel::fadeout()
{
    if(opacity<=0.0)
    {
        timer->stop();//定时器停止
    }
    else
    {
        QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
        effect->setOpacity(opacity);
        this->setGraphicsEffect(effect);
        opacity-=0.01;
    }
}

void StringLabel::appear()
{
    this->timer = new QTimer;
    this->timer->setInterval(10);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(appearin()));
}

void StringLabel::appearin()
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
        apopacity+=0.01;
    }
}
