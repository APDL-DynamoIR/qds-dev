
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <QString>

#include "Test_Result_Event_Nexus.h"
#include "Tutoring_Event_Nexus.h"

#include "comparison-monads.h"

#include "Student_Uniqueness_Ground.h"
#include "Student_Demographic_Data_QObject.h"

#include "QVariant_Event_Nexus.h"

#include <QMetaType>
#include <QDebug>
#include <QMetaObject>
#include <QDataStream>

Q_DECLARE_METATYPE(Test_Result*)
Q_DECLARE_METATYPE(Tutoring*)
Q_DECLARE_METATYPE(Student*)
Q_DECLARE_METATYPE(Student_Uniqueness_Ground*)
Q_DECLARE_METATYPE(Student_Demographic_Data_QObject*)

Q_DECLARE_METATYPE(Test_Result)
Q_DECLARE_METATYPE(Tutoring)
Q_DECLARE_METATYPE(Student)
Q_DECLARE_METATYPE(Student_Uniqueness_Ground)
Q_DECLARE_METATYPE(Student_Demographic_Data_QObject)

signed int global_compare_as_refinement_of(QVariant qvar1, QVariant qvar2)
{
 if(qvar1.canConvert<Tutoring_Topic>())
 {
  if(qvar2.canConvert<Tutoring_Topic>())
  {
   return qvar1.value<Tutoring_Topic>().compare_as_refinement_of(qvar2.value<Tutoring_Topic>());
  }
 }
 return -1;
}

const QMetaObject* get_metaobject_by_type_name(QString name)
{
 name.append('*');
 int id = QMetaType::type(name.toLatin1());
 return QMetaType::metaObjectForType(id);
}

int get_attribute_code(QString attr)
{
 int index = attr.indexOf('/');
 if(index == -1)
   return -1;
 QString tn = attr.left(index);

 const QMetaObject* qmo = get_metaobject_by_type_name(tn);

 if(qmo)
 {
  QString mn = attr.mid(index + 1);
  mn.append("()");
  mn.prepend("get_");
  return qmo->indexOfMethod(mn.toLatin1());
 }
 return -1;
}


void check_tutoring(const Tutoring_Event_Nexus& tnexus,
  const Test_Result_Event_Nexus& nexus, int threshold,
  QString subject, QString topic, int number_of_weeks)
{
 qDebug() << QString("Checking whether student %1 scored at "
                     "most %2 on %4 and then received at least "
                     "%3 weeks of %4 tutoring ...")
                           .arg(tnexus.student().demographic().get_full_name())
                           .arg(threshold).arg(number_of_weeks).arg(subject);

 tnexus.observation_ordinal_comparison(number_of_weeks, []
   (const Tutoring& t1, QVariant var)
 {
  static int index = get_attribute_code("Tutoring/number_of_weeks");
  return Comparison<Ordinal>( t1.get_ordinal_comparison(var, index) );
 }).ge_and<Nominal>([tnexus, &subject] ()
 {
  static int index = get_attribute_code("Tutoring/subject");
  return Comparison<Nominal>( tnexus.tutoring().get_nominal_comparison(subject, index) );
 }).eq_and<Taxonomic>([tnexus, &topic]()
 {
  static int index = get_attribute_code("Tutoring/topic");
  const Tutoring_Topic* const tt = Tutoring::get_topic_by_name(topic);
  if(tt)
  {
   return Comparison<Taxonomic>( tnexus.tutoring().get_taxonomic_comparison(
     QVariant::fromValue<Tutoring_Topic>(*tt), index) );
  }
  return Comparison<Taxonomic>::no_comparison();
 }).below_and<Taxonomic>([tnexus, &topic, &subject]()
 {
  static int index = get_attribute_code("Tutoring/topic");
  return Comparison<Taxonomic>( Tutoring::get_taxonomic_comparison(
    QVariant::fromValue<Tutoring_Topic>(*Tutoring::get_topic_by_name(topic)),
    QVariant::fromValue<QString>(subject)
    , index));
 }).below_and<Ordinal>([nexus, threshold, subject]()
 {
  static int index = get_attribute_code(QString("Test_Result/%1").arg(subject.toLower()));
  return Comparison<Ordinal>( nexus.test_result().get_ordinal_comparison(threshold, index) );
 }).le_do([tnexus, &subject, &topic, number_of_weeks]()
 {
  qDebug() << QString("Student %1 received %2 weeks of %3 tutoring, "
                      "which is considered part of %4, "
                      "main topic: %5")
              .arg(tnexus.student().demographic().get_full_name())
              .arg(tnexus.tutoring().get_number_of_weeks())
              .arg(topic).arg(subject).arg(tnexus.tutoring().get_topic().main_topic());
 });

}

