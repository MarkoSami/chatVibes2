QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcontact.cpp \
    addstory.cpp \
    application/application.cpp \
    customGUI/qclickablegroubox.cpp \
    lib/filesystem_lib.cpp \
    lib/gui_lib.cpp \
    lib/gui_render.cpp \
    lib/utils.cpp \
    logic/contact.cpp \
    logic/conversation.cpp \
    logic/message.cpp \
    logic/story.cpp \
    logic/user.cpp \
    loginform.cpp \
    main.cpp \
    mainwindow.cpp \
    messagelongalert.cpp \
    profilewindow.cpp \
    registerfrom.cpp \
    settings.cpp \
    startnewchat.cpp \
    welcomepage.cpp

HEADERS += \
    addcontact.h \
    addstory.h \
    application/application.h \
    customGUI/qclickablegroubox.h \
    customGUI/qclickablegroubox.h \
    lib/filesystem_lib.h \
    lib/gui_lib.h \
    lib/gui_render.h \
    lib/utils.h \
    logic/contact.h \
    logic/conversation.h \
    logic/message.h \
    logic/story.h \
    logic/user.h \
    loginform.h \
    mainwindow.h \
    messagelongalert.h \
    profilewindow.h \
    registerfrom.h \
    settings.h \
    startnewchat.h \
    welcomepage.h

FORMS += \
    addcontact.ui \
    addstory.ui \
    loginform.ui \
    mainwindow.ui \
    messagelongalert.ui \
    profilewindow.ui \
    registerfrom.ui \
    settings.ui \
    startnewchat.ui \
    welcomepage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    img/discussion_1.png \
    img/find_1.png \
    img/profile.png \
    img/undraw_new_message_re_fp03.svg


RESOURCES +=

DISTFILES += \
    img/discussion_1.png \
    img/find_1.png \
    img/profile.png \
    img/undraw_new_message_re_fp03.svg
