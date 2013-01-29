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

class DateTime
{
public:
    DateTime()
    {
        this->datetime = 0;
    }

    DateTime(long long datetime)
    {
        this->datetime = datetime;
    }

private:
    long long datetime;
};

extern DateTime DFT_TIME;


#endif // _DATETIME_H_
