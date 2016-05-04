#-------------------------------------------------
#
# Project created by QtCreator 2016-03-15T23:48:51
#
#-------------------------------------------------

QT       += core gui webenginewidgets printsupport

# greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SMART-GUI-V2
TEMPLATE = app

SOURCES += main.cpp\
           mainwindow.cpp \
           selectalgwindow.cpp \
           addalgo.cpp \
           setupwindow.cpp

HEADERS += mainwindow.h \
           selectalgwindow.h \
           addalgo.h \
           setupwindow.h

FORMS   += mainwindow.ui \
           selectalgwindow.ui \
           addalgo.ui \
           setupwindow.ui

RESOURCES += \
           chartfile.qrc