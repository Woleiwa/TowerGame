#include "buff.h"
#include <fstream>
#include <QDebug>

buff::buff(string name)
{
    this->buff_name = name;
    this->readFromTxt();
}

void buff::readFromTxt()
{
    string filename = "E://code/test/buff/" + this->buff_name + ".txt";
    ifstream fstr(filename);
    if(!fstr.is_open())
    {
        qDebug()<< "No such file called" << QString::fromStdString(filename);
        return;
    }
    string temp;
    fstr >> temp;
    if(temp == "true")
    {
        this->temporary = true;
    }
    else
    {
        this->temporary = false;
    }
    fstr >> this->last_time;
    string atk;
    fstr >> atk;
    if(atk == "true")
    {
        this->atk_or_not = true;
    }
    else
    {
        this->atk_or_not = false;
    }
    fstr >> this->attach_buff;
}

void buff::updateBuff(int i)
{
    if(this->last_time != 0)
    {
        this->last_time += i;
    }
}
