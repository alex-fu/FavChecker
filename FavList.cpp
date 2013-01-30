////////////////////////////////////////////////////////////////
///
/// @file FavList.cpp
/// @brief This file describe the Favourite list class
/// @author Alex Fu <alex.fu@emc.com>
/// @version 1.0
/// @date 2013-01-23
///
////////////////////////////////////////////////////////////////

#include "FavList.h"
#include "Log.h"
#include "FavCheckerException.h"

using namespace std;

/////////////////////////////////////////
//
// Entry for FavItem implementation
//
/////////////////////////////////////////

const char* FavItem::FavItemTypeStr[] = {
    "Default Fav Item",
    "User Defined Fav Item",
    "Auto Generate Fav Item"
};

const char* FavItem::FavItemStsStr[] = {
    "Default Fav Item Status",
    "Has New Update on Fav Item",
    "No New Updates on Fav Item"
};

FavItem::FavItem(string url, FavItemType_e type)
    :url(url), type(type)
{
    status = FavItemSts_Dft;
    lastCheckTime = DFT_TIME;
    lastUpdateTime = DFT_TIME;
    sublist = NULL;
}

FavItem::FavItem(string arString)
{
    //TODO: ensure arString is a file
    unpack(arString);
}

FavItem::~FavItem()
{
    //TODO: For future: can apply Factory Pattern
    destroySubFavList();
    debug("FavItem[url: %s] was destroyed", this->url.c_str());
}

void FavItem::createSubFavList(void)
{
    sublist = new SubFavList();
    if(sublist != NULL)
    {
        debug("Created subfavlist successful for item[url: %s]", url.c_str());
        return;
    }
    debug("Created subfavlist failed for item[url: %s]", url.c_str());
}

void FavItem::destroySubFavList(void)
{
    if(sublist != NULL)
    {
        sublist->freeItems();
        delete sublist;
        debug("SubFavList from FavItem[url: %s] was destroyed", this->url.c_str());
    }
}

string FavItem::pack(void)
{
    //Need to add some try...catch
    //TODO: use proper library to serilize or pack the class
    //First, pack self
    //Second,
    //if(sublist)
    //{
    //    sublist.pack();
    //}
    //Third, combine them together
}

void FavItem::unpack(string arString)
{
    //Need to add some try...catch
    //TODO: use proper library to deserilize or unpack the class
    //reverse the pack steps
}





/////////////////////////////////////////
//
// Entry for FavList implementation
//
/////////////////////////////////////////

FavList::FavList(void)
    : _type(FavListType_Main)
{

}

FavList::~FavList(void)
{
    freeItems();
}

int FavList::size(void)
{
    return _favList.size();
}

FavItem * FavList::operator[](int index)
{
    return _favList[index];
}

FavItem * FavList::addFavItem(std::string url)
{
    FavItem * fi = NULL;

    fi = new FavItem(url, FavItem::FavItemType_UserDefined);
    //then attach to list
    _attachFavItem(fi);

    return fi;
}

void FavList::delFavItem(string url)
{
    //find the FavItem
    int index = findFavItem(url);
    FavItem *fi = _favList[index];

    //first detach from list
    _detachFavItem(index);

    try
    {
        //call fi's destroySubFavList
        fi->destroySubFavList();
    }
    catch(FavCheckerException & e)
    {
        cerr << e.what();
        //FIXME:
    }
    delete fi;
    debug("Delete FavItem[url: %s] successful", url.c_str());
}

//return index for favItem if found, index begin from 0
int FavList::findFavItem(string url)
{
    if(!_favList.empty())
    {
        for(int i=0; i<_favList.size(); i++)
        {
            if(_favList[i]->getUrl().compare(url) == 0)
            {
                //found it
                debug("Found the favItem[url: %s] in favlist[index: %d]", url.c_str(), i);
                return i;
            }

        }

        warn("Didn't find favitem[url: %s] in favlist", url.c_str());
    }
    else
    {
        warn("FavList is empty");
    }
    return INVALID_VECTOR_INDEX;
}

void FavList::freeItems(void)
{
    int vlen = _favList.size();
    for(int i=0; i<vlen; i++)
    {
        //TODO: Try to substitute with iterator
        FavItem * fi = _favList[i];
        delFavItem(fi->getUrl());
    }
}

void FavList::_attachFavItem(FavItem *favItem)
{
    _favList.push_back(favItem);
    debug("Attach a new favitem[url: %s] to favlist", favItem->getUrl().c_str());
}

void FavList::_detachFavItem(int index)
{
    if(!_favList.empty())
    {
        if(index != INVALID_VECTOR_INDEX)
        {
            //use begin()+index to locate the iterator
            //index begin from 0
            _favList.erase(_favList.begin() + index);
            debug("Detach favitem[index: %d] from favlist", index);
        }
        else
        {
            warn("Didn't find favitem[index: %d] in favlist", index);
        }
    }
    warn("FavList is empty");
}


string FavList::pack()
{
    //TODO: find some library to serialize the structure

}

void FavList::unpack(string arString)
{
    //TODO:
}






/////////////////////////////////////////
//
// Entry for SubFavList implementation
//
/////////////////////////////////////////

SubFavList::SubFavList()
{
    ziPolicy = NULL;
    _type = FavListType_Sub;
}

SubFavList::~SubFavList(void)
{
    freeItems();
}

FavItem * SubFavList::addFavItem(std::string url)
{
    FavItem * fi = NULL;

    fi = new FavItem(url, FavItem::FavItemType_AutoGen);
    //then attach to list
    _attachFavItem(fi);

    return fi;
}

void SubFavList::autoRemoveZombie()
{
    //TODO:

}







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
    for(int i=0; i<list.size(); i++)
    {
        FavItem *fi = list[i];
        cout << "Item " << setw(2) << dec << i << ":\t\t"
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
    for(int i=0; i<list.size(); i++)
    {
        FavItem *fi = list[i];
        cout << "Item " << setw(2) << dec << i << ":\t"
           << "Url: " << fi->getUrl() << "\t"
           << "Type: " << fi->getType() << "\t"
           << "Status: " << fi->getStatus() << endl;
    }

}

#endif
