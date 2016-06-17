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
           hdr/state.h \
           hdr/position.h \
           hdr/maze_admin.h \
           hdr/set_dim_dialog.h \
           hdr/search_case.h \
           hdr/maze_group.h \
           hdr/field_settings_group.h \
           hdr/stats_group.h \
           hdr/search_group.h \
           hdr/search_strategy.h \
           hdr/uniform_cost.h


SOURCES += src/main.cpp \
           src/main_window.cpp \
           src/field.cpp \
           src/graph.cpp \
           src/state.cpp \
           src/position.cpp \
           src/maze_admin.cpp \
           src/set_dim_dialog.cpp \
           src/search_case.cpp \
           src/maze_group.cpp \
           src/field_settings_group.cpp \
           src/stats_group.cpp \
           src/search_group.cpp \
           src/uniform_cost.cpp