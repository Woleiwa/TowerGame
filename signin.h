#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include "player.h"
QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class SignIn: public QWidget
{
    Q_OBJECT;
public:
    SignIn(QWidget *parent = nullptr);
    ~SignIn() {};
    QPushButton *bt;
    QPushButton *bt2;
    QCheckBox *cbx;
    QLineEdit* le_username;
    QLineEdit* le_password;
    QLabel* lb_username;
    QLabel* lb_password;
    bool sign = false;
public slots:
    bool signIn();
    void forgetPassword();
signals:
    void signin(Player* player);
};

#endif // SIGNIN_H
