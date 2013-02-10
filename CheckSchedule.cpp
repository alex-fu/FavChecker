///   @file CheckSchedule.cpp
///   @brief Implement for CheckSchedule
///   @author Alex Fu <alex.fu@emc.com>
///   @version 1.0
///   @date 2013-02-09


#include "CheckSchedule.h"

CheckSchedule::CheckSchedule()
{
    __schedType = NULL;
    setCheckSchedule(0, 0, false);
}

CheckSchedule::~CheckSchedule()
{
    if(__schedType != NULL)
    {
        delete __schedType;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///   @brief Set check schedule by hour, minute, loop
///
///   @param hour - set hour of checktime
///   @param min  - set minute of checktime
///   @param loop - choose whether to loop
///////////////////////////////////////////////////////////////////////////////////////////////////////
void CheckSchedule::setCheckSchedule(uint8_t hour, uint8_t min, bool loop)
{
    if(__schedType != NULL)
    {
        delete __schedType;
    }

    __schedType = new HMLSchedType();

    if(__schedType == NULL)
    {
        throw;
    }

    HMLSchedType * hml = dynamic_cast<HMLSchedType *>(__schedType);
    hml->hour = hour;
    hml->minute = min;
    hml->loop = loop;
}

std::string CheckSchedule::getCheckSchedule()
{
    return __schedType->name();
}

DateTime CheckSchedule::getNextCheckTime()
{
    HMLSchedType * hml = dynamic_cast<HMLSchedType *>(__schedType);
    if(hml != NULL)
        return __schedType->getNextCheckTime();
    else
        return DateTime::invalid_datetime();
}

//////////////////////////////////////////////////
/// functions for HMLSchedType
//////////////////////////////////////////////////

DateTime HMLSchedType::getNextCheckTime()
{
    DateTime now = DateTime::now();
    //use now.date, only change with this->hour and this->minute
    DateTime objtime(now.date(), TimeDuration(hour, minute, 0));
    
    if(now < objtime)
    {
        return objtime;
    }
    else
    {
        if(loop)
        {
            //now.date plus 1 day, as well as this->hour and this->minute
            return objtime + TimeDuration(24, 0, 0);
        }
        else
        {
            return DateTime::invalid_datetime();
        }
    }
}

