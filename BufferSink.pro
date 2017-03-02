QT += core
QT -= gui

CONFIG += c++11

TARGET = BufferSink
CONFIG += console
CONFIG -= app_bundle
DEFINES += GCC Foundation_EXPORTS POCO_NO_SOO
TEMPLATE = app

SOURCES += main.cpp \
    source/IITPCommands.cpp \
    source/IITPFactory.cpp \
    source/IITPLogger.cpp \
    source/IITPRequestHandler.cpp \
    source/IITPRequestHandlerFactory.cpp \
    source/IITPRequestProcess.cpp \
    source/IITPServer.cpp \
    source/IITPServerConnection.cpp \
    source/IITPServerConnectionFactory.cpp \
    source/IITPServerParams.cpp \
    source/IITPServerSession.cpp


HOMEDIR = $$(INNOVATIVECOMMON)


CONFIG(debug, debug|release) {
    OBJECTS_DIR = Debug
    DESTDIR = Debug
 }
else {
    OBJECTS_DIR = Release
    DESTDIR = Release
}

INCLUDEPATH = ./source \
             $$HOMEDIR/Malibu \
             $$HOMEDIR/Malibu/Poco/Net/include \
             $$HOMEDIR/Malibu/Poco/Foundation/include

LIBS += -L$$HOMEDIR/Lib/Gcc \
    -L$$HOMEDIR/Lib/Gcc/$$DESTDIR \
    -Wl,@$$HOMEDIR/Lib/Gcc/Malibu_Qt.lcf

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    source/IITPCommands.h \
    source/IITPFactory.h \
    source/IITPLogger.h \
    source/IITPRequestHandler.h \
    source/IITPRequestHandlerFactory.h \
    source/IITPRequestProcess.h \
    source/IITPServer.h \
    source/IITPServerConnection.h \
    source/IITPServerConnectionFactory.h \
    source/IITPServerParams.h \
    source/IITPServerSession.h
