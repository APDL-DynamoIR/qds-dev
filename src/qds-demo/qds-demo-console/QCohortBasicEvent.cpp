
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "QCohortBasicEvent.h"

#include <QStringList>
#include <QMap>
#include <QDebug>

#include <QDataStream>

QCohortBasicEvent::QCohortBasicEvent(QString description)
{
 QStringList qsl = description.split('-');

 if(qsl.isEmpty()) return;

 QString yr = qsl.takeFirst();
 year_ = yr.toInt();

 if(qsl.isEmpty()) return;

 QString month = qsl.takeFirst();

 static QMap<QString, int> months {{
   {"January", 0},
   {"February", 1},
   {"March", 2},
   {"April", 3},
   {"May", 4},
   {"June", 5},
   {"July", 6},
  }};

 month_ = months.value(month, -1);

 if(qsl.isEmpty()) return;

 QString day = qsl.takeFirst();
 day_ = day.toInt();

}

signed int QCohortBasicEvent::get_temporal_comparison(const QCohortBasicEvent& e) const
{
 if(year_ > e.year_) return 1;
 if(year_ < e.year_) return -1;
 if(month_ > e.month_) return 1;
 if(month_ < e.month_) return -1;
 if(day_ > e.day_) return 1;
 if(day_ < e.day_) return -1;
 return  0;
}

void QCohortBasicEvent::absorb_data(QDataStream& qds)
{
 qds >> year_;
 qds >> month_;
 qds >> day_;
 qds >> hour_;
 qds >> minute_;
}

void QCohortBasicEvent::supply_data(QDataStream& qds) const
{
 qds << year_;
 qds << month_;
 qds << day_;
 qds << hour_;
 qds << minute_;
}


QDataStream& operator<<(QDataStream& qds, const QCohortBasicEvent& e)
{
 e.supply_data(qds);
 return qds;
}


QDataStream& operator>>(QDataStream& qds, QCohortBasicEvent& e)
{
 e.absorb_data(qds);
 return qds;
}
