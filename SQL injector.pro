QT += core gui
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# Specify the minimum macOS version for the M1 Pro chip
contains(QMAKE_TARGET.arch, arm64) {
    QMAKE_MACOS_DEPLOYMENT_TARGET = 11.0
}

# Specify the minimum macOS version for the Intel chip
contains(QMAKE_TARGET.arch, x86_64) {
    QMAKE_MACOS_DEPLOYMENT_TARGET = 10.14
}

INCLUDEPATH += $$PWD
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
    table.ui \
    wherediag.ui

ICON = icon.icns

QMAKE_MACOS_DEPLOYMENT_TARGET

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../build-SQL-injector-Qt_6_4_2_for_macOS-Release/SQL injector.app \
    ../suspects.txt \
    SQL injector.app \
    icon.icns \
    icon.ico
