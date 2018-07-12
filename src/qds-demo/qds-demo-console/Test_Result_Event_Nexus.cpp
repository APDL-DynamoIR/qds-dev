
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QStringList>
#include <QDebug>

#include "Test_Result_Event_Nexus.h"

#include "QVariant_Event_Nexus.h"

Test_Result_Event_Nexus::Test_Result_Event_Nexus(QString description)
{
 QStringList qsl = description.simplified().split(' ');

 QString date = qsl.takeAt(0);
 QString name = qsl.takeAt(0);
 QString scores = qsl.takeAt(0);

 qDebug() << "Date: " << date;
 qDebug() << "Name: " << name;
 qDebug() << "Scores: " << scores;


 event_object_= new QCohortBasicEvent(date);

 int scores_[4];
 int c = 0;
 for(QString s : scores.split(':'))
 {
  scores_[c++] = s.toInt();
 }

 observation_object_ = new Test_Result(scores_);

 ground_object_ = new Student(name);
}

QVariant_Event_Nexus* Test_Result_Event_Nexus::to_qvariant_nexus()
{
 QVariant_Event_Nexus* result = new QVariant_Event_Nexus(event_object_, ground_object_);
 result->data()["Test_Result/reading"] = {Ordinal, observation_object_->get_reading()};
 result->data()["Test_Result/writing"] = {Ordinal, observation_object_->get_writing()};
 result->data()["Test_Result/math"] = {Ordinal, observation_object_->get_math()};
 result->data()["Test_Result/length_of_unit"] = {Ordinal, observation_object_->get_length_of_unit()};

 return result;

}

