QT += webengine webenginewidgets

TEMPLATE = app

CONFIG += c++11

RESOURCES += src/qml/layout.qrc

INCLUDEPATH += include/

HEADERS += include/request_interceptor.hpp

SOURCES += src/main.cpp \
           src/request_interceptor.cpp \
           src/handlers/zenoh-handler.cpp \
           src/handlers/common-handler.cpp

LIBS += -lzenohpico

DESTDIR = dist
OBJECTS_DIR = $${DESTDIR}/.obj
RCC_DIR = $${DESTDIR}/.rcc

