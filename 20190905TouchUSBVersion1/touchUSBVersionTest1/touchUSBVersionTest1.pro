#-------------------------------------------------
#
# Project created by QtCreator 2019-09-05T11:23:25
#
#-------------------------------------------------

QT       += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = touchUSBVersionTest1
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    touchusbnode.cpp \
    conio.c \
    cglobal.cpp \
    glgragh.cpp

HEADERS += \
        mainwindow.h \
    touchusbnode.h \
    conio.h \
    hdDevice.h \
    cglobal.h \
    glgragh.h

FORMS += \
        mainwindow.ui

unix:!macx: LIBS += -lHDU -lHD -lHL -lQH -lPhantomIOLib42
LIBS += -lglut -lGL -lGLU -lGLEW

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
