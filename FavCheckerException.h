////////////////////////////////////////////////////////////////
///
/// @file FavCheckerException.h
/// @brief This file describe the Favourite list class
/// @author Alex Fu <alex.fu@emc.com>
/// @version 1.0
/// @date 2013-01-23
///
////////////////////////////////////////////////////////////////

#ifndef _FAVCHECKEREXCEPTION_H_
#define _FAVCHECKEREXCEPTION_H_

#include <exception>

class FavCheckerException : public std::exception
{
public:
    virtual const char * what() const throw()
    {
        return "FavCheckerException happened!";
    }
};



#endif  // _FAVCHECKEREXCEPTION_H_
