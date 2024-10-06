#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>

struct table_slot {
    // Enum for the status of the slot
    enum Status { NEVER_USED, TOMBSTONE, OCCUPIED };

    // Member variables
    Status status;
    std::string contents;

    // Constructor to initialize default values
    table_slot() : status(NEVER_USED), contents("") {}
};

class HashTable
{
private:
    std::vector<table_slot> table;

private:
    int hashFunction(const std::string& key) const;

public:
    HashTable();

    void insert(const std::string& key);
    void remove(const std::string& key);
    void print();
};

#endif // HASH_TABLE_H