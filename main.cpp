

#include <QApplication>


//#define _DEBUG_

#ifndef _DEBUG_
#include "widget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
#endif

#ifdef _DEBUG_
#include "testwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestWidget tw;
    tw.show();
    return a.exec();
}
#endif
