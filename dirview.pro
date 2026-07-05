QT += widgets
requires(qtConfig(treeview))

SOURCES       = main.cpp \
    filesystemproxymodel.cpp \
    mainwidget.cpp \
    sizedelegate.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/dirview
INSTALLS += target

HEADERS += \
    filesystemproxymodel.h \
    mainwidget.h \
    roles.h \
    sizedelegate.h
