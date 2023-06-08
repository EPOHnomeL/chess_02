QT       += core gui \
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    api.cpp \
    checkmanager.cpp \
    chessboard.cpp \
    chessgame.cpp \
    client.cpp \
    lobby.cpp \
    main.cpp \
    mainmenu.cpp \
    mainwindow.cpp \
    mygraphicsscene.cpp \
    networking.cpp \
    piece.cpp \
    rulemanager.cpp \
    server.cpp

HEADERS += \
    api.h \
    checkmanager.h \
    chessboard.h \
    chessgame.h \
    client.h \
    lobby.h \
    mainmenu.h \
    mainwindow.h \
    mygraphicsscene.h \
    networking.h \
    piece.h \
    rulemanager.h \
    server.h \
    types.h

FORMS += \
    lobby.ui \
    mainmenu.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
