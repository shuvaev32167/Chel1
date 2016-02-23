#-------------------------------------------------
#
# Project created by QtCreator 2016-02-17T17:35:39
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Chel1

TEMPLATE = app

QMAKE_CXXFLAGS +=   -std=c++1y\
                    -O3\
                    -fopenmp\
                    -pthread

SOURCES += main.cpp\
        MainWindow.cpp \
    Trigon.cpp \
    Weight.cpp \
    Settings.cpp

HEADERS  += MainWindow.h \
    Trigon.h \
    Weight.h \
    Settings.h

FORMS    += MainWindow.ui

LIBS    += -L/usr/lib/gcc/x86_64-linux-gnu/5/ -lgomp
