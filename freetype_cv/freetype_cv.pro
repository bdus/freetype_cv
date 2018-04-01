#-------------------------------------------------
#
# Project created by QtCreator 2018-04-01T14:24:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = freetype_cv
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    putchtext.cpp \
    cvxtext.cpp

HEADERS += \
        mainwindow.h \
    putchtext.h \
    cvxtext.h

FORMS += \
        mainwindow.ui



INCLUDEPATH += D:\opencv\opencv-3.2.0\build\include \
   D:\freetype-2.9\include

CONFIG(debug,debug|release):{
    LIBS += D:\opencv\opencv-3.2.0\build\x64\vc14\lib\opencv_world320d.lib \
            D:\freetype-2.9\objs\x64\Debug\freetype.lib

}else:{
    LIBS += D:\opencv\opencv-3.2.0\build\x64\vc14\lib\opencv_world320.lib \
            D:\freetype-2.9\objs\x64\Release\freetype.lib
}
