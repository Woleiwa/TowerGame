#include "signin.h"
#include "playerlist.h"
#include "player.h"
#include <QMessageBox>
#include "forgetpassword.h"

SignIn::SignIn(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(360,440);
    bt = new QPushButton("登录",this);
    bt2 = new QPushButton("忘记/修改密码",this);

    lb_username = new QLabel("用户名",this);
    lb_password = new QLabel("密码",this);

    le_username = new QLineEdit("",this);
    le_password = new QLineEdit("",this);
    cbx = new QCheckBox("显示密码",this);

    bt->setGeometry(79,299,200,40);
    bt2->setGeometry(79,359,200,40);

    le_username->setGeometry(79,59,200,40);
    le_password->setGeometry(79,139,200,40);
    le_password->setEchoMode(QLineEdit::Password);

    connect(cbx, &QCheckBox::clicked, [&](bool x){
            le_password->setEchoMode(x?QLineEdit::Normal:QLineEdit::Password);
    });

    lb_username->setGeometry(79,19,200,40);
    lb_password->setGeometry(79,99,200,40);

    QPalette background = this->palette();
    QImage Imgbackground(":/new/prefix1/register.jpg");
    QImage refitimgpic=Imgbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    background.setBrush(QPalette::Window, QBrush(refitimgpic));
    this->setPalette(background);
    cbx->setGeometry(79,199,120,40);
    bt->setStyleSheet("QPushButton{background-color:rgb(134,183,200);border:2px solid #5F92B2;border-radius:5px;color:white;font: 18pt '华光行楷_CNKI';}QPushButton:hover{background-color:rgb(0,130,150);border:2px solid #5F92B2;border-radius:5px;color:white;}QPushButton:hover:pressed{background-color:rgb(85,170,255); border:2px solid #3C80B1;border-radius:5px;color:white; }");
    bt2->setStyleSheet("QPushButton{background-color:rgb(134,183,200);border:2px solid #5F92B2;border-radius:5px;color:white;font: 18pt '华光行楷_CNKI';}QPushButton:hover{background-color:rgb(0,130,150);border:2px solid #5F92B2;border-radius:5px;color:white;}QPushButton:hover:pressed{background-color:rgb(85,170,255); border:2px solid #3C80B1;border-radius:5px;color:white; }");

    le_username->setStyleSheet("QLineEdit{background-color:rgb(192,192,192);border:2px solid #802A2A;border-radius:5px;color:white;}");
    le_password->setStyleSheet("QLineEdit{background-color:rgb(192,192,192);border:2px solid #802A2A;border-radius:5px;color:white;}");

    lb_username->setStyleSheet("QLabel{font: 12pt '华光行楷_CNKI';}");
    lb_password->setStyleSheet("QLabel{font: 12pt '华光行楷_CNKI';}");
    connect(bt,SIGNAL(clicked(bool)),this, SLOT(signIn()));
    connect(bt2,SIGNAL(clicked(bool)),this, SLOT(forgetPassword()));
}

bool SignIn::signIn()
{
    QString username = le_username->text();
    QString password = le_password->text();
    std::string user = username.toStdString();
    std::string pass = password.toStdString();

    PlayerList plist;
    plist.readFromTxt();
    if(!plist.find(user))
    {
        QMessageBox::warning(this, "No such user!", "不存在该用户！", QMessageBox::Open);
        return false;
    }
    player_info p_info = plist.search_for_user(user);
    Player* player = new Player(p_info);
    if(!player->sigin(user, pass))
    {
        QMessageBox::warning(this, "Wrong password!", "密码错误！", QMessageBox::Open);
        return false;
    }
    else
    {
        QMessageBox::warning(this, "Success!", "登录成功！", QMessageBox::Open);
        this->sign = true;
        this->close();
        emit signin(player);
        return true;
    }
}

void SignIn::forgetPassword()
{
    ForgetPassword* f = new ForgetPassword;
    f->show();
}
