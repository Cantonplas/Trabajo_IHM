QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    logindialog.cpp \
    registerdialog.cpp \
    selectionwindow.cpp

HEADERS += \
    mainwindow.h \
    logindialog.h \
    registerdialog.h \
    selectionwindow.h

FORMS += \
    mainwindow.ui \
    logindialog.ui \
    registerdialog.ui \
    selectionwindow.ui


INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include

LIBS += -L$$PWD/lib -lnavlib
