#include "storyscene.h"
#include <QTimer>
#include <QGraphicsEffect>
StoryScene::StoryScene(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(960,640);
    this->pass = new MyPushButton(this,":/new/prefix1/pass.png",910,590,40,40);

    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(":/new/prefix1/background.png");
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
    passLabel = new QLabel("跳过",this);
    passLabel->setStyleSheet("QLabel{color: white;font: 18pt '华光行楷_CNKI';}");
    passLabel->setGeometry(850,590,60,40);
    files[0] = ":/new/prefix1/story1.jpg";
    files[1] = ":/new/prefix1/story2.png";
    files[2] = ":/new/prefix1/story3.png";
    storycontent[0] = "你生活在一个叫艾路维特的国家的边境小城里。\n曾经你们的生活是如此的平静，直到城中发现了一种魔法矿石——马娜。\n这矿石十分的珍贵，它可以给锻造之物带来魔法之力，\n城镇因为贩卖矿石变得富裕繁华了起来，居民的生活也越来越滋润。";
    storycontent[1] = "然而有一天，魔界的斥候发现了城中的秘密，它将马娜的存在告诉了魔界之王维鲁斯。\n贪婪的维鲁斯十分渴望马娜的力量，于是便率领魔兽大军进犯城市。\n原本平静的生活被打破，魔兽大军所到之处，生灵涂炭，城市危在旦夕。";
    storycontent[2] = "在城中守军的背水一战之下，魔兽的进攻被一次又一次击退。\n可是光靠守军的英勇作战是无法永久守住城池的，于是曾经在首都学习建筑和魔法的你必\n须站出来，为城市修筑防御塔，在魔兽大军的道路上抵挡他们的进攻，减少守军的伤亡。\n城里的人们相信，在防御塔的守护之下，魔兽的进攻终究会被击退，安宁的生活也会再次\n降临。";
    this->title = new MyQLabel(this,files[i],0,0,960,640);
    this->story = new StringLabel(this,storycontent[i],10,10,940,180);
    story->setStyleSheet("QLabel{color: white;font: 18pt '华光行楷_CNKI';}");
    pass->raise();
    passLabel->raise();
    connect(title,SIGNAL(clicked()),this,SLOT(switchContent()));
    connect(pass,SIGNAL(clicked()),this,SLOT(passStory()));
}

void StoryScene::switchContent()
{
    if(i < 2)
    {
        title->disappear();
        story->disappear();
        QTimer::singleShot(300,[=](){
            i++;
            MyQLabel* newtitle = new MyQLabel(this,files[i],0,0,960,640);
            StringLabel* newstory = new StringLabel(this,storycontent[i],10,10,940,180);
            newstory->setStyleSheet("QLabel{color: white;font: 18pt '华光行楷_CNKI';}");
            QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
            effect->setOpacity(0);
            newtitle->setGraphicsEffect(effect);
            newstory->setGraphicsEffect(effect);
            newtitle->show();
            newstory->show();
            pass->raise();
            passLabel->raise();

            newtitle->appear();
            newstory->appear();
            QTimer::singleShot(1000,[=](){
                delete title;
                delete story;
                this->title = newtitle;
                this->story = newstory;
                pass->raise();
                passLabel->raise();
                connect(title,SIGNAL(clicked()),this,SLOT(switchContent()));});
            });
    }
    else
    {
        this->passStory();
    }
}

void StoryScene::passStory()
{
    pass->zoom1();
    pass->zoom2();
    QTimer::singleShot(300,[=](){
    emit passed();
    this->close();});
}
