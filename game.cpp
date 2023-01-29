#include "game.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <fstream>
#include <QThread>
#include<QLabel>
#include<QStatusBar>
#include<QMouseEvent>
#include<QMessageBox>
#include <QApplication>
#include "levelup.h"
#include <QGraphicsEffect>
#include <QMutex>
QMutex detectmutex;

string towerlist[3] = {"magic","defence","arrow"};

Game::Game(QWidget *parent,int level)
    : QMainWindow(parent)
{
    this->level = level;
    this->map = new Map(level,parent);
    this->groundmap = new MyQLabel(this, ":/new/prefix1/mapground.png", 0, 20, 800, 800);
    this->route_line = this->map->getRoad();
    this->money = this->map->getMoney();
    this->mlabel = new QLabel(this);
    this->scorelabel = new QLabel(this);
    string mstr = to_string(this->money);
    QString mstring = QString::fromStdString(mstr);
    string scorestr = "score:" + to_string(this->score);
    QString qscore = QString::fromStdString(scorestr);
    this->mlabel->setText(mstring);
    this->scorelabel->setText(qscore);
    this->setFixedSize(QSize(900, 820));
    this->setRoute();
    this->stoplabel = new MyQLabel(this,":/new/prefix1/stop.png",360,380,80,80);
    this->stoplabel->hide();
    this->border = new MyQLabel(this,":/new/prefix3/border.png",800,20,100,800);
    QAction *actstop = new QAction("暂停");
    QAction *actgetout = new QAction("退出");
    this->menu = menuBar()->addMenu("&菜单");
    menu->addAction(actstop);
    menu->addAction(actgetout);
    connect(actgetout, SIGNAL(triggered(bool)), this, SLOT(getout()));
    connect(actstop, SIGNAL(triggered(bool)), this, SLOT(stop()));
    /*monster = new Monster(1,1,1,Tile(1,1),2,"right","kunkun",20,20);
    string filename = ":/new/prefix1/monster/";
    filename += monster->getName() + "/" + monster->getDirection() + "_";
    string index = to_string(1);
    filename += index + ".png";
    this->ml = new MonsterLabel(this,QString::fromStdString(filename),route_line[0][0].get_x()*50,route_line[0][0].get_y()*50,50,50,monster);
    this->ml->set(route_line[0]);
    this->ml->action();*/
    this->readFromtxt();
    int size = this->mlist.size();
    this->ml = new MonsterLabel*[size];
    this->start();
    this->towerbutton[0] = new MyQLabel(this, ":/new/prefix2/tower/magic/select.png",820,120,60,60);
    this->towerbutton[1] = new MyQLabel(this, ":/new/prefix2/tower/defence/select.png",820,200,60,60);
    this->towerbutton[2] = new MyQLabel(this, ":/new/prefix2/tower/arrow/select.png",820,280,60,60);
    this->mana = new MyQLabel(this,":/new/prefix2/money.png",820,20,60,60);
    this->mlabel->setGeometry(840,70,40,20);
    this->mlabel->setStyleSheet("QLabel{color:white;font: 12pt '华光行楷_CNKI';}");
    this->mlabel->setAlignment(Qt::AlignVCenter);
    this->scorelabel->setGeometry(800,780,80,20);
    this->scorelabel->setStyleSheet("QLabel{color:white;font: 12pt '华光行楷_CNKI';}");
    this->border->raise();
    this->mlabel->raise();
    this->scorelabel->raise();
    this->towerbutton[0]->raise();
    this->towerbutton[1]->raise();
    this->towerbutton[2]->raise();
    this->towerbutton[0]->set_i(0);
    this->towerbutton[1]->set_i(1);
    this->towerbutton[2]->set_i(2);
    connect(this->towerbutton[0],SIGNAL(clicked(int)),this,SLOT(chooseTower(int)));
    connect(this->towerbutton[1],SIGNAL(clicked(int)),this,SLOT(chooseTower(int)));
    connect(this->towerbutton[2],SIGNAL(clicked(int)),this,SLOT(chooseTower(int)));
    connect(this->border,SIGNAL(clicked()),this,SLOT(cancelChoose()));
    connect(this, SIGNAL(choose(int,int)),this,SLOT(showSelectBox(int,int)));
    connect(this,SIGNAL(put(int,int)),this,SLOT(placeTower(int,int)));
    connect(this,SIGNAL(setMonster(int)), this, SLOT(detectEnemyForMonster(int)));
    connect(this,SIGNAL(setTower(int)),this,SLOT(detectEnemyForMonsterWhenTower(int)));
    connect(this,SIGNAL(setTower(int)),this,SLOT(detectEnemyForTower(int)));
    connect(this,SIGNAL(setMonster(int)), this, SLOT(detectEnemyForTowerWhenMonster(int)));
    this->mana->raise();
    for(int i = 0; i < 16; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            this->occupied[i][j] = false;
        }
    }
    this->player_skill[0] = new Skill(this,"attackup",820,360,60,60);
    this->player_skill[1] = new Skill(this,"freeze",820,460,60,60);
    this->player_skill[2] = new Skill(this,"lightning",820,560,60,60);
    for(int i = 0; i < 3; i++)
    {
        connect(this->player_skill[i],SIGNAL(clicked(string)),this,SLOT(handleSkill(string)));
    }
}

