#-------------------------------------------------
#
# Project created by QtCreator 2019-02-26T13:36:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = clusters
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    compute.cpp \
    scanner.cpp \
    graphseparator.cpp \
    common.cpp \
    mainprogram.cpp \
    chordlesscycles.cpp \
    specifyclusters.cpp \
    printclusters.cpp

HEADERS += \
        mainwindow.h \
    compute.h \
    scanner.h \
    graphseparator.h \
    common.h \
    mainprogram.h \
    chordlesscycles.h \
    specifyclusters.h \
    printclusters.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
