
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)



#ifndef QCOHORTEVENT__H
#define QCOHORTEVENT__H


#include <QString>

#include "QCohortEventNexus.h"

#include "QCohortObservation.h"


class QCohortEvent
{
protected:

 int year_;
 int month_;
 int day_;

 int hour_;
 int minute_;


public:

 QCohortEvent();




};


#endif
