#-------------------------------------------------
#
# Project created by QtCreator 2015-12-22T15:32:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Group6Interface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    icmekan.cpp \
    DijkstrasAlgorithm.cpp \
    Graph.cpp \
    dismekan.cpp \
    mygraphicsscene.cpp

HEADERS  += mainwindow.h \
    icmekan.h \
    Area.h \
    Define.h \
    Edge.h \
    DijkstrasAlgorithm.h \
    Graph.h \
    Vertex.h \
    dismekan.h \
    mygraphicsscene.h

FORMS    += mainwindow.ui \
    icmekan.ui \
    dismekan.ui
