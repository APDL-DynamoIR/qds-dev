
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef QCOHORTBASICEVENT__H
#define QCOHORTBASICEVENT__H

#include <QString>

#include "QCohortEvent.h"

#include "comparison-monads.h"


class QCohortBasicEvent : public QCohortEvent
{
public:

 typedef Comparison<Temporal> Comparison_Result_Monad_type;

 QCohortBasicEvent(QString description);

 signed int get_temporal_comparison(const QCohortBasicEvent& e) const;

void absorb_data(QDataStream& qds);
void supply_data(QDataStream& qds) const;

};

QDataStream& operator<<(QDataStream&, const QCohortBasicEvent&);
QDataStream& operator>>(QDataStream&, QCohortBasicEvent&);

#endif
