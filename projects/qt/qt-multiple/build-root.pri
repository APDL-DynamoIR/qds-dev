

#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)



QT       += core

CONFIG   += console

TEMPLATE = lib



####  These regex matches should identify the pertinent directories and
##    build settings for Qt and qmake, based on the qmake output directory
##    (assuming you're using shadow build).  If not, a workaround would be
##    to set some of these constants by hand (most of these constants
##    are set assuming a common directory structure underneath ROOT_DIR).
##    To see the settings obtained from these substitutions,
##    uncomment the "message" lines below.

ROOT_DIR = $$OUT_PWD
ROOT_DIR ~= s!/cpp/projects.qt/.*!!

BUILD_DIR_CODE = $$OUT_PWD
BUILD_DIR_CODE ~= s!.*/(build|release)-($$PROJECT_NAME)-(.*)-(Debug|Release)!\3


#message($$ROOT_DIR)
#message($$BUILD_DIR_CODE)

TARGET_QT_VERSION = $$QT_VERSION

TARGET_QT_VERSION ~= s/\./-

TARGET_CODE = $$TARGET_QT_VERSION-$$BUILD_DIR_CODE

TARGET_NUM = targets-$${TARGET_CODE}

CPP_ROOT_DIR = $$ROOT_DIR/cpp

PROJECTS_ROOT_DIR = $$ROOT_DIR/projects

QT_PROJECTS_ROOT_DIR = $$PROJECTS_ROOT_DIR/qt

PROJECTS_DIR = $$QT_PROJECTS_ROOT_DIR/qt$$TARGET_CODE

SRC_ROOT_DIR = $$CPP_ROOT_DIR/src

SRC_GLOBAL_DIR = $$CPP_ROOT_DIR/src/global

SRC_GROUP_DIR = $$SRC_ROOT_DIR/$$PROJECT_GROUP

SRC_DIR = $$SRC_GROUP_DIR/$$PROJECT_NAME

TARGET = $$PROJECT_NAME

TARGETS_ROOT_DIR = $$CPP_ROOT_DIR/targets/qt/qt-multiple

TARGETSDIR = $$TARGETS_ROOT_DIR/$$TARGET_NUM


CONFIG(debug, debug|release) {
    OBJECTS_DIR = $$TARGETSDIR/PROJECT_OBJECTS/$$PROJECT_NAME/debug
} else {
    OBJECTS_DIR = $$TARGETSDIR/PROJECT_OBJECTS/$$PROJECT_NAME/release
}

#Debug:OBJECTS_DIR = $$TARGETSDIR/$$PROJECT_NAME/release
#release:OBJECTS_DIR = $$TARGETSDIR/$$PROJECT_NAME/debug
### This only applies to Qt Creator plugins
#CONFIG(debug, debug|release) {
#    DESTDIR = $$TARGETSDIR
#} else {
#    DESTDIR = $$QT_PLUGINS_LIB_DIR
#}


DESTDIR = $$TARGETSDIR

INCLUDEPATH += $$SRC_DIR $$SRC_ROOT_DIR $$SRC_GLOBAL_DIR

#groups




