///   @file CheckSchedule.h
///   @brief Define the check schedule
///   @author Alex Fu <alex.fu@emc.com>
///   @version 1.0
///   @date 2013-02-09



#ifndef _CHECKSCHEDULE_H_
#define _CHECKSCHEDULE_H_

#include "types.h"
#include "DateTime.h"

class ScheduleType
{
public:
    virtual const std::string name() { return "Unknown ScheduleType"; }

    virtual DateTime getNextCheckTime() = 0;
};

class HMLSchedType : public ScheduleType
{
public:
    virtual const std::string name() { return "HML"; }

    virtual DateTime getNextCheckTime();

public:
    uint8_t hour;
    uint8_t minute;
    bool loop;
};

class CheckSchedule
{
public:
    CheckSchedule();
    ~CheckSchedule();

    void setCheckSchedule(uint8_t hour, uint8_t min, bool loop);
    std::string getCheckSchedule();
    DateTime getNextCheckTime();

private:
    ScheduleType *__schedType;
};



#endif  // _CHECKSCHEDULE_H_
