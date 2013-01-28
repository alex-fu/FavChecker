////////////////////////////////////////////////////////////////
///
/// @file main.cpp
/// @brief Unit test main procedure
/// @author Alex Fu <alex.fu@emc.com>
/// @version 1.0
/// @date 2013-01-28
///
////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include "FavList.h"

using namespace std;

int main(int argc, char *argv[])
{
    //TODO: use BOOST test framework
#ifdef _UNIT_TEST
    cout << "Start FavChecker unit test" << endl;
    unitTest_FavList();


    cout << "Finish FavChecker unit test" << endl;
#endif

    return 0;
}

