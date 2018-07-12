
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef COMPARISON_MONADS__H
#define COMPARISON_MONADS__H


#include <QString>
#include <QPair>
#include <functional>


#include "QCohortEventNexus.h"

#include "QCohortObservation.h"

#include <QtGlobal>

#include <QDate>
#include <QDateTime>

extern signed int global_compare_as_refinement_of(QVariant qvar1, QVariant qvar2);


struct Unrecognized_Attribute_Index_Exception
{
 QString index;
};

struct Dimension_Of_Comparison_Mismatch_Exception
{
 QString requested;
 QString field;
 QString actual;
};


quint8 unit_normalize(signed int r);
quint8 eqne_normalize(int r);

enum Dimensions_Of_Comparison
{
 Nominal, Ordinal, Temporal, Uniqueness, Taxonomic
};

QDataStream& operator<<(QDataStream& qds, Dimensions_Of_Comparison dc);
QDataStream& operator>>(QDataStream& qds, Dimensions_Of_Comparison& dc);

QString Get_DOC_Name(Dimensions_Of_Comparison  dc);

template<Dimensions_Of_Comparison dc>
struct Comparison;

namespace _Comparison_Base {

template<typename T>
void _call(T* pt, std::function<T()> fun)
{
 if(pt)
   *pt = fun();
 else
   fun();
}


template<typename T>
void _skip(T* pt)
{
 *pt = T::no_comparison();
}


template<>
void _call(void* pt, std::function<void()> fun);

template<>
void _skip(void*);

}

//?template<Dimensions_Of_Comparison dc>
struct Comparison_Base
{
protected:
 quint8 result_;

 Comparison_Base(quint8 r) : result_(r){}
 Comparison_Base(){}

 template<typename T>
 void _and_(int r, std::function<T()> fun, T* pt = nullptr, int* r1 = nullptr)
 {
  if(result_ == r)
  {
   _Comparison_Base::_call(pt, fun);
   return;
  }
  else if(r1)
  {
   if(result_ == *r1)
   {
    _Comparison_Base::_call(pt, fun);
    return;
   }
  }
  else if(pt)
  {
   _Comparison_Base::_skip(pt);
  }
 }

 template<typename T>
 T _and(int r, int r1, std::function<T()> fun)
 {
  T result;
  _and_(r, fun, &result, &r1);
  return result;
 }

 template<typename T>
 T _and(int r, std::function<T()> fun)
 {
  T result;
  _and_(r, fun, &result);
  return result;
 }

 template<typename T>
 void _do(int r, std::function<T()> fun)
 {
  _and_(r, fun);
 }

 template<typename T>
 void _do(int r, int r1, std::function<T()> fun)
 {
  _and_(r, fun, (T*) nullptr, &r1);
 }

};


template<>
class Comparison<Dimensions_Of_Comparison::Uniqueness> : Comparison_Base
{
 Comparison() : Comparison_Base()
 {

 }

public:

 Comparison(int r)
  : Comparison_Base(r)
 {

 }

