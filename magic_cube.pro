
HEADERS += \
    cube.h

SOURCES += \
    cube.cpp \
    main.cpp

QT   +=core gui

greaterThan(QT_MAJOR_VERSION,4):QT +=widgets

QT   += opengl

LIBS   += -lopengl32
LIBS   += -lglu32
