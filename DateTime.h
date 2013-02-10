////////////////////////////////////////////////////////////////////
///
/// @file DateTime.h
/// @brief Define DateTime helper class
/// @author Alex Fu <alex.fu@emc.com>
/// @version 1.0
/// @date 2013-01-23
///
////////////////////////////////////////////////////////////////////

#ifndef _DATETIME_H_
#define _DATETIME_H_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace boost::posix_time;
using namespace boost::gregorian;

class Date
{
public:
    Date(date d)
    {
        __date = d;
    }
    ~Date() {}

    friend class DateTime;

private:
    date __date;
};

class TimeDuration
{
public:
    TimeDuration(uint32_t hour, uint32_t minute, uint32_t second, uint64_t microsecond = 0)
        : __duration(hour, minute, second, microsecond)
    {}

    ~TimeDuration() {}

    friend class DateTime;

    inline long total_seconds() const      { return __duration.total_seconds(); };

    inline long total_milliseconds() const { return __duration.total_milliseconds(); };

    inline long total_microseconds() const { return __duration.total_microseconds(); };

protected:
    TimeDuration(time_duration & duration)
        : __duration(duration)
    {}

private:
    time_duration __duration;
};

class DateTime
{
public:
    DateTime();

    DateTime(Date date, TimeDuration time);

    DateTime(const DateTime & dt);

    ~DateTime();

    static DateTime now();
    static DateTime invalid_datetime();

    Date date()
    {
        return Date(__datetime.date());
    }

    TimeDuration timeOfDay()
    {
        time_duration td = __datetime.time_of_day();
        return TimeDuration(td);
    }
    uint32_t hour()
    {
        return __datetime.time_of_day().hours();
    }
    uint32_t minute()
    {
        return __datetime.time_of_day().minutes();
    }
    uint32_t second()
    {
        return __datetime.time_of_day().seconds();
    }

    TimeDuration operator-(const DateTime &dt)
    {
        time_duration td = this->__datetime - dt.__datetime;
        return TimeDuration(td);
    }

    DateTime operator+(const TimeDuration & duration)
    {
        DateTime dt;
        dt.__datetime += duration.__duration;
        return dt;
    }
    DateTime operator-(const TimeDuration & duration)
    {
        DateTime dt;
        dt.__datetime -= duration.__duration;
        return dt;
    }

    bool operator==(const DateTime &dt)
    {
        return (__datetime == dt.__datetime);
    }
    bool operator!=(const DateTime &dt)
    {
        return (__datetime != dt.__datetime);
    }
    bool operator<=(const DateTime &dt)
    {
        return (__datetime <= dt.__datetime);
    }
    bool operator>=(const DateTime &dt)
    {
        return (__datetime >= dt.__datetime);
    }
    bool operator<(const DateTime &dt)
    {
        return (__datetime < dt.__datetime);
    }
    bool operator>(const DateTime &dt)
    {
        return (__datetime > dt.__datetime);
    }

private:
    ptime __datetime;
    
};

extern DateTime DFT_TIME;


#endif // _DATETIME_H_
