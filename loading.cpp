#include "loading.h"

Loading::Loading(QWidget* parent, int i)
    : QWidget(parent)
{
    this->setFixedSize(640,480);
    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(":/new/prefix1/background.png");
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);

    this->qb = new QProgressBar(this);
    qb->setObjectName("加载中");
    qb->setMinimum(0);
    qb->setMaximum(100);

    qb->setAlignment(Qt::AlignCenter);
    qb->setGeometry(39,399,542,20);
    this->i = i;
    qtimer = new QTimer;
    int per_second = 100/i;
    qtimer->setInterval(1000/per_second);
    connect(qtimer,SIGNAL(timeout()),this,SLOT(load()));
    qb->reset();
    qtimer->start();
    title = new MyQLabel(this,":/new/prefix1/title.png", 20, 20, 600, 240);
}

void Loading::load()
{
    int currentValue = qb->value();

    if(currentValue >= qb->maximum())
    {
        qtimer->stop();
        emit end();
        this->hide();
    }
    else
    {
        qb->setValue(qb->value() + 1);
        //qDebug() << qb->value();
    }
}
