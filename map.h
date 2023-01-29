#ifndef MAP_H
#define MAP_H
//#include "monster.h"
//#include "tower.h"
#include <vector>
#include <QWidget>
#include "tile.h"
using namespace std;

class Map
{
    //vector<Monster> mlist;
    //vector<Tower> tlist;
    vector<Tile> start_point;
    int level;
    QWidget* parent;
    vector<vector<Tile>> route;
    int money = 0;
    int gap = 0;
public:
    Map(int level = 0, QWidget* parent = nullptr);
    void readFromTxt();
    void generateMonster(){};
    //void setTower(Tower tower){};
    vector<vector<Tile>> getRoad(){return this->route;};
    int getMoney() {return this->money;};
    int getGap() {return this->gap;};
};

#endif // MAP_H
