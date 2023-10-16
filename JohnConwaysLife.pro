QT += core gui
QT += widgets

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    DataWorker/dataworker.h \
    Interface/LED/led.h \
    Interface/LifeWidget/lifewidget.h \
    Interface/SettingWindow/ColorData/colordata.h \
    Interface/SettingWindow/settingdialog.h \
    Interface/mainwindow.h \
    Model/Life.h \
    Model/Pair.h

SOURCES += \
        DataWorker/dataworker.cpp \
        Interface/LED/led.cpp \
        Interface/LifeWidget/lifewidget.cpp \
        Interface/SettingWindow/settingdialog.cpp \
        Interface/mainwindow.cpp \
        Model/Life.cpp \
        main.cpp

FORMS += \
    Interface/SettingWindow/settingdialog.ui \
    Interface/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
