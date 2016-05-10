#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T18:02:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NeedlemanWunschAlgorithm
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    linearneedlemanwunsch.cpp

HEADERS  += mainwindow.h \
    linearneedlemanwunsch.h

FORMS    += mainwindow.ui
CONFIG += c++11
