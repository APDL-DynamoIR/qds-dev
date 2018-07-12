
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QStringList>
#include <QDebug>

#include "QVariant_Event_Nexus.h"

QVariant_Event_Nexus::QVariant_Event_Nexus(QCohortBasicEvent* e, Student* g)
{
 event_object_ = e;
 ground_object_ = g;
 observation_object_ = new QVariant_Observation();
}

QMap<QString, QPair<Dimensions_Of_Comparison, QVariant>>& QVariant_Event_Nexus::data()
{
 return observation_object_->data();
}

void QVariant_Event_Nexus::absorb_data(QDataStream& qds)
{
 qds >> *event_object_;
 qds >> *ground_object_;
 qds >> *observation_object_;
}

void QVariant_Event_Nexus::supply_data(QDataStream& qds) const
{
 qds << *event_object_;
 qds << *ground_object_;
 qds << *observation_object_;
}


QDataStream& operator<<(QDataStream& qds, const QVariant_Event_Nexus& qven)
{
 qven.supply_data(qds);
 return qds;
}


QDataStream& operator>>(QDataStream& qds, QVariant_Event_Nexus& qven)
{
 qven.absorb_data(qds);
 return qds;
}

