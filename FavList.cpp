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
    return "Unrealized";
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

uint32_t FavList::size(void)
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
    vector<FavItem *>::iterator it = findFavItem(url);
    if(it != _favList.end())
    {
        delFavItem(it);
    }
    else
    {
        warn("Delete url failed: Didnot find favitem[url: %s] in favlist", url.data());
    }
    return;
}

void FavList::delFavItem(vector<FavItem *>::iterator it)
{
    FavItem *fi = *it;
    string url = fi->getUrl();

    //first detach from list
    _detachFavItem(it);

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
    debug("Delete FavItem[url: %s] successful", url.data());
}



//return index for favItem if found, index begin from 0
vector<FavItem *>::iterator FavList::findFavItem(string url)
{
#if 0
    if(!_favList.empty())
    {
        for(uint32_t i=0; i<_favList.size(); i++)
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
#else
    UrlCompare urlcmp;
    urlcmp.url = url;

    vector<FavItem *>::iterator it;

    it = find_if(_favList.begin(), _favList.end(), urlcmp);

    //we also can use boost::bind to achieve this
//    it = find_if(_favList.begin(), _favList.end(), boost::bind(&FavItem::url, _1) == url);

    return it;
#endif
}

void FavList::freeItems(void)
{
    vector<FavItem *>::iterator it;

    uint32_t vlen = _favList.size();
    //it's more convenient to use number loop instead of iterator
    for(int i=vlen-1; i>=0; i--)
    {
        it = _favList.begin() + i;
        if(it != _favList.end())
            delFavItem(it);
    }
}

void FavList::_attachFavItem(FavItem *favItem)
{
    _favList.push_back(favItem);
    debug("Attach a new favitem[url: %s] to favlist", favItem->getUrl().c_str());
}

void FavList::_detachFavItem(vector<FavItem *>::iterator it)
{
    if(!_favList.empty())
    {
        //save url first before erase
        FavItem *fi = *it;
        string url = fi->getUrl();
        _favList.erase(it);
        debug("Detach favitem[url: %s] from favlist", url.data());
        return;
    }
    warn("FavList is empty");
    return;
}


string FavList::pack()
{
    //TODO: find some library to serialize the structure

    return "Unrealized";
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







