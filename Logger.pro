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
    src/eventfilter.cpp \
    src/models/sidebarmodel.cpp

HEADERS += \
    src/mainwindow.h \
    src/filemanager.h \
    src/eventfilter.h \
    src/models/sidebarmodel.h

FORMS += \
    src/mainwindow.ui

win32: LIBS += -lWtsapi32
