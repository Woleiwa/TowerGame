#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
class ForgetPassword : public QWidget
{
    Q_OBJECT
public:
    ForgetPassword(QWidget *parent = nullptr);

    QPushButton *bt;
    QLineEdit* le_username;
    QLineEdit* le_password;
    QLineEdit* le_cor_password;
    QLineEdit* le_phonenum;
    QLabel* lb_username;
    QLabel* lb_password;
    QLabel* lb_cor_password;
    QLabel* lb_phonenum;
public slots:
    void modifyPassword();

};

#endif // FORGETPASSWORD_H
