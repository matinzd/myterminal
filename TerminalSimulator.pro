TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsqlite3\
        -lboost_system\

SOURCES += \
    src/main.cpp \
    commands/ls.cpp \
    commands/cd.cpp \
    src/bashloop.cpp \
    commands/clear.cpp \
    commands/commands.cpp \
    utils/database.cpp \
    commands/rm.cpp \
    commands/touch.cpp \
    commands/mkdir.cpp

HEADERS += \
    headers/sysinfo.h \
    headers/bashloop.h \
    headers/commands.h \
    utils/database.h
