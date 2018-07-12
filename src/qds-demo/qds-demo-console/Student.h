
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef STUDENT__H
#define STUDENT__H


#include <QString>


#include "QCohortGround.h"

#include "comparison-monads.h"

class Student_Uniqueness_Ground;
class Student_Demographic_Data_QObject;
class Student_Personal_Information;
class Student_Course_Information;


class Student : public QCohortGround
{
 Q_OBJECT

 Student_Uniqueness_Ground* uniqueness_;
 Student_Demographic_Data_QObject* demographic_;
 Student_Personal_Information* personal_;
 Student_Course_Information* course_;

public:

 typedef Comparison<Uniqueness> Comparison_Uniqueness_Result_Monad_type;
 typedef Comparison<Ordinal> Comparison_Ordinal_Result_Monad_type;
 typedef Comparison<Nominal> Comparison_Nominal_Result_Monad_type;


 const Student_Uniqueness_Ground& uniqueness() const
 {
  return *uniqueness_;
 }

 const Student_Demographic_Data_QObject& demographic() const
 {
  return *demographic_;
 }

 Student_Demographic_Data_QObject& demographic()
 {
  return *demographic_;
 }

 Student(QString full_name_);
 Student();
 Student(const Student& rhs);

 void absorb_data(QDataStream& qds);
 void supply_data(QDataStream& qds) const;

};

QDataStream& operator<<(QDataStream&, const Student&);
QDataStream& operator>>(QDataStream&, Student&);


#endif
