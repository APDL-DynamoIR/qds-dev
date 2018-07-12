
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef STUDENT_DEMOGRAPHIC_DATA__H
#define STUDENT_DEMOGRAPHIC_DATA__H

#include <QString>

class Student_Demographic_Data
{
 int age_;
 char gender_;

 QString full_name_;

public:

 Student_Demographic_Data();

 int age() const { return age_; }
 char gender() const { return gender_; }
 QString full_name() const { return full_name_; }

 void set_age(int a) { age_ = a; }
 void set_gender(char g) { gender_  = g; }
 void set_full_name(QString n) { full_name_ = n; }

};


#endif
