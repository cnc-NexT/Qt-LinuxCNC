d#-------------------------------------------------
#
# Project created by QtCreator 2021-06-16T12:11:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_LLX_Symbols
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release):       LIBS   += -L$$PWD/../../../../../../data/plc/release/ -lLLSymbols
else:win32:CONFIG(debug, debug|release):    LIBS   += -L$$PWD/../../../../../../data/plc/debug/ -lLLSymbols
else:unix:                                  LIBS   += -L$$PWD/../../../../../../data/plc/ -lLLSymbols

INCLUDEPATH += $$PWD/../../../../../../data/plc \
               /usr/include/linuxcnc \
               /home/user/linuxcnc/include \
               /home/user/linuxcnc/src/hal/utils \
               /usr/include/linuxcnc \
               /home/udos/linuxcnc-dev/src/hal \
               /home/udos/linuxcnc-dev/src/hal/utils

LIBS += -Iinclude -Isrc/emc/rs274ngc -Llib -lnml -llinuxcnc  -llinuxcnchal -llinuxcncini -DULAPI -lposemath
LIBS += -lGLU -lGL

DEPENDPATH  += $$PWD/../../../../../../data/plc

RESOURCES += \
    stylessheet.qrc

DISTFILES += \
    Bitmap/System/Settings.xml \
    Bitmap/exit_icon.png

