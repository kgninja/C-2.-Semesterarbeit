QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ThreeLoses
TEMPLATE = app


SOURCES += main.cpp \
    lifes.cpp \
    playground.cpp \
    playbox.cpp

HEADERS += \
    lifes.h \
    playground.h \
    playbox.h

RESOURCES += \
    images.qrc
