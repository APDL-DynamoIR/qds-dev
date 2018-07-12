
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef STUDENT_DEMOGRAPHIC_DATA_QOBJECT__H
#define STUDENT_DEMOGRAPHIC_DATA_QOBJECT__H


#include <QString>

#include "QCohortEventNexus.h"

#include "QCohortObservation.h"

#include "comparison-monads.h"

#include "Student_Demographic_Data.h"

class Student_Demographic_Data_QObject : public QObject
{
 Q_OBJECT

 Student_Demographic_Data data_;

public:

 typedef Comparison<Ordinal> Comparison_Ordinal_Result_Monad_type;
 typedef Comparison<Nominal> Comparison_Nominal_Result_Monad_type;

 Student_Demographic_Data_QObject();
 Student_Demographic_Data_QObject(const Student_Demographic_Data_QObject& rhs);

 Q_INVOKABLE int get_age() const { return data_.age(); }
 Q_INVOKABLE char get_gender() const { return data_.gender(); }
 Q_INVOKABLE QString get_full_name() const { return data_.full_name(); }

 Q_INVOKABLE void set_age(int a) { data_.set_age(a); }
 Q_INVOKABLE void set_gender(char g) { data_.set_gender(g); }
 Q_INVOKABLE void set_full_name(QString n) { data_.set_full_name(n); }

 Q_INVOKABLE int get_ordinal_comparison(const Student_Demographic_Data_QObject& rhs, int index) const;
 Q_INVOKABLE int get_nominal_comparison(const Student_Demographic_Data_QObject& rhs, int index) const;

 void absorb_data(QDataStream& qds);
 void supply_data(QDataStream& qds) const;

};


#endif
