QT       += core gui\
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    cardanimationwidget.cpp

HEADERS += \
    apimethods.h \
    cardanimationwidget.h

FORMS += \
    cardanimationwidget.ui

LIBS += -L/usr/local/lib -lssl -lcrypto
LIBS += -L/usr/local/Cellar/openssl@3/3.1.1_1/lib -lssl -lcrypto
LIBS += -L/usr/local/Cellar/openssl@1.1/1.1.1u/lib -lssl -lcrypto

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/local/Cellar/openssl@3/3.1.1_1/include
INCLUDEPATH += /usr/local/Cellar/openssl@1.1/1.1.1u/include
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
