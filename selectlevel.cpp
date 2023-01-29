#include "selectlevel.h"
#include "widget.h"
#include "game.h"

SelectLevel::SelectLevel(QWidget *parent , Player* player)
    : QWidget(parent)
{
    this->player = player;
    this->setFixedSize(960,640);

    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(":/new/prefix1/background_for_level.jpg");
    QImage fitimgpic=ImgAllbackground.scaled(960,640, Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);
    player->getmy_info();
    int max_level = player->find_max_level();

    this->buttons = new MyPushButton*[32];
    this->label = new StringLabel*[32];
    this->left = new MyPushButton(this,":/new/prefix1/left.png",20, 260, 60, 60);
    this->right = new MyPushButton(this,":/new/prefix1/right.png",880, 260, 60, 60);
    qDebug() << QString::fromStdString(player->get_info().username) << Qt::endl;
    for(int i = 0; i < 32; i++)
    {
        if(i <= max_level)
        {
            int p = i / 4;
            int j = i % 4;
            string num = to_string(i + 1);
            QString cur_label = QString::fromStdString(num);
            if(i < 16)
            {
                this->buttons[i] = new MyPushButton(this,":/new/prefix1/level_button/"+cur_label+".png", j * 200 + 100, p * 140 + 40, 160, 80);
                qDebug() << ":/new/prefix1/level_button/"+cur_label+".png";
                this->buttons[i]->setLevel(i);
                connect(this->buttons[i],SIGNAL(clicked(int)),this,SLOT(startGame(int)));
            }
            else
            {
                this->buttons[i] = new MyPushButton(this,":/new/prefix1/"+cur_label+".png", j * 200 + 1080, p * 140 + 40, 160, 80);
            }
        }
        else
        {
            int p = (i % 16) / 4;
            int j = i % 4;
            if(i < 16)
            {
                this->buttons[i] = new MyPushButton(this,":/new/prefix1/locked_button.png", j * 200 + 100, p * 140 + 40, 160, 80);
            }
            else
            {
                this->buttons[i] = new MyPushButton(this,":/new/prefix1/locked_button.png", j * 200 + 1080, p * 140 + 40, 160, 80);
            }
        }
    }

    this->logout = new MyPushButton(this,":/new/prefix1/logout.png",840,580,100,50);
    connect(logout,SIGNAL(clicked()),this,SLOT(logOut()));
    connect(left,SIGNAL(clicked()),this,SLOT(TurnLeft()));
    connect(right,SIGNAL(clicked()),this,SLOT(TurnRight()));
}

void SelectLevel::logOut()
{
    logout->zoom1();
    logout->zoom2();
    QTimer::singleShot(500,[=](){
    Widget* newlogin = new Widget;
    this->hide();
    newlogin->show();});
}

void SelectLevel::TurnLeft()
{
    this->left->zoom1();
    this->left->zoom2();
    if(this->page < 2)
    {
        int range = this->page* 16;
        int num = 0;
        for(int i = range - 16; i < range; i++)
        {
            int p = num / 4;
            int j = num % 4;
            this->buttons[i]->move(j * 200 - 1080, p * 140 + 40);
            num++;
        }
        this->page++;
        num = 0;
        for(int i = range ; i < range + 16; i++)
        {
            int p = num / 4;
            int j = num % 4;
            this->buttons[i]->move(j * 200 + 100, p * 140 + 40);
            num++;
        }
    }
}

void SelectLevel::TurnRight()
{
    this->right->zoom1();
    this->right->zoom2();
    if(this->page >1)
    {
        int range = this->page* 16;
        this->page--;
        int num = 0;
        for(int i = range - 16; i < range; i++)
        {
            int p = num / 4;
            int j = num % 4;
            this->buttons[i]->move(j * 200 + 1080, p * 140 + 40);
            num++;
        }
        num = 0;
        for(int i = range - 32 ; i < range - 16; i++)
        {
            int p = num / 4;
            int j = num % 4;
            this->buttons[i]->move(j * 200 + 100, p * 140 + 40);
            num++;
        }
    }
}

void SelectLevel::startGame(int i)
{
    qDebug() << i <<Qt::endl;
    this->buttons[i]->zoom1();
    this->buttons[i]->zoom2();
    QTimer::singleShot(300,[=](){
    this->hide();
    Game* g = new Game(nullptr,i);
    g->show();
    connect(g,SIGNAL(win(int,int)),this,SLOT(update(int,int)));
    connect(g,SIGNAL(closed()),this,SLOT(reShow()));
    });
}

void SelectLevel::reShow()
{
    this->show();
}

 void SelectLevel::update(int level, int score)
 {
    this->player->insert_game_info(level + 1,score);
    qDebug() << level << score;
    int max_level = this->player->find_max_level();
    for(int i = 0; i < 32; i++)
    {
        this->buttons[i]->hide();
        if(i <= max_level)
        {
            int p = i / 4;
            int j = i % 4;
            string num = to_string(i + 1);
            QString cur_label = QString::fromStdString(num);
            if(i < 16)
            {
                this->buttons[i] = new MyPushButton(this,":/new/prefix1/level_button/"+cur_label+".png", j * 200 + 100, p * 140 + 40, 160, 80);
                qDebug() << ":/new/prefix1/level_button/"+cur_label+".png";
                this->buttons[i]->setLevel(i);
                connect(this->buttons[i],SIGNAL(clicked(int)),this,SLOT(startGame(int)));
            }
            else
            {
                this->buttons[i] = new MyPushButton(this,":/new/prefix1/"+cur_label+".png", j * 200 + 1080, p * 140 + 40, 160, 80);
            }
        }
        else
        {
            int p = (i % 16) / 4;
            int j = i % 4;
            if(i < 16)
            {
                this->buttons[i] = new MyPushButton(this,":/new/prefix1/locked_button.png", j * 200 + 100, p * 140 + 40, 160, 80);
            }
            else
            {
                this->buttons[i] = new MyPushButton(this,":/new/prefix1/locked_button.png", j * 200 + 1080, p * 140 + 40, 160, 80);
            }
        }
    }
    this->page = 1;
 }
