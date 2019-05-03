TEMPLATE = app
TARGET = customvideowidget
QT += core websockets
QT += multimedia multimediawidgets widgets
QT  += core gui network
QT +=
HEADERS = \
    videoplayer.h \
    videowidget.h \
    videowidgetsurface.h \
    websocketiodevice.h \
    clientsubscription.h \
    nethandlebase.h \
    nethandleplay.h \
    networkhandlemodules.h \
    playcommandmodule.h \
    wificonnecttest.h \
    nethandlesetpercent.h \
    nethandlesetvol.h \
    nethandlesetplayurl.h \
    nethandlerequestvideolist.h \
    nethandlerequestpercent.h

SOURCES = \
    main.cpp \
    videoplayer.cpp \
    videowidget.cpp \
    videowidgetsurface.cpp \
    websocketiodevice.cpp \
    clientsubscription.cpp \
    nethandlebase.cpp \
    nethandleplay.cpp \
    networkhandlemodules.cpp \
    playcommandmodule.cpp \
    wificonnecttest.cpp \
    nethandlesetpercent.cpp \
    nethandlesetvol.cpp \
    nethandlesetplayurl.cpp \
    nethandlerequestvideolist.cpp \
    nethandlerequestpercent.cpp


target.path = $$[QT_INSTALL_EXAMPLES]/multimediawidgets/customvideosurface/customvideowidget
INSTALLS += target
LIBS += -lQt5Mqtt










