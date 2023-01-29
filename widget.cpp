#include "widget.h"
#include "ui_widget.h"
#include<QPalette>
#include <QPixmap>
#include <QFile>
#include <QPainter>
#include "register.h"
#include "signin.h"
#include <QPropertyAnimation>
#include <QTimer>
#include "loading.h"
#include "selectlevel.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(640,480);
    bt = new MyPushButton(this,":/new/prefix1/regist.png",199,229,240,60);
    bt2 = new MyPushButton(this,":/new/prefix1/login.png",199,329,240,60);


    //bt->setStyleSheet("QPushButton{border-image:url(:/new/prefix1/button.jpg);border:2px solid #5F92B2;border-radius:5px;color:white;font: 24pt '华光行楷_CNKI';}");
    //bt->setStyleSheet("QPushButton{background-color:rgb(134,183,200);border:2px solid #5F92B2;border-radius:5px;color:white;font: 24pt '华光行楷_CNKI';}QPushButton:hover{background-color:rgb(0,130,150);border:2px solid #5F92B2;border-radius:5px;color:white;}QPushButton:hover:pressed{background-color:rgb(85,170,255); border:2px solid #3C80B1;border-radius:5px;color:white; }");
    //bt2->setStyleSheet("QPushButton{background-color:rgb(134,183,200);border:2px solid #5F92B2;border-radius:5px;color:white;font: 24pt '华光行楷_CNKI';}QPushButton:hover{background-color:rgb(0,130,150);border:2px solid #5F92B2;border-radius:5px;color:white;}QPushButton:hover:pressed{background-color:rgb(85,170,255); border:2px solid #3C80B1;border-radius:5px;color:white; }");
    this->setObjectName("parent_widget");
    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(":/new/prefix1/background.png");
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
    connect(bt2,SIGNAL(clicked()),this, SLOT(signIn()));
    connect(bt,SIGNAL(clicked()),this, SLOT(playerRegister()));


    title = new MyQLabel(this,":/new/prefix1/title.png", 119,-50, 400, 180);
    title->comeOut();

}

void Widget:: signIn()
{
    if(bt2->zoom1())
    {
        bt2->zoom2();
    }
    qDebug() << "sign in" << Qt::endl;
    QTimer::singleShot(500,[=](){
        SignIn* s = new SignIn;
        s->show();
        connect(s,SIGNAL(signin(Player*)),this,SLOT(start(Player*)));
    });
}

void Widget:: playerRegister()
{

    if(bt->zoom1())
    {
        bt->zoom2();
    }

    qDebug() << "register" << Qt::endl;
    QTimer::singleShot(500,[=](){
        Register* r = new Register;
        r->show();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start(Player* player)
{
    qDebug() <<"start" << Qt::endl;
    this->hide();
    Loading* ld = new Loading(nullptr,6);

    ld->show();
    connect(ld,SIGNAL(end()),this,SLOT(storyscene()));
    this->p = player;
}

void Widget::storyscene()
{
    this->st = new StoryScene;
    st->show();
    connect(st,SIGNAL(passed()),this,SLOT(selectLevel()));
}

void Widget::selectLevel()
{
    SelectLevel* sl = new SelectLevel(nullptr,this->p);
    sl->show();
}