void Game::setRoute()
{
    int num = 0;
    for(int i = 0; i < this->route_line.size(); i++)
    {
        num += this->route_line[i].size();
    }
    route = new MyQLabel*[num];
    int cur = 0;
    for(int i = 0; i < this->route_line.size(); i++)
    {
        for(int j = 0; j < this->route_line[i].size(); j++)
        {
            int x = route_line[i][j].get_x();
            int y = route_line[i][j].get_y();
            route[cur] = new MyQLabel(this,":/new/prefix1/road.png", 50 * x, 50 * y + 20, 50, 50);
            cur++;
        }
    }
}

void Game::getout()
{
    emit closed();
    this->close();
}

void Game::stop()
{
    this->stop_flag =true;
    this->stoplabel->show();
    this->stoplabel->raise();
    for(int i = 0; i < this->num;i++)
    {
        this->ml[i]->stopMonster();
    }
    for(int i = 0; i < this->tw.size(); i++)
    {
        this->tw[i]->stopTower();
    }
    for(int i = 0; i < this->blist.size(); i++)
    {
        this->blist[i]->stopBullet();
    }
    connect(stoplabel,SIGNAL(clicked()),this,SLOT(reStart()));
}

void Game::reStart()
{
    this->stoplabel->zoom1();
    this->stoplabel->zoom2();
    QTimer::singleShot(500,[=](){
    this->stop_flag =false;
    for(int i = 0; i < this->num;i++)
    {
        this->ml[i]->restart();
    }
    for(int i = 0; i < this->tw.size(); i++)
    {
        this->tw[i]->restart();
    }
    for(int i = 0; i < this->blist.size(); i++)
    {
        this->blist[i]->restart();
    }
    this->stoplabel->hide();
    });
}

void Game::readFromtxt()
{
    string file = "E://code/test/level/" + to_string(this->level + 1) + ".txt";
    ifstream gamefile(file);
    while(!gamefile.fail())
    {
        char buffer[1024];
        gamefile.getline(buffer,1023);
        string line(buffer);
        if(line.length() != 0)
        {
            int mid = line.find(" ");
            string name(line, 0, mid);
            string route(line, mid + 1, line.length() - mid - 1);
            int r = stoi(route);
            if(r > this->route_num)
            {
                this->route_num = r;
            }
            Monster* mst = new Monster(name, this->route_line[r - 1][0]);
            this->mlist.push_back(mst);
            this->routelist.push_back(r);
        }
    }
    this->mon_num = mlist.size();
    for(int i = 0; i < this->route_num; i++)
    {
        vector<Monster*>m;
        this->mlist_on_route.push_back(m);
        this->mindex.push_back(0);
    }
    for(int i = 0; i < this->mon_num; i++)
    {
        int r = this->routelist[i];
        this->mlist_on_route[r - 1].push_back(this->mlist[i]);
    }
}

