#ifndef SKILL_H
#define SKILL_H
#include "myqlabel.h"
#include <QTimer>
#include "buff.h"
class Skill: public MyQLabel
{
    Q_OBJECT
    string name;
    bool buff_flag = false;
    int cost;
    buff* attach_buff;
    bool target;
    int cd;
    QLabel* cd_bar;
    int cur_cd;
    QTimer* timer;
public:
    Skill(QWidget* parent = nullptr, string name = "", int x = 0, int y = 0, int width = 0, int height = 0);
    void readFromFile();
    int getCost() {return this->cost;};
    string getName() {return this->name;};
    bool hasBuff() {return this->buff_flag;};
    buff getBuff() {return *(this->attach_buff);};
    int getCd() {return this->cd;};
    bool getTarget() {return this->target;};
    void mousePressEvent(QMouseEvent *event);
    void cdBegin();
    QLabel* getcdBar() {return this->cd_bar;};
signals:
    void clicked(string name);
public slots:
    void increaseCd();

};

#endif // SKILL_H
