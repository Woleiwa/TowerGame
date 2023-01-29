#ifndef STRINGLABEL_H
#define STRINGLABEL_H
#include <QTimer>
#include <QWidget>
#include <QLabel>

class StringLabel : public QLabel
{
    Q_OBJECT
    QString content;
    QTimer* timer;
    double opacity = 1.0;
    double apopacity = 0;
public:
    StringLabel(QWidget *parent = nullptr, QString content = "",int x = 0, int y = 0, int width = 0, int height = 0);
    void disappear();
    void appear();
public slots:
    void fadeout();
    void appearin();
};

#endif // STRINGLABEL_H
