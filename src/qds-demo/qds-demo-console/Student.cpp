
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <QString>
#include <QStringList>
#include <QDebug>

#include "Student.h"

#include "Student_Uniqueness_Ground.h"

#include "Student_Demographic_Data_QObject.h"



Student::Student(QString full_name)
 : QCohortGround(), uniqueness_(new Student_Uniqueness_Ground),
   demographic_(new Student_Demographic_Data_QObject),
   personal_(nullptr),
   course_(nullptr)
   //, full_name_(full_name)
{
 demographic_->set_full_name(full_name);
 uniqueness_->check_id_from_name(full_name);
}

Student::Student() : QCohortGround(),
  uniqueness_(nullptr),
  demographic_(nullptr),
  personal_(nullptr),
  course_(nullptr)
{


}

Student::Student(const Student& rhs)
 : QCohortGround(rhs),
   uniqueness_(rhs.uniqueness_),
   demographic_(rhs.demographic_),
   personal_(rhs.personal_),
   course_(rhs.course_)
{

}

void Student::absorb_data(QDataStream& qds)
{
 uniqueness_->absorb_data(qds);
 demographic_->absorb_data(qds);
}

void Student::supply_data(QDataStream& qds) const
{
 uniqueness_->supply_data(qds);
 demographic_->supply_data(qds);
}


QDataStream& operator<<(QDataStream& qds, const Student& qven)
{
 qven.supply_data(qds);
 return qds;
}


QDataStream& operator>>(QDataStream& qds, Student& qven)
{
 qven.absorb_data(qds);
 return qds;
}

