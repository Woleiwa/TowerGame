#ifndef LOADING_H
#define LOADING_H

#include <QWidget>
#include <QProgressBar>
#include <QTimer>
#include "myqlabel.h"
class Loading: public QWidget
{
    Q_OBJECT;
    QProgressBar * qb;
    int i;
    QTimer* qtimer;
    MyQLabel* title;
public:
    Loading(QWidget* parent = nullptr, int i = 10);
public slots:
    void load();
signals:
    void end();
};

#endif // LOADING_H
