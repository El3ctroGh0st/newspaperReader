#-------------------------------------------------
#
# Project created by QtCreator 2018-02-06T16:49:52
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = newspaperReader
TEMPLATE = app


SOURCES += main.cpp\
        newspaperreader.cpp \
    xmlparser.cpp \
    addsourcedialog.cpp

HEADERS  += newspaperreader.hpp \
    xmlparser.hpp \
    addsourcedialog.hpp

FORMS += \
    addsourcedialog.ui
