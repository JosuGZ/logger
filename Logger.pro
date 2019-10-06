#-------------------------------------------------
#
# Project created by QtCreator 2016-08-10T16:48:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Logger
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/filemanager.cpp \
    src/models/sidebarmodel.cpp
win32: SOURCES += \
    src/eventfilter.cpp

HEADERS += \
    src/mainwindow.h \
    src/filemanager.h \
    src/models/sidebarmodel.h
win32: HEADERS += \
    src/eventfilter.h

FORMS += \
    src/mainwindow.ui

win32: LIBS += -lWtsapi32
