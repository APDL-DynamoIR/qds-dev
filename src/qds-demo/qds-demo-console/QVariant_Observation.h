
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef QVARIANT_OBSERVATION__H
#define QVARIANT_OBSERVATION__H


#include <QString>
#include <QMap>

#include "QCohortEventNexus.h"

#include "QCohortObservation.h"

#include "comparison-monads.h"


class QCohortBasicEvent;
class Student;


class QVariant_Observation : public QCohortObservation
{
 Q_OBJECT

 QMap<QString, QPair<Dimensions_Of_Comparison, QVariant>> data_;

public:

 typedef Comparison<Ordinal> Comparison_Ordinal_Result_Monad_type;

 const QMap<QString, QPair<Dimensions_Of_Comparison, QVariant>>& get_data() const
 {
  return data_;
 }

 QMap<QString, QPair<Dimensions_Of_Comparison, QVariant>>& data()
 {
  return data_;
 }

 QVariant_Observation();
 QVariant_Observation(const QVariant_Observation& rhs);

 Q_INVOKABLE int get_comparison(QString index, const QVariant_Observation& rhs, QString rhs_index) const;
 Q_INVOKABLE int get_comparison(QVariant val, QString index) const;

 void absorb_data(QDataStream& qds);
 void supply_data(QDataStream& qds) const;

};

QDataStream& operator<<(QDataStream&, const QVariant_Observation&);
QDataStream& operator>>(QDataStream&, QVariant_Observation&);

#endif
