
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include "comparison-monads.h"

#include <QDataStream>
#include <QDebug>


namespace _Comparison_Base {

template<>
void _call(void* pt, std::function<void()> fun)
{
 fun();
}

template<>
void _skip(void*)
{
}
}



quint8 unit_normalize(signed int r)
{
 if(r > 0)
  return 1;

 else if(r < 0)
  return 3;

 return 0;
}

quint8 eqne_normalize(int r)
{
 if(r > 0)
  return 1;

 else return 0;
}

QDataStream& operator<<(QDataStream& qds, Dimensions_Of_Comparison dc)
{
 //qDebug() << "<< DoC: " << Get_DOC_Name(dc);
 qds << (quint8) dc;
 return qds;
}

QDataStream& operator>>(QDataStream& qds, Dimensions_Of_Comparison& dc)
{
 quint8 u8;
 qds >> u8;
 dc = (Dimensions_Of_Comparison) u8;
 //qDebug() << ">> DoC: " << Get_DOC_Name(dc);
 return qds;
}


QString Get_DOC_Name(Dimensions_Of_Comparison dc)
{
 switch(dc)
 {
 case Nominal: return "Nominal";
 case Ordinal: return "Ordinal";
 case Temporal: return "Temporal";
 case Uniqueness: return "Uniqueness";
 case Taxonomic: return "Taxonomic";
 }
}
