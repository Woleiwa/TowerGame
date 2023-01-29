#ifndef BULLET_H
#define BULLET_H

#include <QWidget>
#include "myqlabel.h"
#include "buff.h"
using namespace std;
class bullet : public MyQLabel
{
    Q_OBJECT
    string type;
    MyQLabel* luncher;
    MyQLabel* target;
    QTimer* movetimer;
    int atk;
    double f_x;
    double f_y;
    int rank;
    bool direction;
    int index_l;
    int index_t;
    bool stop = false;
    bool get_buff = false;
    buff* atk_buff = nullptr;
public:
    explicit bullet(QWidget *parent = nullptr, string type = "", int atk = 0, MyQLabel* luncher = nullptr, MyQLabel* target = nullptr);
    void start();
    void setRank(int i) {this->rank = i;};
    void setDirection(bool d) {this->direction = d;};
    void setIndex_l(int i) {this->index_l = i;};
    void setIndex_t(int i) {this->index_t = i;};
    bool getDirection() {return this->direction;}
    int getIndex_l() {return this->index_l;};
    int getIndex_t() {return this->index_t;};
    int getAtk() {return this->atk;};
    void stopBullet();
    void restart(){this->stop = false;}
    bool hasBuff() {return this->get_buff;};
    buff* getBuff() {return this->atk_buff;};
    void attachBuff(buff* atkbuff);
signals:
    void hit(int i, bool direction);
public slots:
    void moveTowards();
};

#endif // BULLET_H