int main(int argc, char *argv[])
{
 qRegisterMetaType<Test_Result>();
 qRegisterMetaType<Test_Result*>();
 qRegisterMetaType<Student>();
 qRegisterMetaType<Student*>();
 qRegisterMetaType<Student_Uniqueness_Ground>();
 qRegisterMetaType<Student_Uniqueness_Ground*>();
 qRegisterMetaType<Student_Demographic_Data_QObject>();
 qRegisterMetaType<Student_Demographic_Data_QObject*>();
 qRegisterMetaType<Tutoring>();
 qRegisterMetaType<Tutoring*>();
 qRegisterMetaType<Tutoring_Topic>();
 qRegisterMetaType<Tutoring_Topic*>();

 qRegisterMetaTypeStreamOperators<Tutoring_Topic>("Tutoring_Topic");

 Test_Result_Event_Nexus nexus("2018-May-1 John_Doe 75:90:80:6");

 Test_Result_Event_Nexus nexus1("2018-May-5 John_Doze 70:90:88:3");

 nexus.event_comparison(nexus1, []
  (const QCohortBasicEvent& e1, const QCohortBasicEvent& e2)
 {
  return Comparison<Temporal>( e1.get_temporal_comparison(e2) );
 }).before_and<Ordinal>([nexus, nexus1]()
 {
  return nexus.observation_ordinal_comparison(nexus1, []
   (const Test_Result& t1, const Test_Result& t2)
  {
   static int index = get_attribute_code("Test_Result/math");
   return Comparison<Ordinal>( t1.get_ordinal_comparison(t2, index) );
  });
 }).lt_do([nexus, nexus1]()
 {
  qDebug() << "Score " << nexus1.test_result().get_math()
           << " improves on " << nexus.test_result().get_math();
 });


 try
 {
  nexus.ground_uniqueness_comparison(nexus1, []
   (const Student& s1, const Student& s2)
  {
   static int index = get_attribute_code("Student_Uniqueness_Ground/id");
   return Comparison<Uniqueness>( s1.uniqueness().get_uniqueness_comparison(s2.uniqueness(), index) );
  }).same_do([]()
  {
   qDebug() << "Yes, the student ids are the same.";
  }, // or else
  []()
  {
   qDebug() << "The student ids are different.";
  });

  Student& s = const_cast<Student&>(nexus.student());
  Student& s1 = const_cast<Student&>(nexus1.student());

  // just for show to populate the fields...
  s.demographic().set_age(16);
  s.demographic().set_gender('M');

  s1.demographic().set_age(16);
  s1.demographic().set_gender('F');

  nexus.ground_ordinal_comparison(nexus1, []
   (const Student& s1, const Student& s2)
  {
   static int index = get_attribute_code("Student_Demographic_Data_QObject/age");
   return Comparison<Ordinal>( s1.demographic().get_ordinal_comparison(s2.demographic(), index) );
  }).eq_and<Nominal>([nexus, nexus1]()
  {
   return nexus.ground_nominal_comparison(nexus1, []
    (const Student& s1, const Student& s2)
   {
    static int index = get_attribute_code("Student_Demographic_Data_QObject/gender");
    return Comparison<Nominal>( s1.demographic().get_nominal_comparison(s2.demographic(), index) );
   });
  }).ne_and<Ordinal>([nexus, nexus1]()
  {
   return nexus.observation_ordinal_comparison(nexus1, []
    (const Test_Result& t1, const Test_Result& t2)
   {
    static int index = get_attribute_code("Test_Result/math");
    return Comparison<Ordinal>( t1.get_ordinal_comparison(t2, index) );
   });
  }).lt_do([nexus, nexus1]()
  {
   qDebug() << "The female student outscored the male student: "
            << nexus1.test_result().get_math()
            << " vs. " << nexus.test_result().get_math();
  });
 }
 catch(Unrecognized_Attribute_Index_Exception uaie)
 {
  qDebug() << "Unrecognized_Attribute_Index: " << uaie.index;
 }
 catch(Dimension_Of_Comparison_Mismatch_Exception dcme)
 {
  qDebug() << QString("Dimension_Of_Comparison_Mismatch: "
                      "You requested %1, but field \"%2\" "
                      "calls for comparison %3.").arg(dcme.requested)
              .arg(dcme.field).arg(dcme.actual);
 }



 Tutoring_Event_Nexus tnexus("2018-May-1 John_Doe Math:GroupTheory 8");
 check_tutoring(tnexus, nexus, 80, "Math", "Algebra", 6);


 QVariant_Event_Nexus* vnexus = nexus.to_qvariant_nexus();
 QVariant_Event_Nexus* tvnexus = tnexus.to_qvariant_nexus();

 QVariant_Event_Nexus tvnexus1(new QCohortBasicEvent(QString()),
                               new Student(QString()));

 QByteArray qba;
 QDataStream qds(&qba, QIODevice::WriteOnly);
 qds << *tvnexus;

 QDataStream qds1(qba);
 qds1 >> tvnexus1;

 tvnexus1.observation_ordinal_comparison(*vnexus, []
   (const QVariant_Observation& o1, const QVariant_Observation& o2)
 {
  return Comparison<Ordinal>( o1.get_comparison("Tutoring/number_of_weeks",
    o2, "Test_Result/length_of_unit") );
 }).gt_do([]()
 {
  qDebug() << "The tutoring laster longer than the unit tested.";
 });

 return 0;

}


