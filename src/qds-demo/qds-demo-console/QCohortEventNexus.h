
//          Copyright Nathaniel Christen 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef QCOHORTEVENTNEXUS__H
#define QCOHORTEVENTNEXUS__H

#include <QString>
#include <QVariant>
#include <functional>



template<typename EVENT_Type,
         typename GROUND_Type,
         typename OBSERVATION_Type>
class QCohortEventNexus
{
 typedef QCohortEventNexus<EVENT_Type, GROUND_Type, OBSERVATION_Type> this_type;

protected:

 EVENT_Type* event_object_;
 GROUND_Type* ground_object_;
 OBSERVATION_Type* observation_object_;

 //?GETTER(EVENT_Type ,event_object)


public:

 typename EVENT_Type::Comparison_Result_Monad_type event_comparison(const QCohortEventNexus& this_type,
   std::function<typename EVENT_Type::Comparison_Result_Monad_type (const EVENT_Type&,
                                                                    const EVENT_Type&)> fval)
 {
  if(event_object_)
  {
   return fval(*event_object_, *this_type.event_object_);
  }
  else
  {
   return EVENT_Type::Comparison_Result_Monad_type::no_comparison();
  }
 }

 typename OBSERVATION_Type::Comparison_Ordinal_Result_Monad_type observation_ordinal_comparison(const QCohortEventNexus& this_type,
   std::function<typename OBSERVATION_Type::Comparison_Ordinal_Result_Monad_type (const OBSERVATION_Type&,
                                                                    const OBSERVATION_Type&)> fval) const
 {
  if(observation_object_)
  {
   return fval(*observation_object_, *this_type.observation_object_);
  }
  else
  {
   return OBSERVATION_Type::Comparison_Ordinal_Result_Monad_type::no_comparison();
  }
 }

 typename OBSERVATION_Type::Comparison_Ordinal_Result_Monad_type observation_ordinal_comparison
 (QVariant qvar,
   std::function<typename OBSERVATION_Type::Comparison_Ordinal_Result_Monad_type (const OBSERVATION_Type&,
   QVariant)> fval) const
 {
  if(observation_object_)
  {
   return fval(*observation_object_, qvar);
  }
  else
  {
   return OBSERVATION_Type::Comparison_Ordinal_Result_Monad_type::no_comparison();
  }
 }



 typename GROUND_Type::Comparison_Ordinal_Result_Monad_type ground_ordinal_comparison(const QCohortEventNexus& this_type,
   std::function<typename GROUND_Type::Comparison_Ordinal_Result_Monad_type (const GROUND_Type&,
                                                                    const GROUND_Type&)> fval) const
 {
  if(ground_object_)
  {
   return fval(*ground_object_, *this_type.ground_object_);
  }
  else
  {
   return GROUND_Type::Comparison_Ordinal_Result_Monad_type::no_comparison();
  }
 }

 typename GROUND_Type::Comparison_Nominal_Result_Monad_type ground_nominal_comparison(const QCohortEventNexus& this_type,
   std::function<typename GROUND_Type::Comparison_Nominal_Result_Monad_type (const GROUND_Type&,
                                                                    const GROUND_Type&)> fval) const
 {
  if(ground_object_)
  {
   return fval(*ground_object_, *this_type.ground_object_);
  }
  else
  {
   return GROUND_Type::Comparison_Nominal_Result_Monad_type::no_comparison();
  }
 }


 typename GROUND_Type::Comparison_Uniqueness_Result_Monad_type ground_uniqueness_comparison(const QCohortEventNexus& this_type,
   std::function<typename GROUND_Type::Comparison_Uniqueness_Result_Monad_type (const GROUND_Type&,
                                                                    const GROUND_Type&)> fval) const
 {
  if(ground_object_)
  {
   return fval(*ground_object_, *this_type.ground_object_);
  }
  else
  {
   return GROUND_Type::Comparison_Uniqueness_Result_Monad_type::no_comparison();
  }
 }

};



#endif
