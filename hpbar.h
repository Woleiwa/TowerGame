#ifndef HPBAR_H
#define HPBAR_H

#include <QWidget>
#include <QProgressBar>
class HpBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit HpBar(QWidget *parent = nullptr, int x = 0, int y = 0, int width = 0, int height = 0);
    void setvalue(int value);
    void changecolor();
signals:

};

#endif // HPBAR_H