 static Comparison no_comparison()
 {
  Comparison result;
  result.result_ = 2;
  return result;
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> same_and(std::function<Comparison<dc>()> fun)
 {
  return _and(0, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> not_same_and(std::function<Comparison<dc>()> fun)
 {
  return _and(1, fun);
 }

 void same_do(std::function<void()> fun)
 {
  _do(0, fun);
 }

 void same_do(std::function<void()> fn1, std::function<void()> fn2)
 {
  _do(0, fn1);
  _do(1, fn2);
 }


 void not_same_do(std::function<void()> fun)
 {
  _do(1, fun);
 }



};


template<>
class Comparison<Dimensions_Of_Comparison::Nominal> : Comparison_Base
{
 friend struct Comparison_Base;
 Comparison() : Comparison_Base()
 {

 }

public:

 Comparison(int r)
  : Comparison_Base(r)
 {

 }

 static Comparison no_comparison()
 {
  Comparison result;
  result.result_ = 2;
  return result;
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> eq_and(std::function<Comparison<dc>()> fun)
 {
  return _and(0, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> ne_and(std::function<Comparison<dc>()> fun)
 {
  return _and(1, fun);
 }

 void eq_do(std::function<void()> fun)
 {
  _do(0, fun);
 }

 void ne_do(std::function<void()> fn1, std::function<void()> fn2)
 {
  _do(0, fn1);
  _do(1, fn2);
 }


 void ne_do(std::function<void()> fun)
 {
  _do(1, fun);
 }



};


template<>
class Comparison<Dimensions_Of_Comparison::Temporal> : Comparison_Base
{
 Comparison() : Comparison_Base()
 {

 }

public:

 Comparison(signed int r)
  : Comparison_Base(r)
 {

 }

 static Comparison no_comparison()
 {
  Comparison result;
  result.result_ = 2;
  return result;
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> after_and(std::function<Comparison<dc>()> fun)
 {
  return _and(1, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> not_before_and(std::function<Comparison<dc>()> fun)
 {
  return _and(1, 0, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> same_time_and(std::function<Comparison<dc>()> fun)
 {
  return _and(0, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> different_time_and(std::function<Comparison<dc>()> fun)
 {
  return _and(1, 3, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> not_after_and(std::function<Comparison<dc>()> fun)
 {
  return _and(0, 3, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> before_and(std::function<Comparison<dc>()> fun)
 {
  return _and(3, fun);
 }
};


template<Dimensions_Of_Comparison dc>
struct _raw_comparisons;

template<>
struct _raw_comparisons<Nominal>
{
 template<typename T>
 static signed int compare_raw(std::initializer_list<T> pr)
 {
  return *pr.begin() == *(pr.begin() + 1)? 0:1;
 }

 static int compare_raw_qv(std::initializer_list<QVariant> pr)
 {
  return *pr.begin() == *(pr.begin() + 1) ? 0:1;
 }


 template<typename T>
 static signed int compare_raw(QPair<T, T> pr)
 {
  return pr.first == pr.second? 0:1;
 }
};


template<>
struct _raw_comparisons<Ordinal>
{
 template<typename T>
 static signed int compare_raw(std::initializer_list<T> pr)
 {
  return *pr.begin() - *(pr.begin() + 1);
 }

 static int compare_raw_qv(std::initializer_list<QVariant> pr)
 {
  return *pr.begin() == *(pr.begin() + 1) ? 0:
         *pr.begin() < *(pr.begin() + 1) ? -1:1;
 }


 template<typename T>
 static signed int compare_raw(QPair<T, T> pr)
 {
  return pr.first - pr.second;
 }
};



template<>
struct _raw_comparisons<Temporal>
{
 static int compare_raw_qv(std::initializer_list<QVariant> pr)
 {
  QVariant v1 = (*pr.begin());
  QVariant v2 = (*(pr.begin() + 1));

  if(v1.canConvert<QDate>())
  {
   if(v2.canConvert<QDate>())
   {
    return v1.toDate() == v2.toDate()? 0:
      v1.toDate() < v2.toDate()? -1:1;
   }
  }

  if(v1.canConvert<QDateTime>())
  {
   if(v2.canConvert<QDateTime>())
   {
    return v1.toDate() == v2.toDate()? 0:
      v1.toDate() < v2.toDate()? -1:1;
   }
  }
  return 2;
 }
};



template<>
struct _raw_comparisons<Taxonomic>
{
 template<typename T>
 static signed int compare_raw(std::initializer_list<T> pr)
 {
  return (*pr.begin()).compare_as_refinement_of(*(pr.begin() + 1));
 }

 static int compare_raw_qv(std::initializer_list<QVariant> pr)
 {
  return global_compare_as_refinement_of(*pr.begin(), *(pr.begin() + 1));;
 }

 template<typename T>
 static signed int compare_raw(QPair<T, T> pr)
 {
  return pr.first.compare_as_refinement_of(pr.second);
 }
};


template<>
struct _raw_comparisons<Uniqueness>
{
 template<typename T>
 static int compare_raw(std::initializer_list<T> pr)
 {
  return *pr.begin() == *(pr.begin() + 1) ? 0:1;
 }

 static int compare_raw_qv(std::initializer_list<QVariant> pr)
 {
  return *pr.begin() == *(pr.begin() + 1) ? 0:1;
 }

 template<typename T>
 static bool compare_raw(QPair<T, T> pr)
 {
  return pr.first == pr.second ? 0:1;
 }
};




template<Dimensions_Of_Comparison dc, typename T>
signed int compare_raw(std::initializer_list<T> pr)
{
 return _raw_comparisons<dc>::compare_raw(pr);
}

template<Dimensions_Of_Comparison dc>
signed int compare_raw_qv(std::initializer_list<QVariant> pr)
{
 return _raw_comparisons<dc>::compare_raw_qv(pr);
}


template<Dimensions_Of_Comparison dc, typename T>
signed int compare_raw(QPair<T, T> pr)
{
 return _raw_comparisons<dc>::compare_raw(pr);
}

template<>
class Comparison<Dimensions_Of_Comparison::Ordinal> : Comparison_Base
{
 friend struct Comparison_Base;
 Comparison() : Comparison_Base()
 {

 }

public:

 Comparison(signed int r)
  : Comparison_Base(unit_normalize(r))
 {

 }

 static Comparison no_comparison()
 {
  Comparison result;
  result.result_ = 2;
  return result;
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> gt_and(std::function<Comparison<dc>()> fun)
 {
  return _and(1, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> ge_and(std::function<Comparison<dc>()> fun)
 {
  return _and(1, 0, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> eq_and(std::function<Comparison<dc>()> fun)
 {
  return _and(0, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> ne_and(std::function<Comparison<dc>()> fun)
 {
  return _and(1, 3, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> le_and(std::function<Comparison<dc>()> fun)
 {
  return _and(0, 3, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> lt_and(std::function<Comparison<dc>()> fun)
 {
  return _and(3, fun);
 }


 void gt_do(std::function<void()> fun)
 {
  _do(1, fun);
 }

 void ge_do(std::function<void()> fun)
 {
  _do(1, 0, fun);
 }

 void eq_do(std::function<void()> fun)
 {
  _do(0, fun);
 }

 void ne_do(std::function<void()> fun)
 {
  _do(1, 3, fun);
 }

 void le_do(std::function<void()> fun)
 {
  _do(0, 3, fun);
 }

 void lt_do(std::function<void()> fun)
 {
  _do(3, fun);
 }


};



template<>
class Comparison<Dimensions_Of_Comparison::Taxonomic> : Comparison_Base
{
 friend struct Comparison_Base;
 Comparison() : Comparison_Base()
 {

 }

public:

 Comparison(signed int r)
  : Comparison_Base(unit_normalize(r))
 {

 }

 static Comparison no_comparison()
 {
  Comparison result;
  result.result_ = -1;
  return result;
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> below_and(std::function<Comparison<dc>()> fun)
 {
  return _and(1, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> not_below_and(std::function<Comparison<dc>()> fun)
 {
  return _and(0, -1, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> same_and(std::function<Comparison<dc>()> fun)
 {
  return _and(0, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> not_same_and(std::function<Comparison<dc>()> fun)
 {
  return _and(1, -1, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> not_unrelated_and(std::function<Comparison<dc>()> fun)
 {
  return _and(0, 1, fun);
 }

 template<Dimensions_Of_Comparison dc>
 Comparison<dc> unrelated_and(std::function<Comparison<dc>()> fun)
 {
  return _and(-1, fun);
 }


 void below_do(std::function<void()> fun)
 {
  _do(1, fun);
 }

 void not_below_do(std::function<void()> fun)
 {
  _do(0, -1, fun);
 }

 void same_do(std::function<void()> fun)
 {
  _do(0, fun);
 }

 void not_same_do(std::function<void()> fun)
 {
  _do(1, -1, fun);
 }

 void not_unrealted_do(std::function<void()> fun)
 {
  _do(0, 1, fun);
 }

 void unrealted_do(std::function<void()> fun)
 {
  _do(-1, fun);
 }

};


#endif
