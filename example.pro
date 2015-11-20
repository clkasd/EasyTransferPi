#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T08:23:51
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = example
CONFIG   += console
CONFIG   -= app_bundle
CONFIG +=serialport
TEMPLATE = app


SOURCES += main.cpp \
    serialportmanager.cpp \
    actionhandler.cpp \
    easytransferpi.cpp

HEADERS += \
    serialportmanager.h \
    actionhandler.h \
    easytransferpi.h
