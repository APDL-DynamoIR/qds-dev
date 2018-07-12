

#           Copyright Nathaniel Christen 2018.
#  Distributed under the Boost Software License, Version 1.0.
#     (See accompanying file LICENSE_1_0.txt or copy at
#           http://www.boost.org/LICENSE_1_0.txt)



PROJECT_NAME = qds-demo-console

QT += widgets

include(../build-group.pri)

TEMPLATE = app

INCLUDEPATH += $$SRC_GROUP_DIR


HEADERS += \
  $$SRC_DIR/QCohortBasicEvent.h \
  $$SRC_DIR/QCohortEvent.h \
  $$SRC_DIR/QCohortEventNexus.h \
  $$SRC_DIR/QCohortGround.h \
  $$SRC_DIR/QCohortObservation.h \
  $$SRC_DIR/Test_Result.h \
  $$SRC_DIR/Student.h \
  $$SRC_DIR/Test_Result_Event_Nexus.h \
  $$SRC_DIR/comparison-monads.h \
  $$SRC_DIR/Student_Uniqueness_Ground.h \
  $$SRC_DIR/QCohortUniquenessGround.h \
  $$SRC_DIR/Student_Demographic_Data.h \
  $$SRC_DIR/Student_Demographic_Data_QObject.h \
  $$SRC_DIR/Tutoring.h \
  $$SRC_DIR/Tutoring_Event_Nexus.h \
  $$SRC_DIR/QVariant_Observation.h \
  $$SRC_DIR/QVariant_Event_Nexus.h


SOURCES += \
  $$SRC_DIR/main.cpp \
  $$SRC_DIR/QCohortBasicEvent.cpp \
  $$SRC_DIR/QCohortEvent.cpp \
  $$SRC_DIR/QCohortGround.cpp \
  $$SRC_DIR/QCohortObservation.cpp \
  $$SRC_DIR/Test_Result.cpp \
  $$SRC_DIR/Student.cpp \
  $$SRC_DIR/Test_Result_Event_Nexus.cpp \
  $$SRC_DIR/comparison-monads.cpp \
  $$SRC_DIR/Student_Uniqueness_Ground.cpp \
  $$SRC_DIR/QCohortUniquenessGround.cpp \
  $$SRC_DIR/Student_Demographic_Data.cpp \
  $$SRC_DIR/Student_Demographic_Data_QObject.cpp \
  $$SRC_DIR/Tutoring.cpp \
  $$SRC_DIR/Tutoring_Event_Nexus.cpp \
  $$SRC_DIR/QVariant_Observation.cpp \
  $$SRC_DIR/QVariant_Event_Nexus.cpp



