#ifndef STORYSCENE_H
#define STORYSCENE_H

#include <QWidget>
#include "myqlabel.h"
#include "mypushbutton.h"
#include "stringlabel.h"
class StoryScene : public QWidget
{
    Q_OBJECT
    MyQLabel *title;
    MyPushButton* pass;
    StringLabel* story;
    QLabel *passLabel;
    int i = 0;
    QString files[3];
    QString storycontent[3];
public:
    explicit StoryScene(QWidget *parent = nullptr);

public slots:
    void switchContent();
    void passStory();
signals:
    void passed();
};

#endif // STORYSCENE_H
