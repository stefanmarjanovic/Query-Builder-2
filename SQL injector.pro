QT += core gui
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += app_bundle \

RC_ICONS = icon.ico
ICON = myapp.icns

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    data.cpp \
    main.cpp \
    mainwindow.cpp \
    statements.cpp

HEADERS += \
    data.h \
    mainwindow.h \
    statements.h \
    ui_wherebox.h

FORMS += \
    columnsdiag.ui \
    mainwindow.ui \
    wherediag.ui

ICON = icon.icns

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../suspects.txt \
    icon.icns \
    icon.ico
