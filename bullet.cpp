#include "bullet.h"
#include <math.h>

bullet:: bullet(QWidget *parent, string type , int atk, MyQLabel* luncher, MyQLabel* target)
    : MyQLabel(parent)
{
    this->type = type;
    this->luncher = luncher;
    this->target = target;
    this->atk = atk;
    this->f_x = luncher->get_x() + luncher->get_width() / 2 - 10;
    this->f_y = luncher->get_y() + luncher->get_height() / 2 - 10;
    QString file_line = ":/new/prefix2/bullet/";
    QString type_name = QString::fromStdString(type);

    file_line += (type_name + ".png");
    //qDebug() << file_line;
    QImage* img=new QImage;
    img->load(file_line);
    *img = img->scaled(10,10);
    this->setPixmap(QPixmap::fromImage(*img));
    this->setGeometry((int)f_x,(int)f_y,20,20);
    this->show();
}

void bullet::start()
{
    this->movetimer = new QTimer;
    this->movetimer->setInterval(50);
    connect(movetimer,SIGNAL(timeout()),this,SLOT(moveTowards()));
    this->movetimer->start();
}

void bullet::moveTowards()
{
    if(stop)
    {
        return;
    }
    //qDebug() <<"bullet"<<this->rank << "moved";
    double target_x = target->get_x() + target->get_width() / 2 - 10;
    double target_y = target->get_y() + target->get_height() / 2 - 10;
    double dx = target_x - f_x;
    double dy = target_y - f_y;
    //qDebug() << dx <<" "<<dy;
    double r = pow(dx * dx + dy * dy,(double)1/2);
    //qDebug() << r;
    if(r <= 10)
    {
        this->movetimer->stop();
        this->disappear();
        emit hit(this->rank,this->direction);
        return;
    }
    this->f_x += dx/r * 10;
    this->f_y += dy/r * 10;
    this->setGeometry((int)f_x,(int)f_y,20,20);
}

void bullet::stopBullet()
{
    this->stop = true;
}

void bullet::attachBuff(buff* atkbuff)
{
    if(atkbuff == nullptr)
    {
        return;
    }
    else if(this->get_buff)
    {
        return;
    }
    else if(atkbuff->getAtkFlag())
    {
        this->atk_buff = new buff(atkbuff->getAttachBuff());
        this->get_buff = true;
    }
}
