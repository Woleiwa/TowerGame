#include "testwidget.h"

TestWidget::TestWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(QSize(200,200));
    this->test = new MyQLabel(this,":/new/prefix1/monster/wolf/front_1.png", 60, 40, 80, 120);
    this->test->test();
}
