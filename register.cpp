#include "register.h"
#include <QApplication>
#include <QPalette>
#include <QPixmap>
#include <QFile>
#include <QPainter>
#include <string>
#include <QString>
#include <vector>
#include <iostream>
#include <string>
#include"playerlist.h"
#include <QMessageBox>
#include "player.h"
Register::Register(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(360,440);
    bt = new QPushButton("注册",this);
    bt2 = new QPushButton("取消",this);

    lb_username = new QLabel("用户名",this);
    lb_password = new QLabel("密码",this);
    lb_cor_password = new QLabel("确认密码",this);
    lb_phonenum = new QLabel("电话号码",this);

    le_username = new QLineEdit("",this);
    le_password = new QLineEdit("",this);
    le_cor_password = new QLineEdit("",this);
    le_phonenum = new QLineEdit("",this);

    bt->setGeometry(79,359,80,40);
    bt2->setGeometry(199,359,80,40);

    QPalette background = this->palette();
    QImage Imgbackground(":/new/prefix1/register.jpg");
    QImage refitimgpic=Imgbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    background.setBrush(QPalette::Window, QBrush(refitimgpic));
    this->setPalette(background);

    le_username->setGeometry(79,59,200,40);
    le_password->setGeometry(79,139,200,40);
    le_cor_password->setGeometry(79,219,200,40);
    le_phonenum->setGeometry(79,299,200,40);

    lb_username->setGeometry(79,19,200,40);
    lb_password->setGeometry(79,99,200,40);
    lb_cor_password->setGeometry(79,179,200,40);
    lb_phonenum->setGeometry(79,259,200,40);

    bt->setStyleSheet("QPushButton{background-color:rgb(134,183,200);border:2px solid #5F92B2;border-radius:5px;color:white;font: 12pt '华光行楷_CNKI';}QPushButton:hover{background-color:rgb(0,130,150);border:2px solid #5F92B2;border-radius:5px;color:white;}QPushButton:hover:pressed{background-color:rgb(85,170,255); border:2px solid #3C80B1;border-radius:5px;color:white; }");
    bt2->setStyleSheet("QPushButton{background-color:rgb(134,183,200);border:2px solid #5F92B2;border-radius:5px;color:white;font: 12pt '华光行楷_CNKI';}QPushButton:hover{background-color:rgb(0,130,150);border:2px solid #5F92B2;border-radius:5px;color:white;}QPushButton:hover:pressed{background-color:rgb(85,170,255); border:2px solid #3C80B1;border-radius:5px;color:white; }");

    le_username->setStyleSheet("QLineEdit{background-color:rgb(192,192,192);border:2px solid #802A2A;border-radius:5px;color:white;}");
    le_password->setStyleSheet("QLineEdit{background-color:rgb(192,192,192);border:2px solid #802A2A;border-radius:5px;color:white;}");
    le_cor_password->setStyleSheet("QLineEdit{background-color:rgb(192,192,192);border:2px solid #802A2A;border-radius:5px;color:white;}");
    le_phonenum->setStyleSheet("QLineEdit{background-color:rgb(192,192,192);border:2px solid #802A2A;border-radius:5px;color:white;}");

    lb_username->setStyleSheet("QLabel{font: 12pt '华光行楷_CNKI';}");
    lb_password->setStyleSheet("QLabel{font: 12pt '华光行楷_CNKI';}");
    lb_cor_password->setStyleSheet("QLabel{font: 12pt '华光行楷_CNKI';}");
    lb_phonenum->setStyleSheet("QLabel{font: 12pt '华光行楷_CNKI';}");

    connect(bt2,SIGNAL(clicked(bool)),this, SLOT(cancel()));
    connect(bt,SIGNAL(clicked(bool)),this, SLOT(regist()));
}

Register::~Register()
{

}

void Register::cancel()
{
    this->close();
    qDebug() << "close" << Qt::endl;
}

bool judge(string password)
{
    if(password.length() < 6 || password.length() > 20)
    {
        return false;
    }
    else
    {
        bool j1 = false;
        bool j2 = false;
        bool j3 = false;
        for(int i = 0; i < password.length(); i++)
        {
            if(password[i] >= '0' && password[i] <= '9')
            {
                j1 = true;
            }
            else if(password[i] >= 'a' && password[i] <= 'z')
            {
                j2 = true;
            }
            else if(password[i] >= 'A' && password[i] <= 'Z')
            {
                j3 = true;
            }
            if(j1 && j2 && j3)
            {
                break;
            }
        }
        return j1&j2&j3;
    }
}

void Register::regist()
{
    QString username = le_username->text();
    std::string str_name = username.toStdString();
    PlayerList plist;
    plist.readFromTxt();
    if(str_name.length() == 0)
    {
        QMessageBox::warning(this, "Empty username!", "用户名不能为空！", QMessageBox::Open);
        return;
    }
    if (plist.find(str_name))
    {
        QMessageBox::warning(this, "Repeated username!", "请选择一个全新的用户名！", QMessageBox::Open);
        return;
    }
    QString password = le_password->text();
    QString cor_password = le_cor_password->text();
    if (password != cor_password)
    {
        QMessageBox::warning(this, "Password error!", "两次密码不一致！", QMessageBox::Open);
        return;
    }
    string str_pass = password.toStdString();
    if(!judge(str_pass))
    {
        QMessageBox::warning(this, "Password error!", "密码不符合要求，请输入一个长度为7-19，含有数字，大小写字母的密码！", QMessageBox::Open);
        return;
    }
    QString phonenum = le_phonenum->text();
    string str_phone = phonenum.toStdString();
    if(str_phone.length() == 0)
    {
        QMessageBox::warning(this, "Empty phonenum!", "请输入电话号码！", QMessageBox::Open);
        return;
    }
    Player newplayer(str_name,str_pass,str_phone);
    newplayer.regist();
    QMessageBox::warning(this, "Success", "注册成功！", QMessageBox::Open);
    qDebug()<<"Add a new player!" << Qt::endl;
    this->close();
}
