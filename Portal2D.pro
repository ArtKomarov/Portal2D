TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -Wall -Wextra

SOURCES += \
#    src/*
    src/boundary.cpp \
    src/box.cpp \
    src/finaldoor.cpp \
    src/graphics.cpp \
    src/grelem.cpp \
    src/hero.cpp \
    src/main.cpp \
    src/manager.cpp \
    src/physelem.cpp \
    src/physics.cpp \
    src/portal.cpp

HEADERS += \
#    src/*
#    levels/*
    src/boundary.h \
    src/box.h \
    src/finaldoor.h \
    src/graphics.h \
    src/physics.h \
    src/manager.h \
    src/hero.h \
    src/portal.h \
    src/grelem.h \
    src/physelem.h \
    levels/level1.hpp \
    levels/level2.hpp

#LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audi

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sfml-window sfml-graphics sfml-system sfml-audio
