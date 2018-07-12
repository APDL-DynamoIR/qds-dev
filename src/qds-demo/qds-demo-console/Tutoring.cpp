
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "Tutoring.h"

#include <QDebug>
#include <QDataStream>

Q_DECLARE_METATYPE(Tutoring)

Tutoring_Topic::Tutoring_Topic(QStringList breakdown)
  : main_and_parents_(breakdown)
{

}

void Tutoring_Topic::absorb_data(QDataStream& qds)
{
 qds >> main_and_parents_;

 //qDebug() << ">> Topic: " << main_and_parents_;
}

void Tutoring_Topic::supply_data(QDataStream& qds) const
{
 //qDebug() << "<< Topic: " << main_and_parents_;

 qds << main_and_parents_;
}


QDataStream& operator<<(QDataStream& qds, const Tutoring_Topic& tt)
{
 tt.supply_data(qds);
 return qds;
}


QDataStream& operator>>(QDataStream& qds, Tutoring_Topic& tt)
{
 tt.absorb_data(qds);
 return qds;
}



void Tutoring::init_topics(QMap<QString, Tutoring_Topic>& result)
{
 result.insert("GroupTheory", Tutoring_Topic({"GroupTheory", "Algebra", "Math"}));
 result.insert("Algebra", Tutoring_Topic({"Algebra", "AdvancedMath", "Math"}));
 result.insert("Math", Tutoring_Topic({"Math"}));
}

signed int Tutoring::match_topics(const Tutoring_Topic& t1, const Tutoring_Topic& t2,
  Tutoring* _this, QString mt, Tutoring_Topic const** tt)
{
 static QMap<QString, Tutoring_Topic>* topics = nullptr;
 if(!topics)
 {
  topics = new QMap<QString, Tutoring_Topic>;
  init_topics(*topics);
 }

 if(_this)
 {
  auto it = topics->constFind(mt);
  if(it != topics->constEnd())
  {
   _this->topic_ = it.value();
  }
  return 0;
 }

 if(tt)
 {
  auto it = topics->constFind(mt);
  if(it != topics->constEnd())
  {
   *tt = &it.value();
  }
  return 0;
 }

 if(mt.isEmpty())
 {
  if (t2.main_topic() == t1.main_topic())
    return 0;
 }
 else if (t1.main_topic() == mt)
   return 0;

 auto it = topics->constFind(t1.main_topic());
 if(it != topics->constEnd())
 {
  QString _mt = mt.isEmpty()? t2.main_topic() : mt;
  const Tutoring_Topic& tt = it.value();
  if(tt.parents_contains(_mt))
    return 1;
 }
 return -1;
}


Tutoring::Tutoring(QString subject, QString main_topic, int number_of_weeks)
 : QCohortObservation()
{
 subject_ = subject;
 number_of_weeks_ = number_of_weeks;
 match_topics(topic_, topic_, this, main_topic);
}

Tutoring::Tutoring()
 : QCohortObservation(), subject_(),number_of_weeks_(0)
{

}

Tutoring::Tutoring(const Tutoring& rhs)
 : QCohortObservation(rhs), subject_(rhs.subject_),
   number_of_weeks_(rhs.number_of_weeks_), topic_(rhs.topic_)
{
}

const Tutoring_Topic* const Tutoring::get_topic_by_name(QString mt)
{

 static Tutoring_Topic dummy;
 const Tutoring_Topic* result;
 match_topics(dummy, dummy, nullptr, mt, &result);
 return result;
}


int Tutoring::get_ordinal_comparison(const Tutoring& rhs, int index) const
{
 static int first_index = metaObject()->indexOfMethod("get_number_of_weeks()");

 //?qDebug() << "Index: " << index;
 switch(index - first_index)
 {
 case 0: return compare_raw<Ordinal, int>({ number_of_weeks_, rhs.number_of_weeks_ });
 case 1: throw Dimension_Of_Comparison_Mismatch_Exception({"Nominal", "subject", "Ordinal"});
 case 2: throw Dimension_Of_Comparison_Mismatch_Exception({"Taxonomic", "subject", "Ordinal"});

 default: throw Unrecognized_Attribute_Index_Exception(
  {QString("%1/%2").arg(metaObject()->className()).arg(index)});
 }
}

