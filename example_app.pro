QT       += core gui widgets sql svgwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    logindialog.cpp \
    registerdialog.cpp \
    statsdialog.cpp

HEADERS += \
    mainwindow.h \
    logindialog.h \
    registerdialog.h \
    statsdialog.h \
    tool.h

FORMS += \
    mainwindow.ui \
    logindialog.ui \
    registerdialog.ui \
    statsdialog.ui


INCLUDEPATH += $$PWD/lib/include
DEPENDPATH += $$PWD/lib/include

LIBS += -L$$PWD/lib -lnavlib

RESOURCES += \
    resources.qrc \
    resources/resources.qrc \
    ressources.qrc

DISTFILES += \
    resources/carta_nautica.jpg \
    resources/icons/Punto.svg \
    resources/icons/compass_leg.svg \
    resources/icons/ruler.svg \
    resources/icons/transportador.svg
