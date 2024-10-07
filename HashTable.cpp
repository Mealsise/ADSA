#include "HashTable.h"
#include <iostream>

int HashTable::hashFunction(const std::string& key) const
{
    return (key.end())[-1] - 'a';
}

HashTable::HashTable()
{
    for (int i = 0; i < 26; ++i) {
      table.push_back(table_slot());
    }
}


void HashTable::insert(const std::string& key)
{
    int index = hashFunction(key);
    while (table[index].status == table_slot::OCCUPIED)
    {
        index = index == 25 ? 0 : index + 1;
    }
    table[index].status = table_slot::OCCUPIED;
    table[index].contents = key;
}

void HashTable::remove(const std::string& key)
{
    int index = hashFunction(key);
    if (table[index].status == table_slot::OCCUPIED && table[index].contents == key)
    {
      table[index].status = table_slot::TOMBSTONE;
    }
}

void HashTable::print()
{
    for (int index = 0; index < 26; index++)
    {
        if (table[index].status == table_slot::OCCUPIED)
        {
            std::cout << table[index].contents << " ";
        }
    }
    std::cout << std::endl;
}
