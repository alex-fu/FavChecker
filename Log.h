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
#define err(fmt, args...)   fprintf(stderr, STRERROR#fmt#CRLF, ##args)
#define warn(fmt, args...)  fprintf(stdout, STRWARN#fmt#CRLF, ##args)
#define info(fmt, args...)  fprintf(stdout, STRINFO#fmt#CRLF, ##args)

#ifdef _DEBUG
#define debug(fmt, args...) fprintf(stdout, STRDEBUG#fmt#CRLF, ##args)
#else
#define debug(fmt, args...) 
#endif


#endif //_LOG_H_