void Game::start()
{
    this->timer = new QTimer;
    this->timer->setInterval(this->map->getGap() * 1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(generateMonster()));
    timer->start();
}

void Game::generateMonster()
{
    if(this->stop_flag)
    {
        return;
    }
    for(int i = 0; i < this->route_num; i++)
    {
        if(this->num < this->mon_num)
        {
            Monster* mon = this->mlist_on_route[i][this->mindex[i]];
            this->mindex[i] += 1;
            string filename = ":/new/prefix1/monster/";
            mon->changeDirection("front");
            filename += mon->getName() + "/" + mon->getDirection() + "_";
            string index = to_string(1);
            filename += index + ".png";
            this->ml[this->num] = new MonsterLabel(this,QString::fromStdString(filename),route_line[i][0].get_x()*50,route_line[i][0].get_y()*50 + 20,50,50,mon);
            this->ml[this->num]->setRank(this->num);
            this->ml[this->num]->set(route_line[i]);
            //qDebug()<<QString::fromStdString(mon->getName());
            this->ml[this->num]->show();
            this->ml[this->num]->action();
            connect(this->ml[this->num],SIGNAL(moved(int)),this,SLOT(detectMove(int)));
            connect(this->ml[this->num],SIGNAL(moved(int)),this,SLOT(detectEnemyForMonster(int)));
            connect(this->ml[this->num],SIGNAL(attack(int)),this, SLOT(updateHpTower(int)));
            connect(this->ml[this->num],SIGNAL(killedEnemy(int)),this,SLOT(detectMove(int)));
            connect(this->ml[this->num],SIGNAL(moved(int)),this,SLOT(detectEnemyForTowerWhenMonster(int)));
            connect(this->ml[this->num],SIGNAL(died(int)),this,SLOT(killMonster(int)));
            connect(this->ml[this->num],SIGNAL(launchBullet(int,int)),this,SLOT(monsterLaunchBullet(int,int)));
            connect(this->ml[this->num],SIGNAL(runed(int)),this,SLOT(getRun(int)));
            this->num++;
            this->border->raise();
            this->towerbutton[0]->raise();
            this->towerbutton[1]->raise();
            this->towerbutton[2]->raise();
            this->mana->raise();
            this->mlabel->raise();
            this->scorelabel->raise();
            qDebug() << "Raise Skill";
            this->player_skill[0]->raise();
            this->player_skill[1]->raise();
            this->player_skill[2]->raise();
            this->player_skill[0]->getcdBar()->raise();
            this->player_skill[1]->getcdBar()->raise();
            this->player_skill[2]->getcdBar()->raise();
        }
        else
        {
            this->timer->stop();
        }
    }
}

void Game::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    /*qDebug() << "Paint" << this->num;
    QBrush brush;
    brush.setColor(Qt::red);//把刷子设置为红色
    painter.setBrush(brush);
    for(int i = 0; i < this->num; i++)
    {
        MonsterLabel* mlabel = ml[i];
        Monster* mst = mlist[i];
        float rate = 1.0* mst->getHp()/mst->getMaxHp();
        painter.drawRect(mlabel->get_x(), mlabel->get_y() - 5, mlabel->get_width() * rate, 5);
    }*/
}

void Game::chooseTower(int i)
{
    this->towerbutton[i]->zoom1();
    this->towerbutton[i]->zoom2();
    this->choosetower = i;
    //qDebug()<<this->choosetower;
}

void Game::mouseMoveEvent(QMouseEvent* event)
{
    int x = event->position().x();
    int y = event->position().y();
    if(this->choosetower != - 1)
    {
        //qDebug() << x;
        //qDebug() << y;
        emit choose(x,y);

    }
}

