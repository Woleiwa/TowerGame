#include "levelup.h"
#include <QTimer>
LevelUp::LevelUp(QWidget *parent, Tower* tower)
    : QWidget(parent)
{
    this->tower = tower;
    this->setFixedSize(QSize(200,180));
    this->sure = new MyPushButton(this,":/new/prefix3/sure.png",10,130,80,40);
    this->cancel = new MyPushButton(this,":/new/prefix3/cancel.png",110,130,80,40);
    this->message = new QLabel(this);
    connect(cancel,SIGNAL(clicked()),this,SLOT(closeWindow()));
    connect(sure,SIGNAL(clicked()),this,SLOT(emitSignal()));
    QString str = "升级需要花费" + QString::fromStdString(to_string(this->tower->getPriceForLevelUp())) + "马娜\n";
    str += "攻击力增加" + QString::fromStdString(to_string(this->tower->getAttack_Up())) +"\n";
    str += "血量增加" + QString::fromStdString(to_string(this->tower->getHp_Up())) +"\n";
    str += "攻击范围增加" +  QString::fromStdString(to_string(this->tower->getScale_Up())) +"\n";
    this->message->setText(str);
    this->message->setGeometry(10,20,180,90);
}

void LevelUp::closeWindow()
{
    this->cancel->zoom1();
    this->cancel->zoom2();
    QTimer::singleShot(200,[=](){
        this->close();
    });
}

void LevelUp::emitSignal()
{
    this->sure->zoom1();
    this->sure->zoom2();
    QTimer::singleShot(200,[=](){
        emit levelup(tower->getRank());
        this->close();
    });
}
