QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customizecannydetection.cpp \
    imageprocessing.cpp \
    main.cpp \
    mainwindow.cpp \
    sendingdata.cpp \
    serialcommunication.cpp

HEADERS += \
    customizecannydetection.h \
    imageprocessing.h \
    mainwindow.h \
    sendingdata.h \
    serialcommunication.h

FORMS += \
    customizecannydetection.ui \
    mainwindow.ui \
    sendingdata.ui

LIBS += E:\opencv\build\install\x64\vc16\lib\opencv_core452d.lib
LIBS += E:\opencv\build\install\x64\vc16\lib\opencv_calib3d452d.lib
LIBS += E:\opencv\build\install\x64\vc16\lib\opencv_features2d452d.lib
LIBS += E:\opencv\build\install\x64\vc16\lib\opencv_highgui452d.lib
LIBS += E:\opencv\build\install\x64\vc16\lib\opencv_imgproc452d.lib
LIBS += E:\opencv\build\install\x64\vc16\lib\opencv_photo452d.lib
LIBS += E:\opencv\build\install\x64\vc16\lib\opencv_video452d.lib
LIBS += E:\opencv\build\install\x64\vc16\lib\opencv_videoio452d.lib
LIBS += E:\opencv\build\install\x64\vc16\lib\opencv_imgcodecs452d.lib
LIBS += E:\opencv\build\install\x64\vc16\lib\opencv_objdetect452d.lib

INCLUDEPATH += E:\opencv\build\install\include
DEPENDPATH += E:\opencv\build\install\include
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
