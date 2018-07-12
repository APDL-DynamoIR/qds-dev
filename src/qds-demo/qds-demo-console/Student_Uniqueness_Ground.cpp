
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "Student_Uniqueness_Ground.h"

#include <QDebug>
#include <QDataStream>

Student_Uniqueness_Ground::Student_Uniqueness_Ground()
{
}


Student_Uniqueness_Ground::Student_Uniqueness_Ground(const Student_Uniqueness_Ground& rhs)
 : id_(rhs.id_)
{

}

void Student_Uniqueness_Ground::check_id_from_name(QString name)
{
 id_ = check_id(name);
}

int Student_Uniqueness_Ground::check_id(QString name)
{
 static QMap<QString, int> ids;
 static int count = 0;
// if(count == 0)
//    ++count;
 auto it = ids.constFind(name);
 if(it == ids.cend())
 {
  ids.insert(name, ++count);
  return count;
 }
 else
 {
  return it.value();
 }
}

int Student_Uniqueness_Ground::get_uniqueness_comparison(const Student_Uniqueness_Ground& rhs, int index) const
{
 static int first_index = metaObject()->indexOfMethod("get_id()");
 switch(index - first_index)
 {
 case 0: return compare_raw<Uniqueness, int>({ id_, rhs.id_ });
 default: throw Unrecognized_Attribute_Index_Exception(
  {QString("%1/%2").arg(metaObject()->className()).arg(index)});
 }
}

void Student_Uniqueness_Ground::absorb_data(QDataStream& qds)
{
 qds >> id_;
}

void Student_Uniqueness_Ground::supply_data(QDataStream& qds) const
{
 qds << id_;
}



