#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>
#include "myqlabel.h"
class TestWidget : public QWidget
{
    Q_OBJECT
    MyQLabel* test;
public:
    explicit TestWidget(QWidget *parent = nullptr);

signals:

};

#endif // TESTWIDGET_H
