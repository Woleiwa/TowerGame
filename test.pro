QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attackable.cpp \
    buff.cpp \
    bullet.cpp \
    forgetpassword.cpp \
    game.cpp \
    hpbar.cpp \
    levelup.cpp \
    loading.cpp \
    main.cpp \
    map.cpp \
    md5.cpp \
    monster.cpp \
    monsterlabel.cpp \
    mypushbutton.cpp \
    myqlabel.cpp \
    player.cpp \
    playerlist.cpp \
    register.cpp \
    selectlevel.cpp \
    signin.cpp \
    skill.cpp \
    storyscene.cpp \
    stringlabel.cpp \
    testwidget.cpp \
    tile.cpp \
    tower.cpp \
    towerlabel.cpp \
    widget.cpp

HEADERS += \
    attackable.h \
    buff.h \
    bullet.h \
    forgetpassword.h \
    game.h \
    hpbar.h \
    levelup.h \
    loading.h \
    map.h \
    md5.h \
    monster.h \
    monsterlabel.h \
    mypushbutton.h \
    myqlabel.h \
    player.h \
    playerlist.h \
    register.h \
    selectlevel.h \
    signin.h \
    skill.h \
    storyscene.h \
    stringlabel.h \
    testwidget.h \
    tile.h \
    tower.h \
    towerlabel.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
