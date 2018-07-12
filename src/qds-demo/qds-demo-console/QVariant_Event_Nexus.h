
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef QVARIANT_EVENT_NEXUS__H
#define QVARIANT_EVENT_NEXUS__H


#include <QString>

#include "QCohortEventNexus.h"

#include "QCohortBasicEvent.h"
#include "QVariant_Observation.h"
#include "Student.h"


class QVariant_Event_Nexus : public QCohortEventNexus<QCohortBasicEvent, Student, QVariant_Observation>
{

public:

 QVariant_Event_Nexus(QCohortBasicEvent* e, Student* g);

 const QVariant_Observation& observation() const
 {
  return *observation_object_;
 }

 QMap<QString, QPair<Dimensions_Of_Comparison, QVariant>>& data();

 const Student& student() const
 {
  return *ground_object_;
 }

 void absorb_data(QDataStream& qds);
 void supply_data(QDataStream& qds) const;

};

QDataStream& operator<<(QDataStream&, const QVariant_Event_Nexus&);
QDataStream& operator>>(QDataStream&, QVariant_Event_Nexus&);

#endif
