#ifndef REGISTER_H
#define REGISTER_H


#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>


class Register : public QWidget
{
    Q_OBJECT;
public:
    Register(QWidget *parent = nullptr);
    ~Register();
    QPushButton *bt;
    QPushButton *bt2;
    QLineEdit* le_username;
    QLineEdit* le_password;
    QLineEdit* le_cor_password;
    QLineEdit* le_phonenum;
    QLabel* lb_username;
    QLabel* lb_password;
    QLabel* lb_cor_password;
    QLabel* lb_phonenum;

public slots:
    void regist();
    void cancel();
};

#endif // REGISTER_H