void Game::mouseReleaseEvent(QMouseEvent *event)
{
    int x = event->position().x();
    int y = event->position().y();
    if(this->choosetower != - 1)
    {
        if(this->selectlevel != nullptr)
        {
            this->selectlevel->hide();
            delete this->selectlevel;
            this->selectlevel = nullptr;
        }
        emit put(x, y);
    }
}

void Game::showSelectBox(int x,int y)
{
    x /= 50;
    y = (y - 20)/50;
    if(x >= 0 && x < 16 && y >= 0 && y < 16)
    {
        if(this->selectlevel != nullptr)
        {
            this->selectlevel->hide();
            delete this->selectlevel;
            this->selectlevel = nullptr;
        }
        //qDebug() << "show";
        this->selectlevel = new MyQLabel(this, ":/new/prefix3/selectbox.png", x * 50, y * 50 + 20, 50 ,50);
        this->selectlevel->show();
    }
}

void Game::placeTower(int x, int y)
{
    if(this->stop_flag)
    {
        return;
    }
    if(this->choosetower != -1)
    {
        x /= 50;
        y = (y - 20)/50;
        if(x >= 0 && x < 16 && y >= 0 && y < 16)
        {
            string name = towerlist[choosetower];
            Tower* tw = new Tower(name);
            if(tw->getScale() != 1 && this->isOnRoad(x, y))
            {
                return;
            }
            else if(tw->getScale() == 1 && !this->isOnRoad(x, y))
            {
                return;
            }
            else if(this->occupied[x][y])
            {
                return;
            }
            else if(tw->getPrice() > this->money)
            {
                this->choosetower = -1;
                QMessageBox::warning(this, "No enough money!", "你没有足够的马娜！", QMessageBox::Open);
                return;
            }
            string pic_name = ":/new/prefix2/tower/" + name +"/1.png";
            tw->setPosition(Tile(x,y));
            TowerLabel* tlb = new TowerLabel(this,QString::fromStdString(pic_name), x * 50 , y * 50 + 20, 50, 50, tw);
            tlb->action();
            tlb->set_i(this->tw.size());
            connect(tlb,SIGNAL(died(int)),this,SLOT(killTower(int)));
            this->money -= tw->getPrice();
            tw->setRank(this->tw.size());
            string mstr = to_string(this->money);
            QString mstring = QString::fromStdString(mstr);
            this->mlabel->setText(mstring);
            tlb->show();
            this->tw.push_back(tlb);
            connect(tlb,SIGNAL(killedEnemy(int)),this,SLOT(detectEnemyForTower(int)));
            connect(tlb,SIGNAL(attack(int)),this, SLOT(updateHpMonster(int)));
            connect(tlb,SIGNAL(launchBullet(int,int)),this,SLOT(towerLaunchBullet(int,int)));
            connect(tlb,SIGNAL(clicked(int)),this,SLOT(towerLevelUp(int)));
            emit setTower(this->tw.size() - 1);
            this->occupied[x][y] = true;
            this->choosetower = -1;
        }

    }
}

bool Game::isOnRoad(int x, int y)
{
    Tile cur(x,y);
    for(int i =0 ;i < this->route_line.size(); i++)
    {
        for (int j = 0; j < this->route_line[i].size(); j++)
        {
            if(cur == route_line[i][j])
            {
                return true;
            }
        }
    }
    return false;
}

void Game::detectMove(int i)
{
    Tile next = this->ml[i]->getNext();
    Tile cur = this->ml[i]->getMonster()->getPosition();
    //qDebug() << "monster" << i <<"moved";
    if(next.get_x() >= 0)
    {
        if(this->occupied[next.get_x()][next.get_y()])
        {
            this->ml[i]->block();
            qDebug() << "monster" << i <<"blocked by next";
            qDebug() << next.get_x() << next.get_y();
            qDebug() << cur.get_x() << cur.get_y();
        }
        else if(this->occupied[cur.get_x()][cur.get_y()])
        {
            this->ml[i]->block();
            qDebug() << "monster" << i <<"blocked";
        }
        else
        {
            this->ml[i]->setfree();
        }
    }
}

