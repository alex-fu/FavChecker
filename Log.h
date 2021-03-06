////////////////////////////////////////////////////////////////
///
/// @file Log.h
/// @brief This file describe the log helper functions
/// @author Alex Fu <alex.fu@emc.com>
/// @version 1.0
/// @date 2013-01-23
///
////////////////////////////////////////////////////////////////

#ifndef _LOG_H_
#define _LOG_H_

#include <stdio.h>

#define STRERROR "[Error]: "
#define STRWARN  "[Warn ]: "
#define STRINFO  "[Info ]: "
#define STRDEBUG "[Debug]: "

#ifdef _WINDOWS
#define CRLF     "\n\r"
#else
#define CRLF     "\n"
#endif

//FIXME: Large improvement space
#define error(fmt, args...)   fprintf(stderr, STRERROR#fmt "\n", ##args)
#define warn(fmt, args...)  fprintf(stdout, STRWARN#fmt "\n", ##args)
#define info(fmt, args...)  fprintf(stdout, STRINFO#fmt "\n", ##args)

#ifdef _DEBUG
#define debug(fmt, args...) fprintf(stdout, STRDEBUG#fmt "\n", ##args)
#else
#define debug(fmt, args...) 
#endif

#ifdef _DEBUG
#define ENTER_FUNCTION()  fprintf(stdout, "[ENTER FUNCTION]: " __FUNCTION__ "\n")
#define LEAVE_FUNCTION()  fprintf(stdout, "[LEAVE FUNCTION]: " __FUNCTION__ "\n")
#else
#define ENTER_FUNCTION() 
#define LEAVE_FUNCTION()
#endif

#endif //_LOG_H_
