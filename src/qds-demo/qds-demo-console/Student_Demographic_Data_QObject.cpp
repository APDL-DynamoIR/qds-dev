
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "Student_Demographic_Data_QObject.h"

#include <QDebug>
#include <QDataStream>


Student_Demographic_Data_QObject::Student_Demographic_Data_QObject()
 : QObject(nullptr)
{
}

Student_Demographic_Data_QObject::Student_Demographic_Data_QObject(
  const Student_Demographic_Data_QObject& rhs)
 : QObject(nullptr)
{


}

int Student_Demographic_Data_QObject::get_ordinal_comparison(
  const Student_Demographic_Data_QObject& rhs, int index) const
{
 static int first_index = metaObject()->indexOfMethod("get_age()");

 //?qDebug() << "Index: " << index;
 switch(index - first_index)
 {
 case 0: return compare_raw<Ordinal, int>({ get_age(), rhs.get_age() });
 case 1: throw Dimension_Of_Comparison_Mismatch_Exception({"Nominal", "gender", "Ordinal"});
 default: throw Unrecognized_Attribute_Index_Exception(
  {QString("%1/%2").arg(metaObject()->className()).arg(index)});
 }
}

int Student_Demographic_Data_QObject::get_nominal_comparison(
  const Student_Demographic_Data_QObject& rhs, int index) const
{
 static int first_index = metaObject()->indexOfMethod("get_age()");

 //?qDebug() << "Index: " << index;
 switch(index - first_index)
 {
 case 0: throw Dimension_Of_Comparison_Mismatch_Exception({"Ordinal", "age", "Nominal"});
 case 1: return compare_raw<Nominal, int>({ get_gender(), rhs.get_gender() });
 default: throw Unrecognized_Attribute_Index_Exception(
  {QString("%1/%2").arg(metaObject()->className()).arg(index)});
 }
}

void Student_Demographic_Data_QObject::absorb_data(QDataStream& qds)
{
 int age;
 qds >> age;
 set_age(age);
 quint8 c;
 qds >> c;
 set_gender( (char) c );
 QString full_name;
 qds >> full_name;
 set_full_name(full_name);
}

void Student_Demographic_Data_QObject::supply_data(QDataStream& qds) const
{
 qds << (quint8) get_age();
 qds << get_gender();
 qds << get_full_name();
}