void Game::detectEnemyForMonster(int mst)
{
    if(this->stop_flag)
    {
        return;
    }
    MonsterLabel* curmonster = this->ml[mst];
    if(curmonster->findEnemy())
    {
        return;
    }
    int distance = 0x7fffffff;
    int index = -1;
    for(int i = 0; i < this->tw.size(); i++)
    {
        if(tw[i]->getTower()->isDead())
        {
            continue;
        }
        if(curmonster->getMonster()->insideScale(*tw[i]->getTower()))
        {
            if(curmonster->getMonster()->getScale() == 1 && tw[i]->getTower()->getScale() != 1)
            {
                continue;
            }
            int newdistance = curmonster->getMonster()->getDistance(*tw[i]->getTower());
            if(newdistance < distance)
            {
                distance = newdistance;
                index = i;
            }
        }
    }

    if(index != -1)
    {

        curmonster->getEnemy(tw[index]->getTower());
        //qDebug() << "monster" << mst << "find enemy" << index;
    }
}

void Game::detectEnemyForMonsterWhenTower(int i)
{
    if(this->stop_flag)
    {
        return;
    }
    Tower* curtower = this->tw[i]->getTower();
    for(int i = 0; i < this->num; i++)
    {
        if(!this->ml[i]->findEnemy())
        {
            if(this->ml[i]->getMonster()->insideScale(*curtower))
            {
                if(this->ml[i]->getMonster()->getScale() == 1 && curtower->getScale() != 1)
                {
                    continue;
                }
                this->ml[i]->getEnemy(curtower);
            }
        }
    }
}

void Game::updateHpTower(int i)
{
    this->tw[i]->updateHp();
}

void Game::updateHpMonster(int i)
{
    this->ml[i]->updateHp();
}

void Game::killTower(int i)
{
    Tile position = this->tw[i]->getTower()->getPosition();
    this->occupied[position.get_x()][position.get_y()] = false;
    this->tw[i]->disappear();
}

void Game::killMonster(int i)
{
    this->killed++;
    this->ml[i]->disappear();
    this->money += this->ml[i]->getMonster()->getValue();
    string mstr = to_string(this->money);
    QString mstring = QString::fromStdString(mstr);
    this->mlabel->setText(mstring);
    this->score += this->ml[i]->getMonster()->getValue() * 10;
    string scorestr = "score:" + to_string(this->score);
    QString qscore = QString::fromStdString(scorestr);
    this->scorelabel->setText(qscore);
    if(this->killed + this->runed == this->mlist.size())
    {
        this->victory();
    }
}

void Game::detectEnemyForTower(int j)
{
    detectmutex.lock();
    if(this->stop_flag)
    {
        return;
        detectmutex.unlock();
    }
    TowerLabel* curtower = this->tw[j];
    int distance = 0x7fffffff;
    int index = -1;
    qDebug() << "Tower" << j << ":" << curtower->getTower()->getPosition().get_x() << curtower->getTower()->getPosition().get_y();
    if(!curtower->findEnemy())
    {
        for(int i = 0; i < this-> num; i++)
        {
            int newdistance = curtower->getTower()->getDistance(*(this->ml[i]->getMonster()));
            qDebug() << "Monster" << i << "distance" << newdistance;
            if(curtower->getTower()->insideScale(*(this->ml[i]->getMonster())) && !(this->ml[i]->getMonster()->isDead()||this->ml[i]->getMonster()->runned))
            {
                if(newdistance < distance)
                {
                    index = i;
                    distance = newdistance;
                }
            }
        }
    }
    if(index != -1)
    {
        qDebug() <<"find enemy at distance" <<distance;
        curtower->getEnemy(this->ml[index]->getMonster());
        qDebug() << "find enemy" << index << this->ml[index]->getMonster()->getPosition().get_x() <<this->ml[index]->getMonster()->getPosition().get_y();
    }
    detectmutex.unlock();
}

