QT += widgets
requires(qtConfig(treeview))

TARGET = dirview

SOURCES       = main.cpp \
    filesystemproxymodel.cpp \
    foldersizeworker.cpp \
    mainwidget.cpp \
    sizedelegate.cpp

# install
target.path = /usr/bin
INSTALLS += target

HEADERS += \
    filesystemproxymodel.h \
    foldersizeworker.h \
    mainwidget.h \
    roles.h \
    sizedelegate.h
