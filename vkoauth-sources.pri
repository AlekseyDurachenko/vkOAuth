INCLUDEPATH    +=                                                       \
    $$PWD/src                                                           \


HEADERS        +=                                                       \
    $$PWD/src/settings.h                                                \
    $$PWD/src/version.h                                                 \
    $$PWD/src/aboutdialog.h                                             \
    $$PWD/src/mainwindow.h                                              \
    $$PWD/src/resources.h                                               \
    $$PWD/src/theme.h                                                   \
    $$PWD/src/vkauthview.h                                              \


SOURCES        +=                                                       \
    $$PWD/src/version.cpp                                               \
    $$PWD/src/aboutdialog.cpp                                           \
    $$PWD/src/mainwindow.cpp                                            \
    $$PWD/src/resources.cpp                                             \
    $$PWD/src/theme.cpp                                                 \
    $$PWD/src/vkauthview.cpp                                            \


FORMS          +=                                                       \
    $$PWD/src/aboutdialog.ui                                            \
    $$PWD/src/mainwindow.ui                                             \


TRANSLATIONS   +=                                                       \
    $$PWD/ts/vkoauth_ru.ts                                              \


RESOURCES      +=                                                       \
    $$PWD/qrc/icons.qrc                                                 \


OTHER_FILES    +=                                                       \
    $$PWD/ABOUT                                                         \
    $$PWD/AUTHORS                                                       \
    $$PWD/CHANGELOG                                                     \
    $$PWD/LIBRARIES                                                     \
    $$PWD/LICENSE                                                       \
    $$PWD/LICENSE.GPL-3+                                                \
    $$PWD/README.md                                                     \


!contains(QT, testlib) {
    HEADERS   +=                                                        \

    SOURCES   +=                                                        \
        $$PWD/src/main.cpp                                              \

}