void Game::detectEnemyForTowerWhenMonster(int j)
{
    if(this->stop_flag)
    {
        return;
    }
    MonsterLabel* curmonster = this->ml[j];

    for(int i = 0; i < this->tw.size(); i++)
    {
        if(!this->tw[i]->findEnemy())
        {
            if(this->tw[i]->getTower()->insideScale(*curmonster->getMonster()))
            {
                qDebug() << "Monster" << j <<"InsideScale";
                qDebug() << "Tower" << i;
                detectEnemyForTower(i);
            }
        }
    }
}

void Game::towerLaunchBullet(int l,int t)
{
    Tower* curtower = this->tw[l]->getTower();
    bullet* b = new bullet(this,curtower->getType(),curtower->getAttack(),this->tw[l],this->ml[t]);
    if(curtower->getAtkBuff() != nullptr)
    {
        b->attachBuff(curtower->getAtkBuff());
    }
    this->blist.push_back(b);
    b->setIndex_l(l);
    b->setIndex_t(t);
    b->setDirection(true);
    b->setRank(blist.size() - 1);
    b->start();
    connect(b, SIGNAL(hit(int,bool)),this,SLOT(hitByBullet(int, bool)));
    this->border->raise();
    this->towerbutton[0]->raise();
    this->towerbutton[1]->raise();
    this->towerbutton[2]->raise();
    this->mana->raise();
    this->mlabel->raise();
    this->scorelabel->raise();
    this->player_skill[0]->raise();
    this->player_skill[1]->raise();
    this->player_skill[2]->raise();
    this->player_skill[0]->getcdBar()->raise();
    this->player_skill[1]->getcdBar()->raise();
    this->player_skill[2]->getcdBar()->raise();
}

void Game::monsterLaunchBullet(int l, int t)
{
    Monster* curmonster = this->ml[l]->getMonster();
    bullet* b = new bullet(this,curmonster->getType(),curmonster->getAttack(),this->ml[l],this->tw[t]);
    this->blist.push_back(b);
    b->setIndex_l(l);
    b->setIndex_t(t);
    b->setDirection(false);
    b->setRank(blist.size() - 1);
    b->start();
    connect(b, SIGNAL(hit(int,bool)),this,SLOT(hitByBullet(int, bool)));
    this->border->raise();
    this->towerbutton[0]->raise();
    this->towerbutton[1]->raise();
    this->towerbutton[2]->raise();
    this->mana->raise();
    this->mlabel->raise();
    this->scorelabel->raise();
    this->player_skill[0]->raise();
    this->player_skill[1]->raise();
    this->player_skill[2]->raise();
    this->player_skill[0]->getcdBar()->raise();
    this->player_skill[1]->getcdBar()->raise();
    this->player_skill[2]->getcdBar()->raise();
}

void Game::hitByBullet(int i, bool direction)
{
    int t = this->blist[i]->getIndex_t();

    if(direction)
    {
        //qDebug() << "bullet" << i <<"hit monster" << t;
        this->ml[t]->getAttackByBullet(this->blist[i]);
        updateHpMonster(t);
    }
    else
    {
        //qDebug() << "bullet" << i <<"hit tower" << t;
        this->tw[t]->getTower()->getAttackByBullet(this->blist[i]);
        updateHpTower(t);
    }
}

void Game::towerLevelUp(int i)
{
    if(this->stop_flag)
    {
        return;
    }
    if(this->tw[i]->getTower()->getLevel() >= 3)
    {
        QMessageBox::warning(this, "Max Level!", "已到最高等级！", QMessageBox::Open);
        return;
    }
    LevelUp* lvup = new LevelUp(nullptr,this->tw[i]->getTower());
    lvup->show();
    connect(lvup,SIGNAL(levelup(int)),this,SLOT(levelUp(int)));
}

