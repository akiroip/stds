QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    enemy.cpp \
    main.cpp \
    player.cpp \
    stds.cpp

HEADERS += \
    bullet.h \
    enemy.h \
    player.h \
    stds.h

FORMS += \
    stds.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    stds.qrc

win32: RC_ICONS = stds.ico
win32: VERSION = 0.0.1
win32: QMAKE_TARGET_COMPANY = "Prsa Igor"
win32: QMAKE_TARGET_COPYRIGHT = "Copyright (C) 2020 Prsa Igor <akiro.ip@gmail.com>"
win32: QMAKE_TARGET_PRODUCT = "stds"
win32: QMAKE_TARGET_DESCRIPTION = "Simple 2D Shooter"
