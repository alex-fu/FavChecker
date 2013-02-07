///////////////////////////////////////////////////////////////
///
/// @file unittest_favlist.cpp
/// @brief Unit test function for Favlist
/// @author Alex Fu <alex.fu@emc.com>
/// @version Alex Fu
/// @date 2013-02-07
///
///////////////////////////////////////////////////////////////

#include "FavList.h"

using namespace std;

/////////////////////////////////////////
//
// Unit test function for Favlist
//
/////////////////////////////////////////
#ifdef _UNIT_TEST


int unitTest_FavList()
{
    FavList list;
    cout << "UNIT TEST --- Fav List submodule" << endl;

    //test add
    cout << "UNIT TEST --- Add Fav Item" << endl;
    for(int i=0; i<10; i++)
    {
        stringstream urlss;
        urlss << "http://www.example.com/test" << std::dec << i;
        list.addFavItem(urlss.str());
    }
    cout << "UNIT TEST --- Added " << list.size() << " items to Fav List" << endl;
    //show list
    cout << "UNIT TEST --- Show Fav List" << endl;
    for(uint32_t i=0; i<list.size(); i++)
    {
        FavItem *fi = list[i];
        cout << "Item " << setw(2) << dec << i << ":\t"
           << "Url: " << fi->getUrl() << "\t"
           << "Type: " << fi->getType() << "\t"
           << "Status: " << fi->getStatus() << endl;
    }

    //test del
    cout << "UNIT TEST --- Del Fav Item" << endl;
    stringstream urlss;
    urlss << "http://www.example.com/test3";
    list.delFavItem(urlss.str());

    urlss.str("");
    urlss << "http://www.example.com/test7";
    list.delFavItem(urlss.str());

    urlss.str("");
    urlss << "http://www.example.com/test10";
    list.delFavItem(urlss.str());

    //show list
    cout << "UNIT TEST --- Show Fav List" << endl;
    for(uint32_t i=0; i<list.size(); i++)
    {
        FavItem *fi = list[i];
        cout << "Item " << setw(2) << dec << i << ":\t"
           << "Url: " << fi->getUrl() << "\t"
           << "Type: " << fi->getType() << "\t"
           << "Status: " << fi->getStatus() << endl;
    }

    return 0;
}

#endif
