#include "hpbar.h"

HpBar::HpBar(QWidget *parent, int x, int y, int width, int height)
    : QProgressBar(parent)
{
    this->setGeometry(x,y,width,height);
}

void HpBar::setvalue(int value)
{
    this->setValue(value);
    this->changecolor();
}

void HpBar::changecolor()
{
   this->setStyleSheet("QProgressBar { border: 2px solid grey;  background-color: #FFFFFF; text-align: center;}QProgressBar::chunk {background:QLinearGradient(x1:0,y1:0,x2:2,y2:0,stop:0 #666699,stop:1  #DB7093); }");
}
