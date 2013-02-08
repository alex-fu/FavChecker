///////////////////////////////////////////////////////////////
///
/// @file unittest_favlist.cpp
/// @brief Unit test function for Favlist
/// @author Alex Fu <alex.fu@emc.com>
/// @version Alex Fu
/// @date 2013-02-07
///
///////////////////////////////////////////////////////////////

#ifdef _UNIT_TEST

#define BOOST_TEST_INCLUDED
#include <boost/test/unit_test.hpp>

#include "UnitTest.h"
#include "FavList.h"

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(s_favlist)

/////////////////////////////////////////
//
// Unit test function for Favlist
//
/////////////////////////////////////////
BOOST_AUTO_TEST_CASE(t_favlist)
{
    FavList list;
    TEST_MESSAGE("UNIT TEST --- Fav List submodule");

    //test add
    TEST_MESSAGE("UNIT TEST --- Add Fav Item");
    for(int i=0; i<10; i++)
    {
        stringstream urlss;
        urlss << "http://www.example.com/test" << std::dec << i;
        list.addFavItem(urlss.str());
    }
    BOOST_MESSAGE("UNIT TEST --- Added items to Fav List");
    
    CHECK_EQUAL(list.size(), 10);

    //show list
    TEST_MESSAGE("UNIT TEST --- Show Fav List");
    for(uint32_t i=0; i<list.size(); i++)
    {
        FavItem *fi = list[i];
        cout << "Item " << setw(2) << dec << i << ":\t"
           << "Url: " << fi->getUrl() << "\t"
           << "Type: " << fi->getType() << "\t"
           << "Status: " << fi->getStatus() << endl;
    }

    //test del
    TEST_MESSAGE("UNIT TEST --- Del Fav Item");
    stringstream urlss;
    urlss << "http://www.example.com/test3";
    list.delFavItem(urlss.str());

    CHECK_EQUAL(list.size(), 9);

    urlss.str("");
    urlss << "http://www.example.com/test7";
    list.delFavItem(urlss.str());

    CHECK_EQUAL(list.size(), 8);

    urlss.str("");
    urlss << "http://www.example.com/test10";
    list.delFavItem(urlss.str());

    CHECK_EQUAL(list.size(), 8);

    //show list
    TEST_MESSAGE("UNIT TEST --- Show Fav List");
    for(uint32_t i=0; i<list.size(); i++)
    {
        FavItem *fi = list[i];
        cout << "Item " << setw(2) << dec << i << ":\t"
           << "Url: " << fi->getUrl() << "\t"
           << "Type: " << fi->getType() << "\t"
           << "Status: " << fi->getStatus() << endl;
    }
}

BOOST_AUTO_TEST_SUITE_END()

#endif
