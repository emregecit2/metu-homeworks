#include "HashTable.h"

#include <cassert>
#include <iostream>
#include <iomanip>

const int KeyedHashTable::PRIME_LIST[PRIME_TABLE_COUNT] =
{
     2,    3,   5,   7,  11,  13,  17,  19,
     23,  29,  31,  37,  41,  43,  47,  53,
     59,  61,  67,  71,  73,  79,  83,  89,
     97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293, 307, 311,
    313, 317, 331, 337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499, 503,
    509, 521, 523, 541
};

int KeyedHashTable::Hash(const std::string& key) const
{
    int hash = 0;
    for(int k=0; k<key.size(); k++){
        hash += key[k] * PRIME_LIST[k];
    }
    return hash%tableSize;
}

void KeyedHashTable::ReHash()
{
    std::vector<HashData> temp(occupiedElementCount);
    for(int i=0, j=0; i<tableSize; i++){
        if(table[i].intArray.size() || table[i].key.size()){
            temp[j++] = table[i];
        }
    }
    delete[] table;
    tableSize = FindNearestLargerPrime(2*tableSize);
    table = new HashData[tableSize];
    occupiedElementCount = 0;
    for(int i=0; i<temp.size(); i++){
        Insert(temp[i].key, temp[i].intArray);
    }
}

int KeyedHashTable::FindNearestLargerPrime(int requestedCapacity)
{
    int i=-1;
    while(PRIME_LIST[++i]<=requestedCapacity);
    return PRIME_LIST[i];
}

KeyedHashTable::KeyedHashTable()
{
    occupiedElementCount = 0;
    tableSize = 2;
    table = new HashData[2];
}

KeyedHashTable::KeyedHashTable(int requestedCapacity)
{
    occupiedElementCount = 0;
    tableSize = FindNearestLargerPrime(requestedCapacity);
    table = new HashData[tableSize];
}

KeyedHashTable::KeyedHashTable(const KeyedHashTable& other)
{
    occupiedElementCount = other.occupiedElementCount;
    tableSize = other.tableSize;
    table = new HashData[tableSize];
    for(int i=0; i<tableSize; i++){
        table[i] = other.table[i];
    }
}

KeyedHashTable& KeyedHashTable::operator=(const KeyedHashTable& other)
{
    occupiedElementCount = other.occupiedElementCount;
    tableSize = other.tableSize;
    delete[] table;
    table = new HashData[tableSize];
    for(int i=0; i<tableSize; i++){
        table[i] = other.table[i];
    }
    return *this;
}

KeyedHashTable::~KeyedHashTable()
{
    delete[] table;
}

bool KeyedHashTable::Insert(const std::string& key,
                            const std::vector<int>& intArray)
{
    for(int i=0, hash=Hash(key); ;i++){
        int index = (hash+i*i)%tableSize;
        if(empty(index)){
            table[index].key = key;
            table[index].intArray = intArray;
            if(++occupiedElementCount * EXPAND_THRESHOLD >= tableSize){
                ReHash();
            }
            return true;
        }
        if(table[index].key==key){
            return false;
        }
    }
}

bool KeyedHashTable::Remove(const std::string& key)
{
    int i=0, hash=Hash(key), index;
    do{
        index = (hash+i*i)%tableSize;
        i++;
    }while(table[index].key!=key);
    table[index] = HashData();
    table[index].key = "__DELETED__";
}

void KeyedHashTable::ClearTable()
{
    for(int i=0; i<tableSize; i++){
        table[i] = HashData();
    }
    occupiedElementCount = 0;
}

bool KeyedHashTable::Find(std::vector<int>& valueOut,
                          const std::string& key) const
{
    for(int i=0, hash=Hash(key); ;i++){
        int index = (hash+i*i)%tableSize;
        if(empty(index)){
            return false;
        }
        if(table[index].key==key){
            valueOut = table[index].intArray;
            return true;
        }
    }
}

void KeyedHashTable::Print() const
{
    // ============================= //
    // This function is implemented  //
    // Do not edit this function !   //
    // ============================= //
    std::cout << "HT:";
    if(occupiedElementCount == 0)
    {
        std::cout << " Empty";
    }
    std::cout << "\n";
    for(int i = 0; i < tableSize; i++)
    {
        if(table[i].key == "") continue;

        std::cout << "[" << std::setw(3) << i << "] ";
        std::cout << "[" << table[i].key << "] ";
        std::cout << "[";
        for(size_t j = 0; j < table[i].intArray.size(); j++)
        {
            std::cout << table[i].intArray[j];
            if((j + 1) != table[i].intArray.size())
                std::cout << ", ";
        }
        std::cout << "]\n";
    }
    std::cout.flush();
}

bool KeyedHashTable::empty(int index) const
{
    return table[index].intArray.empty() && table[index].key.empty();
}
