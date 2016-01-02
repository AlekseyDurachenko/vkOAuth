unix {
    docs.files      =                                               \
        $$PWD/ABOUT                                                 \
        $$PWD/AUTHORS                                               \
        $$PWD/CHANGELOG                                             \
        $$PWD/LIBRARIES                                             \
        $$PWD/LICENSE                                               \
        $$PWD/LICENSE.GPL-3+                                        \

    langs.files     =                                               \
        $$PWD/ts/*.qm                                               \

    desktopfiles.files =                                            \
        $$PWD/res/desktopfiles/vkoauth.desktop                      \

    appicons.files =                                                \
        $$PWD/res/icons/hicolor                                     \

    contains(DEFINES, APP_PORTABLE) {
        INSTALLS += target docs langs

        target.path     = /
        docs.path       = /
        langs.path      = /lang
    }

    !contains(DEFINES, APP_PORTABLE) {
        INSTALLS += target docs langs desktopfiles appicons

        target.path         = /usr/bin/
        docs.path           = /usr/share/$${TARGET}
        langs.path          = /usr/share/$${TARGET}/lang
        desktopfiles.path   = /usr/share/applications/
        appicons.path       = /usr/share/icons/

        # you should to determine the location of resources
        DEFINES += "APP_RESOURCES_PREFIX='/usr/share/$${TARGET}'"
    }
}
