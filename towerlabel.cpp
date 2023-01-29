#include "towerlabel.h"


TowerLabel::TowerLabel(QWidget *parent, QString file,int x, int y, int width, int height, Tower* tower)
    :MyQLabel(parent, file, x, y, width, height)
{
    this->tower = tower;
    this->hplabel = new QLabel(parent);
    this->hplabel->setGeometry(x, y - 10, width, 10);
    this->hplabel->setStyleSheet("QLabel{background-color:rgb(0,255,0);}");
    this->hplabel->show();
    this->levelup = new MyQLabel(parent,":/new/prefix3/levelup.png",x - 10 ,y - 30, width + 20, 30);
    this->Madbuff = new MyQLabel(parent,":/new/prefix3/buff/mad.png",x,y,width,height);
    this->Madbuff->hide();
    this->levelup->hide();
}

void TowerLabel::updateHp()
{
    if(this->emit_death)
    {
        return;
    }
    //qDebug() << tower->getHp();
    //qDebug() << tower->getMaxHp();
    float rate = (float)this->tower->getHp()/(float)this->tower->getMaxHp();
    if(this->tower->getHp() == 0)
    {
        this->emit_death = true;
        this->Madbuff->disappear();
        this->levelup->disappear();
        emit died(tower->getRank());
    }
    this->hplabel->setGeometry(this->get_x(), this->get_y() - 10, this->get_width()*rate , 10);
    this->hplabel->show();
}

void TowerLabel::action()
{
    attacktimer = new QTimer;
    int time = 1000/this->tower->getFrequence();
    attacktimer->setInterval(time);
    connect(attacktimer,SIGNAL(timeout()),this,SLOT(attackEnemy()));
}

void TowerLabel::getEnemy(Monster* mst)
{
    if(this->tower->isDead())
    {
        return;
    }
    else if(this->find_enemy)
    {
        return;
    }
    else if(mst->isDead())
    {
        return;
    }
    qDebug() << "Tower found an enemy!";
    this->find_enemy = true;
    this->monster_enemy = mst;
    qDebug() << mst->getRank();
    this->attacktimer->start();
}

void TowerLabel::attackEnemy()
{
    if(this->stop)
    {
        return;
    }
    if(this->find_enemy && !this->tower->isDead())
    {
        if(this->monster_enemy->isDead() || this->monster_enemy->runned)
        {
            this->attacktimer->stop();
            this->monster_enemy = nullptr;
            this->find_enemy = false;
            emit killedEnemy(tower->getRank());
        }
        else if(!this->monster_enemy->insideScale(*this->monster_enemy))
        {
            this->attacktimer->stop();
            this->monster_enemy = nullptr;
            this->find_enemy = false;
            emit killedEnemy(tower->getRank());
        }
        else if(this->tower->getScale() > 1)
        {
            //qDebug() << "Tower" << this->tower->getRank() << "launch bullet";
            emit launchBullet(this->tower->getRank(),this->monster_enemy->getRank());
        }
        else
        {
            qDebug() << "Tower" << this->tower->getRank() << "attack";
            this->tower->attackEnenmy(*this->monster_enemy);
            emit attack(this->monster_enemy->getRank());
        }
    }
}

void TowerLabel::levelUp()
{
    if(this->tower->getLevel() < 3 && this->tower->getHp() > 0)
    {
        this->tower->level_up();
        this->levelup->show();
        this->levelup->disappear();
        this->updateHp();
        string pic_name = ":/new/prefix2/tower/" + this->tower->getName() +"/" + to_string(this->tower->getLevel()) +".png";
        this->switchPicture(QString::fromStdString(pic_name));
        if(this->tower->getLevel() == 3 && this->tower->getName() == "defence")
        {
            this->tower->getBuff()->setTimer(new QTimer());
            this->tower->getBuff()->getTimer()->setInterval(100);
            connect(this->tower->getBuff()->getTimer(),SIGNAL(timeout()),this,SLOT(recover()));
            this->tower->getBuff()->getTimer()->start();
        }
    }
}

void TowerLabel::stopTower()
{
    this->stop = true;
}

void TowerLabel::recover()
{
    if(!this->tower->isDead())
    {
        if(this->tower->getHp() < this->tower->getMaxHp())
        {
            this->tower->setHp(this->tower->getHp() + 20);
        }
        this->updateHp();
    }
}

void TowerLabel::handlebuff(string buffname)
{
    if(this->tower->isDead())
    {
        return;
    }
    buff* attbuff = new buff(buffname);
    this->tower->insertBuff(attbuff);
    QTimer* sldtimer = new QTimer;
    sldtimer->setInterval(100);
    attbuff->setTimer(sldtimer);
    if(buffname == "frozen")
    {
        connect(attbuff->getTimer(),SIGNAL(timeout()),this,SLOT(updateFrozen()));
    }
    else
    {
        this->Madbuff->show();
        connect(attbuff->getTimer(),SIGNAL(timeout()),this,SLOT(updateMad()));
    }
    attbuff->getTimer()->start();
}

void TowerLabel::updateMad()
{
   int i = this->tower->getMad();
   if(this->stop || this->tower->isDead())
   {
       return;
   }
   if(i == -1)
   {
       return;
   }
   else
   {
       buff* sld = this->tower->Attackable::getBuff(i);
       sld->updateBuff(-100);
       if(sld->isEnd())
       {
           this->Madbuff->hide();
           sld->getTimer()->stop();
           this->tower->clearBuff(i);
       }
   }
}
