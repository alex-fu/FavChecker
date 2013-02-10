////////////////////////////////////////////////////////////////////
///
/// @file DateTime.cpp
/// @brief Define DateTime helper class
/// @author Alex Fu <alex.fu@emc.com>
/// @version 1.0
/// @date 2013-01-23
///
////////////////////////////////////////////////////////////////////

#include "DateTime.h"

DateTime DFT_TIME;

DateTime::DateTime()
    : __datetime(microsec_clock::local_time())
{
}

DateTime::DateTime(Date date, TimeDuration time)
{
    ptime pt(date.__date, time.__duration);
    __datetime = pt;
}

DateTime::DateTime(const DateTime & dt)
{
    __datetime = dt.__datetime;
}

DateTime::~DateTime()
{
}

DateTime DateTime::invalid_datetime()
{
    DateTime dt;

    ptime pt(not_a_date_time);
    dt.__datetime = pt;

    return dt;
}

DateTime DateTime::now()
{
    return DateTime();
}

