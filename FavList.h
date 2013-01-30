////////////////////////////////////////////////////////////////
///
/// @file FavList.h
/// @brief This file describe the Favourite list class
/// @author Alex Fu <alex.fu@emc.com>
/// @version 1.0
/// @date 2013-01-23
///
////////////////////////////////////////////////////////////////

#ifndef _FAVLIST_H_
#define _FAVLIST_H_

#include "head.h"
#include "DateTime.h"
#include "ZombieItemPolicy.h"

class FavList;
class SubFavList;

//Favourite item
class FavItem
{
public:
    typedef enum FavItemType
    {
        FavItemType_Dft,
        FavItemType_UserDefined,
        FavItemType_AutoGen,
        FavItemType_MAX
    }FavItemType_e;

    typedef enum FavItemSts
    {
        FavItemSts_Dft,
        FavItemSts_HasNew,
        FavItemSts_NoNew,
        FavItemSts_MAX
    }FavItemSts_e;

    const static char* FavItemTypeStr[FavItemType_MAX];
    const static char* FavItemStsStr[FavItemSts_MAX];

    FavItem(std::string url, FavItemType_e type);
    FavItem(std::string arString);
    virtual ~FavItem(void);

    std::string getUrl()
    {
        return url;
    }

    std::string getType()
    {
        return FavItemTypeStr[this->type];
    }

    std::string getStatus()
    {
        return FavItemStsStr[this->status];
    }

    void createSubFavList(void);
    void destroySubFavList(void);

    //pack and unpack functions
    //json file or string
    std::string pack(void);
    void unpack(std::string arString);

private: 
    std::string url;
    FavItemType_e type;
    FavItemSts_e status;
    DateTime lastCheckTime;
    DateTime lastUpdateTime;

    SubFavList *sublist;
};

class FavList
{
public:
    typedef enum FavListType
    {
        FavListType_Main,
        FavListType_Sub
    }FavListType_e;

    static const int INVALID_VECTOR_INDEX = -1;

    FavList(void);
    virtual ~FavList(void);

    int size();

    FavItem * operator[](int index); //TODO

    virtual FavItem * addFavItem(std::string url);
    void delFavItem(std::string url);

    int findFavItem(std::string url);

    void freeItems(void);

    std::string pack(void);
    void unpack(std::string arString);

protected:
    void _attachFavItem(FavItem * favItem);
    void _detachFavItem(int index);

protected:
    std::vector<FavItem *> _favList;
    FavListType_e _type;

};

class SubFavList : public FavList
{
public:
    SubFavList();
    virtual ~SubFavList();

    virtual FavItem * addFavItem(std::string url);

    void autoRemoveZombie(void);

private:
    ZombieItemPolicy *ziPolicy;

};

#ifdef _UNIT_TEST
int unitTest_FavList(void);
#endif

#endif //_FAVLIST_H_
