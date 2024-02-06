QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dialmeter.cpp \
    clockmeter.cpp \
    dialview.cpp \
    main.cpp \
    ecuview.cpp

HEADERS += \
    dialmeter.h \
    clockmeter.h \
    dialview.h \
    ecuview.h

FORMS += \
    ecuview.ui

CONFIG += qwt

unix: INCLUDEPATH += /usr/include/qwt/
unix: LIBS += -L/usr/lib/ -lqwt

win32: INCLUDEPATH += C:\Qwt-6.2.0\include
win32: LIBS += C:/Qwt-6.2.0/lib/qwt.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
