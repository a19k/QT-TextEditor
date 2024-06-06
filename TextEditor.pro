#-------------------------------------------------
#
# Project created by QtCreator 2003-08-27T06:09:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    find.cpp \
    replace.cpp

HEADERS  += mainwindow.h \
    find.h \
    replace.h

FORMS    += mainwindow.ui \
    find.ui \
    replace.ui

RESOURCES += \
    icons.qrc
