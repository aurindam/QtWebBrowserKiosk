TARGET = qtwebbrowserkiosk

CONFIG += c++11
CONFIG -= app_bundle

SOURCES = \
    appengine.cpp \
    main.cpp \
    eventfilter.cpp

HEADERS = \
    appengine.h \
    constant.h \
    eventfilter.h

OTHER_FILES = \
    qml/BrowserWindow.qml \
    qml/Keyboard.qml

QT += qml quick webengine quickcontrols2

RESOURCES += resources.qrc

!cross_compile {
    isEmpty(INSTALL_PREFIX): INSTALL_PREFIX=/usr/local/bin
} else {
    # Path for Qt for Device Creation
    isEmpty(INSTALL_PREFIX): INSTALL_PREFIX=/data/user/qt/qtwebbrowserkiosk-app
}

target.path = $$INSTALL_PREFIX
INSTALLS += target
