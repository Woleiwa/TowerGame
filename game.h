#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "map.h"
#include "myqlabel.h"
#include "monsterlabel.h"
#include <QPainter>
#include "towerlabel.h"
#include "bullet.h"
#include "skill.h"
class Game : public QMainWindow
{
    Q_OBJECT
    int level;
    Map* map;
    MyQLabel* groundmap;
    vector<vector<Tile>> route_line;
    MyQLabel** route;
    MyQLabel* border;
    MyQLabel* mana;
    QMenu *menu;
    bool stop_flag = false;
    MyQLabel* stoplabel;
    MonsterLabel** ml;
    MyQLabel* towerbutton[3];
    vector <Monster*> mlist;
    int mon_num;
    int route_num = 0;
    vector <vector<Monster*>> mlist_on_route;
    vector <int> mindex;
    vector <int> routelist;
    vector <TowerLabel*> tw;
    QTimer* timer;
    QTimer* hptimer;
    int num = 0;
    int choosetower = -1;
    int money = 1000;
    QLabel* mlabel;
    QLabel* scorelabel;
    MyQLabel* selectlevel = nullptr;
    bool occupied[16][16];
    vector<bullet*> blist;
    int score = 500;
    int runed = 0;
    int killed = 0;
    Skill* player_skill[3];
public:
    explicit Game(QWidget *parent = nullptr, int level = 0);
    void setRoute();
    bool getStop() {return stop_flag;};
    void readFromtxt();
    void start();
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool isOnRoad(int x, int y);
    void fail();
    void victory();
signals:
    void put(int x, int y);
    void choose(int x, int y);
    void setTower(int i);
    void setMonster(int i);
    void closed();
    void win(int i, int score);
public slots:
    void hitByBullet(int i, bool direction);
    void getout();
    void stop();
    void reStart();
    void generateMonster();
    void chooseTower(int i);
    void cancelChoose() {this->choosetower = -1;qDebug()<<this->choosetower;};
    void showSelectBox(int x,int y);
    void placeTower(int x, int y);
    void detectMove(int i);
    void detectEnemyForMonster(int i);
    void detectEnemyForMonsterWhenTower(int i);
    void detectEnemyForTower(int i);
    void detectEnemyForTowerWhenMonster(int i);
    void updateHpTower(int i);
    void updateHpMonster(int i);
    void towerLaunchBullet(int l,int t);
    void monsterLaunchBullet(int l, int t);
    void killTower(int i);
    void killMonster(int i);
    void towerLevelUp(int i);
    void levelUp(int i);
    void getRun(int i);
    void handleSkill(string name);
};

#endif // GAME_H
