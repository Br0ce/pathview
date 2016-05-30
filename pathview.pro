# pathview.pro

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = pathview

CONFIG += c++11
CONFIG += release
# CONFIG += debug

INCLUDEPATH += ./hdr/
INCLUDEPATH += /usr/include/eigen3
INCLUDEPATH += /usr/local/include/eigen3

DESTDIR=bin #Target file directory
OBJECTS_DIR=gen_bin #Intermediate object files directory
MOC_DIR=gen_bin #Intermediate moc files directory

# Input
HEADERS += hdr/main_window.h \
           hdr/field.h \
           hdr/graph.h \
           hdr/state.h


SOURCES += src/main.cpp \
           src/main_window.cpp \
           src/field.cpp \
           src/graph.cpp \
           src/state.cpp