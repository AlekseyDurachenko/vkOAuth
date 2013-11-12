# Copyright 2013, Durachenko Aleksey V. <durachenko.aleksey@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# project options
TARGET          = vkoauth
TEMPLATE        = app
VERSION         = 1.0
DESTDIR         = bin

# build options
CONFIG         += release
QT             += core gui webkit
# build direcotries
OBJECTS_DIR     = build/release_obj
MOC_DIR         = build/release_moc
UI_DIR          = build/release_ui
RCC_DIR         = build/release_rcc

# defines
DEFINES        +=                                           \

# 3rd include path
INCLUDEPATH    +=                                           \

# sources
INCLUDEPATH    +=                                           \
    $$PWD/src                                               \

HEADERS        +=                                           \
    $$PWD/src/cmainwindow.h                                 \
    $$PWD/src/qvkauthview.h                                 \

SOURCES        +=                                           \
    $$PWD/src/cmainwindow.cpp                               \
    $$PWD/src/qvkauthview.cpp                               \

FORMS          +=                                           \
    $$PWD/ui/mainwindow.ui                                  \

RESOURCES      +=                                           \

OTHER_FILES    +=                                           \
    $$PWD/AUTHORS                                           \
    $$PWD/CHANGELOG                                         \
    $$PWD/LICENSE                                           \
    $$PWD/README.md                                         \

# if you want to test the project, do: qmake "QT += testlib"
contains(QT, testlib) {
    SOURCES   +=                                            \

    HEADERS   +=                                            \


} else {
    SOURCES   +=                                            \
        $$PWD/src/main.cpp                                  \

}

# debug
build_pass:CONFIG(debug, debug|release) {
    TARGET      = $$join(TARGET,,,d)
    OBJECTS_DIR = $$join(OBJECTS_DIR,,,d)
    MOC_DIR     = $$join(MOC_DIR,,,d)
    UI_DIR      = $$join(UI_DIR,,,d)
    RCC_DIR     = $$join(RCC_DIR,,,d)

    win32 {
    }

    unix {
        LIBS +=
    }
}

# release
build_pass:CONFIG(release, debug|release) {
    win32 {
    }

    unix {
        LIBS +=
    }
}

