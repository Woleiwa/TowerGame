#include "monsterlabel.h"
#include <QPainter>
MonsterLabel::MonsterLabel(QWidget *parent, QString file,int x, int y, int width, int height, Monster* monster)
    :MyQLabel(parent, file, x, y, width, height)
{
    this->monster = monster;
    this->hplabel = new QLabel(parent);
    this->hplabel->setGeometry(x, y - 10, width, 10);
    this->hplabel->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
    this->hplabel->show();
    firebuff = new MyQLabel(parent,":/new/prefix3/buff/fire.png",x,y,width,height);
    sldbuff = new MyQLabel(parent,":/new/prefix3/buff/slowdown.png",x,y,width,height);
    light = new MyQLabel(parent,":/new/prefix3/buff/lighted.png",x,y,width,height);
    frozenbuff = new MyQLabel(parent,":/new/prefix3/buff/frozen.png",x,y,width,height);
    light->hide();
    firebuff->hide();
    sldbuff->hide();
    frozenbuff->hide();
}


void MonsterLabel::monsterMove()
{
    if(this->stop || this->frozen)
    {
        return;
    }
    changeDirection();
    string filename = ":/new/prefix1/monster/";
    filename += this->monster->getName() + "/" + this->monster->getDirection() + "_";
    string index = to_string(step + 1);
    step ++;
    step %= 4;
    filename += index + ".png";
    if(this->blocked)
    {
        this->switchPicture(QString::fromStdString(filename));
        return;
    }

    int x = this->get_x();
    int y = this->get_y();
    if(this->monster->getDirection() == "right")
    {
        x += this->monster->getSpeed();
    }
    else if(this->monster->getDirection() == "left")
    {
        x -= this->monster->getSpeed();
    }
    else if(this->monster->getDirection() == "front")
    {
        y += this->monster->getSpeed();
    }
    else if(this->monster->getDirection() == "back")
    {
        y -= this->monster->getSpeed();
    }
    else if(this->monster->getDirection() == "stop")
    {
        this->hide();
        this->hplabel->hide();
        return;
    }
    int maxhp = monster->getMaxHp();
    int cur_hp = monster->getHp();
    float rate = (float)cur_hp/ (float)maxhp;
    int width = int(rate * this->get_width());
    //qDebug() << cur_hp;
    //qDebug() <<(float)cur_hp;
    this->hplabel->setGeometry(x, y - 10,width, 10);
    this->sldbuff->setGeometry(x,y,50,50);
    this->firebuff->setGeometry(x,y,50,50);
    this->light->setGeometry(x,y,50,50);
    this->frozenbuff->setGeometry(x,y,50,50);
    this->hplabel->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
    this->hplabel->show();
    this->setPosition(x,y);
    if(this->monster->getPosition() != Tile(x/50 , (y - 20)/50))
    {
        if((x % 50 == 0 && (y - 20) % 50 == 0))
        {

            this->monster->setPosition(Tile(x/50, (y - 20)/50));
        }
    }
    emit moved(this->monster->getRank());
    this->switchPicture(QString::fromStdString(filename));
}

void MonsterLabel::changeDirection()
{

    if(!(this->get_x() % 50 == 0 && (this->get_y() - 20) % 50 == 0))
    {
        return;
    }
    int x = this->get_x()/50;
    int y = (this->get_y() - 20)/50;
    int i = 0;
    for(; i < this->route.size(); i++)
    {
        if(route[i].get_x() == x && route[i].get_y() == y)
        {
            break;
        }
    }
    if(i == this->route.size() - 1)
    {
        return;
    }
    else if (i == this->route.size())
    {
        this->monster->changeDirection("stop");
        if(!this->runned)
        {
            emit runed(this->monster->getRank());
            this->runned = true;
            this->monster->runned = true;
        }
        this->hide();
    }
    else
    {
        int j_x = route[i + 1].get_x() - x;
        int j_y = route[i + 1].get_y() - y;
        if(j_x == 1)
        {
            this->monster->changeDirection("right");
        }
        else if(j_x == -1)
        {
            this->monster->changeDirection("left");
        }
        else if(j_y == 1)
        {
            this->monster->changeDirection("front");
        }
        else if(j_y == -1)
        {
            this->monster->changeDirection("back");
        }
        //qDebug() <<j_x <<"," << j_y;
        //qDebug() <<x << "," << y << QString::fromStdString(this->monster->getDirection());
    }
}

