/*
 * =====================================================================================
 *
 *       Filename:  UnitTest.h
 *
 *    Description:  Define unit test functions
 *
 *        Version:  1.0
 *        Created:  02/08/2013 12:59:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Alex Fu (AF), fyfhust@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef _UNITTEST_H_
#define _UNITTEST_H_

#include <boost/test/unit_test.hpp>

#define AUTO_TEST_SUITE(s_name) BOOST_AUTO_TEST_SUITE(s_name)
#define AUTO_TEST_CASE(t_name) BOOST_AUTO_TEST_CASE(t_name)
#define AUTO_TEST_SUITE_END() BOOST_AUTO_TEST_SUITE_END()

//this 3 function for print messages
#define TEST_MESSAGE(message) BOOST_TEST_MESSAGE(message) //print message, no error happened
#define TEST_ERROR(message) BOOST_ERROR(message)  //print error message, continue test
#define TEST_FAIL(message) BOOST_FAIL(message)  //print error message, drop test

/**
 * Validation functions for each level
+-------------+--------------------+----------------------+
| Level       | Count error?       | Drop test if error?  |
+-------------+--------------------+----------------------+
| WARN        | No                 | No                   |
+-------------+--------------------+----------------------+
| CHECK       | Yes                | No                   |
+-------------+--------------------+----------------------+
| REQUIRE     | Yes                | Yes                  |
+-------------+--------------------+----------------------+
*/

//WARN level validation
#define WARN_EQUAL(l, r)  BOOST_WARN_EQUAL(l, r)
#define WARN_GE(l, r)  BOOST_WARN_GE(l, r)
#define WARN_GT(l, r)  BOOST_WARN_GT(l, r)
#define WARN_LE(l, r)  BOOST_WARN_LE(l, r)
#define WARN_LT(l, r)  BOOST_WARN_LT(l, r)
#define WARN_NE(l, r)  BOOST_WARN_NE(l, r)
#define WARN(expr)  BOOST_WARN(expr)
#define WARN_MESSAGE(expr, message)  BOOST_WARN_MESSAGE(expr, message)
#define WARN_THROW(expr, exception)  BOOST_WARN_THROW(expr, exception)
#define WARN_NO_THROW(expr, exception)  BOOST_WARN_NO_THROW(expr, exception)

//CHECK level validation
#define CHECK_EQUAL(l, r)  BOOST_CHECK_EQUAL(l, r)
#define CHECK_GE(l, r)  BOOST_CHECK_GE(l, r)
#define CHECK_GT(l, r)  BOOST_CHECK_GT(l, r)
#define CHECK_LE(l, r)  BOOST_CHECK_LE(l, r)
#define CHECK_LT(l, r)  BOOST_CHECK_LT(l, r)
#define CHECK_NE(l, r)  BOOST_CHECK_NE(l, r)
#define CHECK(expr)  BOOST_CHECK(expr)
#define CHECK_MESSAGE(expr, message)  BOOST_CHECK_MESSAGE(expr, message)
#define CHECK_THROW(expr, exception)  BOOST_CHECK_THROW(expr, exception)
#define CHECK_NO_THROW(expr, exception)  BOOST_CHECK_NO_THROW(expr, exception)

//REQUIRE level validation
#define REQUIRE_EQUAL(l, r)  BOOST_REQUIRE_EQUAL(l, r)
#define REQUIRE_GE(l, r)  BOOST_REQUIRE_GE(l, r)
#define REQUIRE_GT(l, r)  BOOST_REQUIRE_GT(l, r)
#define REQUIRE_LE(l, r)  BOOST_REQUIRE_LE(l, r)
#define REQUIRE_LT(l, r)  BOOST_REQUIRE_LT(l, r)
#define REQUIRE_NE(l, r)  BOOST_REQUIRE_NE(l, r)
#define REQUIRE(expr)  BOOST_REQUIRE(expr)
#define REQUIRE_MESSAGE(expr, message)  BOOST_REQUIRE_MESSAGE(expr, message)
#define REQUIRE_THROW(expr, exception)  BOOST_REQUIRE_THROW(expr, exception)
#define REQUIRE_NO_THROW(expr, exception)  BOOST_REQUIRE_NO_THROW(expr, exception)

#endif  // _UNITTEST_H_
