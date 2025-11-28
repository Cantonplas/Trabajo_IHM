QT += widgets sql
CONFIG += console
TEMPLATE = app
CONFIG += c++17

TARGET = example_app

SOURCES += \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    logindialog.h \
    mainwindow.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

# Incluir las cabeceras de la librería
INCLUDEPATH += $$PWD/lib/include

# Incluir la librería compilada (libnavlib.a)
LIBS += -L$$PWD/lib -lnavlib







