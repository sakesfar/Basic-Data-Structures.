#include <iostream>
#include <vector>
#include <list>

// Possible Hash functions (as Hash Class) with an example for std::string data type as KEY
//If 'key' is a user defined data type , then build an appopriate templated Hash class

template <typename Key>
class Hash
{
public:
    size_t operator() (const Key& key) const {}

};


template<>
class Hash<std::string>
{
public:
    size_t operator() (const std::string& key) const
    {
        size_t hashVal = 0;
        for (char ch : key)
            hashVal = 37 * hashVal + ch;

        return hashVal;
    }
};



/*------------HASH TABLE--------------------*/


template <typename HashedObject>
class HashTable
{
private:
    int m_tableSize;
    std::vector < std::list<HashedObject>> m_lists;

public:
    HashTable(int size=101): m_tableSize{size} 
    {
        m_lists.resize(m_tableSize);
    }

    size_t myHash(const HashedObject& obj)
    {
        static Hash<HashedObject> temp;
        return temp(obj) % m_lists.size();
    }

    bool insert(const HashedObject& obj)
    {
        auto findList = m_lists[myHash(obj)];

        //if obj is present in the list, skip the insertion
        if (std::find(findList.begin(), findList.end(), obj) != findList.end())
            return false;

        findList.push_back(obj);
        
        return true;

    }
      

};




int main()
{
    return 0;
}

