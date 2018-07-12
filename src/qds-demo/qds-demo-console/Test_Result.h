
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef TEST_RESULT__H
#define TEST_RESULT__H


#include <QString>

#include "QCohortEventNexus.h"

#include "QCohortObservation.h"

#include "comparison-monads.h"


class QCohortBasicEvent;
class Test_Result;
class Student;


class Test_Result : public QCohortObservation
{
 Q_OBJECT

 int reading_;
 int writing_;
 int math_;

 int length_of_unit_;

public:

 typedef Comparison<Ordinal> Comparison_Ordinal_Result_Monad_type;

 Test_Result(int scores [4]);
 Test_Result();
 Test_Result(const Test_Result& rhs);


 Q_INVOKABLE int get_reading() const { return reading_; }
 Q_INVOKABLE int get_writing() const { return writing_; }
 Q_INVOKABLE int get_math() const { return math_; }
 Q_INVOKABLE int get_length_of_unit() const { return length_of_unit_; }


 Q_INVOKABLE int get_ordinal_comparison(const Test_Result& rhs, int index) const;

 Q_INVOKABLE int get_ordinal_comparison(int score, int index) const;

};


#endif
