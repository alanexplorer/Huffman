#-------------------------------------------------
#
# Project created by QtCreator 2015-10-27T11:42:04
#
#-------------------------------------------------

QT       += core multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Huffman
TEMPLATE = app


SOURCES += main.cpp\
        gui.cpp \
    huffman.cpp \
    tree.cpp

HEADERS  += gui.h \
    huffman.h \
    tree.h \
    node.h

FORMS    += gui.ui
