
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef TUTORING__H
#define TUTORING__H


#include <QString>

#include "QCohortEventNexus.h"

#include "QCohortObservation.h"

#include "comparison-monads.h"


class QCohortBasicEvent;
class Test_Result;
class Student;


class Tutoring_Topic
{
 QStringList main_and_parents_;

public:

 Tutoring_Topic(QStringList breakdown = QStringList());

 QString main_topic() const
 {
  return main_and_parents_.first();
 }

 bool parents_contains(QString s) const
 {
  return main_and_parents_.contains(s);
 }

 signed int compare_as_refinement_of(const Tutoring_Topic& rhs) const
 {
  if(length() == 0) return -1;
  if(rhs.length() == 0) return -1;
  if(main_topic() == rhs.main_topic()) return 0;
  return parents_contains(rhs.main_topic())? 1:-1;
 }

 int length() const
 {
  return main_and_parents_.length();
 }

 void absorb_data(QDataStream& qds);
 void supply_data(QDataStream& qds) const;

};

QDataStream& operator<<(QDataStream&, const Tutoring_Topic&);
QDataStream& operator>>(QDataStream&, Tutoring_Topic&);

Q_DECLARE_METATYPE(Tutoring_Topic)
Q_DECLARE_METATYPE(Tutoring_Topic*)




class Tutoring : public QCohortObservation
{
 Q_OBJECT

 int number_of_weeks_;
 QString subject_;

 Tutoring_Topic topic_;

 static void init_topics(QMap<QString, Tutoring_Topic>& result);

 static signed int match_topics(const Tutoring_Topic& t1, const Tutoring_Topic& t2,
   Tutoring* _this = nullptr, QString mt = QString(), Tutoring_Topic const** tt = nullptr);


public:

 typedef Comparison<Ordinal> Comparison_Ordinal_Result_Monad_type;
 typedef Comparison<Nominal> Comparison_Nominal_Result_Monad_type;

 Tutoring(QString subject, QString main_topic, int number_of_weeks);
 Tutoring();
 Tutoring(const Tutoring& rhs);

 static const Tutoring_Topic* const get_topic_by_name(QString mt);

 Q_INVOKABLE int get_number_of_weeks() const { return number_of_weeks_; }
 Q_INVOKABLE QString get_subject() const { return subject_; }
 Q_INVOKABLE const Tutoring_Topic& get_topic() const { return topic_; }


 Q_INVOKABLE int get_ordinal_comparison(const Tutoring& rhs, int index) const;
 Q_INVOKABLE int get_nominal_comparison(const Tutoring& rhs, int index) const;

 Q_INVOKABLE int get_ordinal_comparison(QVariant qvar, int index) const;
 Q_INVOKABLE int get_nominal_comparison(QVariant qvar, int index) const;

 Q_INVOKABLE int get_taxonomic_comparison(QVariant qvar, int index) const;
 Q_INVOKABLE static int get_taxonomic_comparison(QVariant qvar1, QVariant qvar2, int index);

};


#endif
