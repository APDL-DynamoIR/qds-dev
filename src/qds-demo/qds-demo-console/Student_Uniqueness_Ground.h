
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef STODENT_UNIQUENESS_GROUND__H
#define STODENT_UNIQUENESS_GROUND__H


#include <QString>

#include "QCohortEventNexus.h"

#include "QCohortUniquenessGround.h"

#include "comparison-monads.h"


class QCohortBasicEvent;
class Test_Result;


class Student_Uniqueness_Ground : public QCohortUniquenessGround
{
 Q_OBJECT

 int id_;

 static int check_id(QString name);

public:

 Student_Uniqueness_Ground();
 Student_Uniqueness_Ground(const Student_Uniqueness_Ground& rhs);

 typedef Comparison<Uniqueness> Comparison_Uniquenes_Result_Monad_type;

 Q_INVOKABLE void check_id_from_name(QString name);

 Q_INVOKABLE int get_id() const { return id_; }

 Q_INVOKABLE int get_uniqueness_comparison(const Student_Uniqueness_Ground& rhs, int index) const;

 void absorb_data(QDataStream& qds);
 void supply_data(QDataStream& qds) const;


};


#endif
