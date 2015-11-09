#-------------------------------------------------
#
# Project created by QtCreator 2015-11-04T23:13:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kmeans
TEMPLATE = app


SOURCES += main.cpp\
        Dialog.cpp \
    canvas.cpp

HEADERS  += Dialog.h \
    canvas.h

CONFIG += c++11
