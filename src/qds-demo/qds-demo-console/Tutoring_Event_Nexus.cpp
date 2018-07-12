
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QStringList>
#include <QDebug>

#include "Tutoring_Event_Nexus.h"

#include "QVariant_Event_Nexus.h"

Tutoring_Event_Nexus::Tutoring_Event_Nexus(QString description)
{
 QStringList qsl = description.simplified().split(' ');

 QString date = qsl.takeAt(0);
 QString name = qsl.takeAt(0);
 QString subject = qsl.takeAt(0);
 QString length = qsl.takeAt(0);

 qDebug() << "Date: " << date;
 qDebug() << "Name: " << name;
 qDebug() << "Subject: " << subject;
 qDebug() << "Length: " << length;

 event_object_= new QCohortBasicEvent(date);

 int index = subject.indexOf(':');
 if(index == -1)
 {
  observation_object_ = new Tutoring();
 }
 else
 {
  observation_object_ = new Tutoring(subject.left(index),
    subject.mid(index + 1), length.toInt());
 }

 ground_object_ = new Student(name);
}

QVariant_Event_Nexus* Tutoring_Event_Nexus::to_qvariant_nexus()
{
 QVariant_Event_Nexus* result = new QVariant_Event_Nexus(event_object_, ground_object_);
 result->data()["Tutoring/number_of_weeks"] = {Ordinal, observation_object_->get_number_of_weeks()};
 result->data()["Tutoring/subject"] = {Nominal, observation_object_->get_subject()};
 result->data()["Tutoring/topic"] = {Taxonomic, QVariant::fromValue<Tutoring_Topic>(observation_object_->get_topic())};

 return result;

}


