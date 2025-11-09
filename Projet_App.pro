QT += core gui widgets
CONFIG += c++17


SOURCES += \
    main.cpp \
    mafenetre.cpp \
    $$files(LIB/*.c)



HEADERS += \
    mafenetre.h \
    $$files(LIB/*.h)


FORMS += \
    mafenetre.ui


INCLUDEPATH += $$PWD/LIB
DEPENDPATH += $$PWD/LIB

LIBS += -L$$PWD/LIB/ -lODALID_Education


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressource.qrc
