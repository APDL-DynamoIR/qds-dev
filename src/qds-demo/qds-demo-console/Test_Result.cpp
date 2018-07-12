
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "Test_Result.h"

#include <QDebug>

Test_Result::Test_Result(int scores [3])
 : QCohortObservation()
{
 reading_ = scores[0];
 writing_ = scores[1];
 math_ = scores[2];
 length_of_unit_ = scores[3];
}

Test_Result::Test_Result()
 : QCohortObservation(), reading_(0),writing_(0),math_(0),length_of_unit_(0)
{

}

Test_Result::Test_Result(const Test_Result& rhs)
 : QCohortObservation(rhs), reading_(rhs.reading_),writing_(rhs.writing_),
   math_(rhs.math_),length_of_unit_(rhs.length_of_unit_)
{

}

int Test_Result::get_ordinal_comparison(const Test_Result& rhs, int index) const
{
 static int first_index = metaObject()->indexOfMethod("get_reading()");

 //?qDebug() << "Index: " << index;
 switch(index - first_index)
 {
 case 0: return compare_raw<Ordinal, int>({ reading_, rhs.reading_ });
 case 1: return compare_raw<Ordinal, int>({ writing_, rhs.writing_ });
 case 2: return compare_raw<Ordinal, int>({ math_, rhs.math_ });
 case 3: return compare_raw<Ordinal, int>({ length_of_unit_, rhs.length_of_unit_ });
 default: throw Unrecognized_Attribute_Index_Exception(
  {QString("%1/%2").arg(metaObject()->className()).arg(index)});
 }
}


int Test_Result::get_ordinal_comparison(int score, int index) const
{
 static int first_index = metaObject()->indexOfMethod("get_reading()");

 switch(index - first_index)
 {
 case 0: return compare_raw<Ordinal, int>({ reading_, score });
 case 1: return compare_raw<Ordinal, int>({ writing_, score });
 case 2: return compare_raw<Ordinal, int>({ math_, score });
 case 3: return compare_raw<Ordinal, int>({ length_of_unit_, score });
 default: throw Unrecognized_Attribute_Index_Exception(
  {QString("%1/%2").arg(metaObject()->className()).arg(index)});
 }
}