int Tutoring::get_nominal_comparison(const Tutoring& rhs, int index) const
{
 static int first_index = metaObject()->indexOfMethod("get_number_of_weeks()");

 //?qDebug() << "Index: " << index;
 switch(index - first_index)
 {
 case 0: throw Dimension_Of_Comparison_Mismatch_Exception({"Ordinal", "subject", "Nominal"});
 case 1: return compare_raw<Nominal, QString>({ subject_, rhs.subject_ });;
 case 2: throw Dimension_Of_Comparison_Mismatch_Exception({"Taxonomic", "subject", "Ordinal"});
 default: throw Unrecognized_Attribute_Index_Exception(
  {QString("%1/%2").arg(metaObject()->className()).arg(index)});
 }
}


int Tutoring::get_ordinal_comparison(QVariant qvar, int index) const
{
 static int first_index = metaObject()->indexOfMethod("get_number_of_weeks()");

 //?qDebug() << "Index: " << index;
 switch(index - first_index)
 {
 case 0: return compare_raw<Ordinal, int>({ number_of_weeks_, qvar.value<int>() });
 case 1: throw Dimension_Of_Comparison_Mismatch_Exception({"Nominal", "subject", "Ordinal"});
 case 2: throw Dimension_Of_Comparison_Mismatch_Exception({"Taxonomic", "subject", "Ordinal"});
 default: throw Unrecognized_Attribute_Index_Exception(
  {QString("%1/%2").arg(metaObject()->className()).arg(index)});
 }
}

int Tutoring::get_nominal_comparison(QVariant qvar, int index) const
{
 static int first_index = metaObject()->indexOfMethod("get_number_of_weeks()");

 switch(index - first_index)
 {
 case 0: throw Dimension_Of_Comparison_Mismatch_Exception({"Ordinal", "subject", "Nominal"});
 case 1: return compare_raw<Nominal, QString>({ subject_, qvar.value<QString>() });
 case 2: throw Dimension_Of_Comparison_Mismatch_Exception({"Taxonomic", "subject", "Nominal"});
 default: throw Unrecognized_Attribute_Index_Exception(
  {QString("%1/%2").arg(metaObject()->className()).arg(index)});
 }
}

int Tutoring::get_taxonomic_comparison(QVariant qvar, int index) const
{
 static int first_index = metaObject()->indexOfMethod("get_number_of_weeks()");

 switch(index - first_index)
 {
 case 0: throw Dimension_Of_Comparison_Mismatch_Exception({"Taxonomic", "number_of_weeks", "Ordinal"});
 case 1: throw Dimension_Of_Comparison_Mismatch_Exception({"Taxonomic", "subject", "Nominal"});
 case 2: return match_topics( topic_, qvar.value<Tutoring_Topic>() );
 default: throw Unrecognized_Attribute_Index_Exception(
  {QString("%1/%2").arg(metaObject()->className()).arg(index)});
 }
}

int Tutoring::get_taxonomic_comparison(QVariant qvar1, QVariant qvar2, int index)
{
 //int type = Tutoring::
 static int first_index = QMetaType::metaObjectForType
   (qMetaTypeId<Tutoring*>())->indexOfMethod("get_number_of_weeks()");

 switch(index - first_index)
 {
 case 0: throw Dimension_Of_Comparison_Mismatch_Exception({"Taxonomic", "number_of_weeks", "Ordinal"});
 case 1: throw Dimension_Of_Comparison_Mismatch_Exception({"Taxonomic", "subject", "Nominal"});
 case 2: return match_topics( qvar1.value<Tutoring_Topic>(), qvar1.value<Tutoring_Topic>(), nullptr, qvar2.value<QString>() );
 default: throw Unrecognized_Attribute_Index_Exception(
  {QString("%1/%2").arg(QMetaType::metaObjectForType
   (qMetaTypeId<Tutoring*>())->className()).arg(index)});
 }
}

