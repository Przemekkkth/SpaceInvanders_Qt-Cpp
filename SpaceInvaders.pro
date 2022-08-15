greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


SOURCES += \
    src/game.cpp \
    src/gamescene.cpp \
    src/main.cpp \
    src/projectile.cpp \
    src/spaceship.cpp \
    src/view.cpp

HEADERS += \
    src/game.h \
    src/gamescene.h \
    src/projectile.h \
    src/spaceship.h \
    src/view.h

RESOURCES += \
    resource.qrc
