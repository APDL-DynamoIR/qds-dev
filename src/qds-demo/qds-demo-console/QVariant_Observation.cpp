
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "QVariant_Observation.h"

#include <QDebug>
#include <QDataStream>


void debug_data(const QVariant_Observation& _this)
{
 //qDebug() << "QVariant_Observation data:";
 QMapIterator<QString, QPair<Dimensions_Of_Comparison, QVariant>> tempit(_this.get_data());
 while(tempit.hasNext())
 {
  tempit.next();
  QString k = tempit.key();
  //qDebug() << "\nkey= " << k;

  QPair<Dimensions_Of_Comparison, QVariant> pr = tempit.value();
  Dimensions_Of_Comparison dc = pr.first;
  //qDebug() << "DoC: " << Get_DOC_Name(dc) << "\n";
 }
}

int QVariant_Observation::get_comparison(QString index,
  const QVariant_Observation& rhs, QString rhs_index) const
{
 auto it = data_.constFind(index);

// qDebug() << "Index: " << index;
// qDebug() << "rIndex: " << rhs_index;

 if(it == data_.cend())
 {
  throw Unrecognized_Attribute_Index_Exception({index});
 }
 QVariant qvar = it.value().second;

 auto it1 = rhs.get_data().constFind(rhs_index);
 if(it1 == data_.cend())
 {
  throw Unrecognized_Attribute_Index_Exception({rhs_index});
 }
 if(it1.value().first != it.value().first)
 {
  throw Dimension_Of_Comparison_Mismatch_Exception({Get_DOC_Name(it.value().first), rhs_index, Get_DOC_Name(it1.value().first)});
 }
 QVariant qvar1 = it1.value().second;

 switch (it.value().first)
 {
 case Dimensions_Of_Comparison::Ordinal:
   return compare_raw_qv<Ordinal>({ qvar, qvar1 });
 case Dimensions_Of_Comparison::Nominal:
   return compare_raw_qv<Nominal>({ qvar, qvar1 });
 case Dimensions_Of_Comparison::Temporal:
   return compare_raw_qv<Temporal>({ qvar, qvar1 });
 case Dimensions_Of_Comparison::Uniqueness:
   return compare_raw_qv<Uniqueness>({ qvar, qvar1 });
 case Dimensions_Of_Comparison::Taxonomic:
   return compare_raw_qv<Taxonomic>({ qvar, qvar1 });

 }

}

int QVariant_Observation::get_comparison(QVariant val, QString index) const
{
 auto it = data_.constFind(index);
 if(it == data_.cend())
 {
  throw Unrecognized_Attribute_Index_Exception({index});
 }
 QVariant qvar = it.value().second;

 switch (it.value().first)
 {
 case Dimensions_Of_Comparison::Ordinal:
   return compare_raw_qv<Ordinal>({ qvar, val });
 case Dimensions_Of_Comparison::Nominal:
   return compare_raw_qv<Nominal>({ qvar, val });
 case Dimensions_Of_Comparison::Temporal:
   return compare_raw_qv<Temporal>({ qvar, val });
 case Dimensions_Of_Comparison::Uniqueness:
   return compare_raw_qv<Uniqueness>({ qvar, val });
 case Dimensions_Of_Comparison::Taxonomic:
   return compare_raw_qv<Taxonomic>({ qvar, val });

 }
}


QVariant_Observation::QVariant_Observation()
 : QCohortObservation()
{
}

QVariant_Observation::QVariant_Observation(const QVariant_Observation& rhs)
 : QCohortObservation(rhs), data_(rhs.data_)
{

}

void QVariant_Observation::absorb_data(QDataStream& qds)
{
 qds >> data_;
 debug_data(*this);
}

void QVariant_Observation::supply_data(QDataStream& qds) const
{
 debug_data(*this);
 qds << data_;
}


QDataStream& operator<<(QDataStream& qds, const QVariant_Observation& qvo)
{
 qvo.supply_data(qds);
 return qds;
}


QDataStream& operator>>(QDataStream& qds, QVariant_Observation& qvo)
{
 qvo.absorb_data(qds);
 return qds;
}

