#include "skill.h"
#include <fstream>

Skill::Skill(QWidget *parent, string name, int x, int y, int width, int height)
    :MyQLabel(parent, "", x, y, width, height)
{
    this->name = name;
    if(name != "")
    {
        string stdfile = ":/new/prefix3/skill/" + this->name + ".png";
        QString file = QString::fromStdString(stdfile);
        QImage* img=new QImage;
        img->load(file);
        *img = img->scaled(width,height);
        this->setPixmap(QPixmap::fromImage(*img));
    }
    this->readFromFile();
    this->cd_bar = new QLabel(parent);
    this->cd_bar->setGeometry(x, y + height + 10, width, 10);
    this->cd_bar->setStyleSheet("QLabel{background-color:rgb(0,0,255);}");
    this->cd_bar->show();
}

void Skill::readFromFile()
{
    string filename = "E:/code/test/skill/setting/" + this->name + ".txt";
    ifstream setting(filename);
    if(!setting.is_open())
    {
        return;
    }
    string buff_judge;
    setting >> buff_judge;
    if(buff_judge == "false")
    {
        this->buff_flag = false;
    }
    else
    {
        this->buff_flag = true;
        string buff_name;
        setting >> buff_name;
        this->attach_buff = new buff(buff_name);
    }
    string target;
    setting >> target;
    if(target == "false")
    {
        this->target = false;
    }
    else
    {
        this->target = true;
    }
    setting >> this->cd;
    setting >> this->cost;
    this->cur_cd = this->cd;
}

void Skill::mousePressEvent(QMouseEvent *event)
{
    if(this->cd == this->cur_cd)
    {
        emit clicked(this->name);
    }
    else
    {
        return;
    }
}

void Skill::cdBegin()
{
    if(this->cd == this->cur_cd)
    {
        this->timer = new QTimer;
        this->cur_cd = 0;
        this->timer->setInterval(1000);
        connect(timer,SIGNAL(timeout()),this,SLOT(increaseCd()));
        this->timer->start();
        this->cd_bar->setGeometry(this->get_x(), this->get_y() + this->get_height() + 10, 0 , 10);
    }
}

void Skill::increaseCd()
{
    if(this->cd == this->cur_cd)
    {
        this->timer->stop();
        delete this->timer;
        this->timer = nullptr;
    }
    else
    {
        this->cur_cd++;
        float rate = (float)this->cur_cd/(float)this->cd;
        float width = (float)this->get_width() * rate;
        this->cd_bar->setGeometry(this->get_x(), this->get_y() + this->get_height() + 10,(int)width, 10);
    }
}