void MonsterLabel::action()
{
    movetimer = new QTimer;
    movetimer->setInterval(100);
    connect(movetimer,SIGNAL(timeout()),this,SLOT(monsterMove()));
    movetimer->start();
    attacktimer = new QTimer;
    int time = 1000/this->monster->getFrequence();
    attacktimer->setInterval(time);
    connect(attacktimer,SIGNAL(timeout()),this,SLOT(attackEnemy()));
}


Tile MonsterLabel::getNext()
{
    Tile cur = this->monster->getPosition();
    int i = 0;
    for(; i < this->route.size(); i++)
    {
        if(route[i] == cur)
        {
            break;
        }
    }
    if(i >= this->route.size() - 1)
    {
        return Tile(-1,-1);
    }
    else
    {
        return route[i + 1];
    }
}


void MonsterLabel::attackEnemy()
{
    if(this->stop || this->frozen)
    {
        return;
    }
    else if(this->runned)
    {
        return;
    }
    if(this->find_enemy &&! this->monster->isDead())
    {
        if(this->tower_enemy->isDead())
        {
            this->attacktimer->stop();
            this->tower_enemy = nullptr;
            this->find_enemy = false;
            emit killedEnemy(this->monster->getRank());            
        }
        else if(!this->tower_enemy->insideScale(*this->tower_enemy))
        {
            this->attacktimer->stop();
            this->tower_enemy = nullptr;
            this->find_enemy = false;
            emit killedEnemy(this->monster->getRank());
        }
        else if(this->monster->getScale() > 1)
        {
            //qDebug() << "monster" << this->monster->getRank() << "launch bullet";
            emit launchBullet(this->monster->getRank(),this->tower_enemy->getRank());
        }
        else
        {
            qDebug() << "monster" << this->monster->getRank() << "attack";
            this->monster->attackEnenmy(*this->tower_enemy);
            emit attack(this->tower_enemy->getRank());
        }
    }
}

 void MonsterLabel::getEnemy(Tower* tw)
 {
    if(this->monster->isDead())
    {
        return;
    }
    else if(this->find_enemy)
    {
        return;
    }
    else if(tw->isDead())
    {
        return;
    }
    qDebug() << "I found an enemy!";
    this->find_enemy = true;
    this->tower_enemy = tw;
    this->attacktimer->start();
 }

 void MonsterLabel::updateHp()
 {
    if(this->emit_death)
    {
        return;
    }
    //qDebug() << monster->getHp();
    //qDebug() << monster->getMaxHp();
    float rate = (float)this->monster->getHp()/(float)this->monster->getMaxHp();
    if(this->monster->getHp() == 0)
    {
        this->emit_death = true;
        this->blocked = true;
        this->sldbuff->hide();
        this->firebuff->hide();
        this->light->hide();
        this->frozenbuff->hide();
        emit died(this->monster->getRank());
    }
    this->hplabel->setGeometry(this->get_x(), this->get_y() - 10, this->get_width()*rate , 10);
    this->hplabel->show();
 }

 void MonsterLabel::stopMonster()
 {
    this->stop = true;
 }

 void MonsterLabel::getlighted()
 {
    if(this->monster->isDead())
    {
        return;
    }
    this->light->show();
    this->light->appear();
    qDebug() << "I get lighted";
    QTimer::singleShot(500,[=](){
        this->light->disappear();
        this->light->hide();
    });
 }

 void MonsterLabel::getAttackByBullet(bullet* bptr)
 {
    this->monster->getAttackByBullet(bptr);
    buff* atkbuff = bptr->getBuff();
    if(bptr->hasBuff())
    {
        string buff_name = bptr->getBuff()->getName();
        if(buff_name == "slowdown")
        {
            if(this->monster->getSlowDown() == -1)
            {
                QTimer* sldtimer = new QTimer;
                sldtimer->setInterval(100);
                atkbuff->setTimer(sldtimer);
                connect(sldtimer,SIGNAL(timeout()),this,SLOT(updateSlowDown()));
                qDebug() << "Monster" << this->monster->getRank() << "get slow down";
                this->sldbuff->show();
                movetimer->setInterval(200);
                movetimer->start();
                sldtimer->start();
            }
        }
        else if(buff_name == "fire")
        {
            if(this->monster->getFire() == -1)
            {
                QTimer* sldtimer = new QTimer;
                sldtimer->setInterval(200);
                atkbuff->setTimer(sldtimer);
                connect(sldtimer,SIGNAL(timeout()),this,SLOT(updateFire()));
                qDebug() << "Monster" << this->monster->getRank() << "get fired";
                this->firebuff->show();
                sldtimer->start();
            }
        }
        this->monster->insertBuff(atkbuff);
    }
 }

 void MonsterLabel::updateSlowDown()
 {
    int i = this->monster->getSlowDown();
    if(this->stop)
    {
        return;
    }
    if(i == -1)
    {
        return;
    }
    else
    {
        buff* sld = this->monster->getBuff(i);
        sld->updateBuff(-100);
        if(sld->isEnd())
        {
            movetimer->setInterval(100);
            movetimer->start();
            this->sldbuff->hide();
            sld->getTimer()->stop();
            this->monster->clearBuff(i);
        }
    }
 }

 void MonsterLabel::updateFire()
 {
    int i = this->monster->getFire();
    if(this->stop)
    {
        return;
    }
    if(i == -1)
    {
        return;
    }
    else
    {
        buff* sld = this->monster->getBuff(i);
        sld->updateBuff(-200);
        int curhp = this->monster->getHp() -10;
        if(curhp < 0)
        {
            curhp = 0;
        }
        this->monster->setHp(curhp);
        this->updateHp();
        if(sld->isEnd())
        {
            this->firebuff->hide();
            sld->getTimer()->stop();
            this->monster->clearBuff(i);
        }
    }
 }

 void MonsterLabel::handlebuff(string buffname)
{
    if(this->monster->isDead())
    {
        return;
    }
    buff* attbuff = new buff(buffname);
    this->monster->insertBuff(attbuff);
    QTimer* sldtimer = new QTimer;
    sldtimer->setInterval(100);
    attbuff->setTimer(sldtimer);
    if(buffname == "frozen")
    {
        this->frozen = true;
        this->frozenbuff->show();
        connect(attbuff->getTimer(),SIGNAL(timeout()),this,SLOT(updateFrozen()));    
    }
    else
    {
        connect(attbuff->getTimer(),SIGNAL(timeout()),this,SLOT(updateMad()));
    }
    attbuff->getTimer()->start();
}

 void MonsterLabel::updateFrozen()
 {
    int i = this->monster->getFrozen();
    if(this->stop || this->monster->isDead())
    {
        return;
    }
    if(i == -1)
    {
        return;
    }
    else
    {
        buff* sld = this->monster->getBuff(i);
        sld->updateBuff(-100);
        if(sld->isEnd())
        {
            this->firebuff->hide();
            sld->getTimer()->stop();
            this->monster->clearBuff(i);
            this->frozen = false;
            this->frozenbuff->hide();
        }
    }
 }

 void MonsterLabel::updateMad()
 {
    int i = this->monster->getMad();
    if(this->stop || this->monster->isDead())
    {
        return;
    }
    if(i == -1)
    {
        return;
    }
    else
    {
        buff* sld = this->monster->getBuff(i);
        sld->updateBuff(-100);
        if(sld->isEnd())
        {
            this->firebuff->hide();
            sld->getTimer()->stop();
            this->monster->clearBuff(i);
        }
    }
 }

