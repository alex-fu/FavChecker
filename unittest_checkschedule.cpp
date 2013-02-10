/*
 * =====================================================================================
 *
 *       Filename:  unittest_checkschedule.cpp
 *
 *    Description:  Unit test for CheckSchedule class
 *
 *        Version:  1.0
 *        Created:  02/09/2013 04:11:06 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alex Fu (AF), fyfhust@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifdef _UNIT_TEST

#define BOOST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>

#include "UnitTest.h"
#include "CheckSchedule.h"
#include "DateTime.h"

using namespace std;
using namespace boost;

AUTO_TEST_SUITE(s_checkschedule)

AUTO_TEST_CASE(t_checkscheduleHML)
{
    CheckSchedule cs;

    {
        //schedule with hour, minute, loop
        int hour = 10; //max: 23, min: 0
        int minute = 0;
        bool loop = true;
        cs.setCheckSchedule(hour, minute, loop);
        CHECK_EQUAL(cs.getCheckSchedule(), "HML");
    }

    {
        //Test loop==0
        bool loop = false;
        DateTime now = DateTime::now();
        cs.setCheckSchedule(now.hour(), now.minute(), loop);
        CHECK_EQUAL(cs.getCheckSchedule(), "HML");
        sleep(1);
        CHECK(cs.getNextCheckTime() == DateTime::invalid_datetime());
//        CHECK_EQUAL(cs.getNextCheckTime(), DateTime::invalid_datetime()); //doesn't work
    }

    {
        //Test time after today's check time
        bool loop = true;
        DateTime now = DateTime::now();
        cs.setCheckSchedule(now.hour(), now.minute(), loop);
        CHECK_EQUAL(cs.getCheckSchedule(), "HML");
        sleep(1);
        DateTime next = now + TimeDuration(24, 0, 0);
//        CHECK_EQUAL(cs.getNextCheckTime(), next); //doesn't work because this 2 may have little difference
        TimeDuration td = cs.getNextCheckTime() - next;
        CHECK_LT(td.total_seconds(), 1);
    }

    {
        //Test time after today's check time
        bool loop = true;
        DateTime now = DateTime::now();
        DateTime next = now - TimeDuration(1, 0, 0);
        cs.setCheckSchedule(next.hour(), next.minute(), loop);
        CHECK_EQUAL(cs.getCheckSchedule(), "HML");
        next = next + TimeDuration(24, 0, 0);
        TimeDuration td = cs.getNextCheckTime() - next;
        CHECK_LT(td.total_seconds(), 1);
    }

    {
        //Test time before today's check time
        bool loop = true;
        DateTime now = DateTime::now();
        DateTime next = now + TimeDuration(1, 0, 0);
        cs.setCheckSchedule(next.hour(), next.minute(), loop);
        CHECK_EQUAL(cs.getCheckSchedule(), "HML");
        TimeDuration td = cs.getNextCheckTime() - next;
        CHECK_LT(td.total_seconds(), 1);
    }

}

AUTO_TEST_SUITE_END()

#endif