void Game::levelUp(int i)
{
    if(this->money < this->tw[i]->getTower()->getPriceForLevelUp())
    {
        QMessageBox::warning(this, "No enough money!", "你没有足够的马娜！", QMessageBox::Open);
        return;
    }
    else
    {
        this->tw[i]->levelUp();
        this->money-= this->tw[i]->getTower()->getPriceForLevelUp();
        string mstr = to_string(this->money);
        QString mstring = QString::fromStdString(mstr);
        this->mlabel->setText(mstring);
    }
}

void Game::getRun(int i)
{
    this->score -= this->ml[i]->getMonster()->getValue() * 10;
    string scorestr = "score:" + to_string(this->score);
    QString qscore = QString::fromStdString(scorestr);
    this->scorelabel->setText(qscore);
    this->runed++;
    if(this->score <= 0)
    {
        this->fail();
    }
    else if(this->killed + this->runed == this->mlist.size())
    {
        this->victory();
    }
}

void Game::fail()
{
    this->stop_flag =true;
    for(int i = 0; i < this->num;i++)
    {
        this->ml[i]->stopMonster();
    }
    for(int i = 0; i < this->tw.size(); i++)
    {
        this->tw[i]->stopTower();
    }
    for(int i = 0; i < this->blist.size(); i++)
    {
        this->blist[i]->stopBullet();
    }
    MyQLabel* failable = new MyQLabel(this,":/new/prefix3/fail.png",300,370,200,100);
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    effect->setOpacity(0);
    failable->setGraphicsEffect(effect);
    failable->show();
    failable->appear();
    QTimer::singleShot(3000,[=](){
        emit closed();
        this->close();
    });
}

void Game::victory()
{
    this->stop_flag =true;
    for(int i = 0; i < this->num;i++)
    {
        this->ml[i]->stopMonster();
    }
    for(int i = 0; i < this->tw.size(); i++)
    {
        this->tw[i]->stopTower();
    }
    for(int i = 0; i < this->blist.size(); i++)
    {
        this->blist[i]->stopBullet();
    }
    MyQLabel* winlable = new MyQLabel(this,":/new/prefix3/win.png",300,370,200,100);
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    effect->setOpacity(0);
    winlable->setGraphicsEffect(effect);
    winlable->show();
    winlable->appear();
    QTimer::singleShot(3000,[=](){
        emit win(this->level,this->score);
        emit closed();
        this->close();
    });
}

void Game::handleSkill(string name)
{
    for(int i = 0; i < 3; i++)
    {
        if(this->player_skill[i]->getName() == name)
        {
            if(this->money < this->player_skill[i]->getCost())
            {
                QMessageBox::warning(this, "No enough money!", "你没有足够的马娜！", QMessageBox::Open);
                return;
            }
            this->money -= this->player_skill[i]->getCost();
            string mstr = to_string(this->money);
            QString mstring = QString::fromStdString(mstr);
            this->mlabel->setText(mstring);
            this->player_skill[i]->cdBegin();
            if(name == "lightning")
            {
                for(int i = 0; i < this->num; i++)
                {
                    Monster* curmonster = this->ml[i]->getMonster();
                    this->ml[i]->getlighted();
                    curmonster->setHp(curmonster->getHp() - 100);
                    this->ml[i]->updateHp();
                }
            }
            else if(name == "freeze")
            {
                for(int i = 0; i < this->num; i++)
                {
                    Monster* curmonster = this->ml[i]->getMonster();
                    curmonster->setHp(curmonster->getHp() - 20);
                    this->ml[i]->updateHp();
                }
            }
            if(this->player_skill[i]->hasBuff())
            {
                string buffname = this->player_skill[i]->getBuff().getName();
                if(this->player_skill[i]->getTarget())
                {
                    for(int i = 0; i < this->tw.size();i++)
                    {
                        this->tw[i]->handlebuff(buffname);
                    }
                }
                else
                {
                    for(int i = 0; i < this->num; i++)
                    {
                        this->ml[i]->handlebuff(buffname);
                    }
                }
            }
        }
    }
}
