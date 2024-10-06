// #include <iostream>
#include "HashTable.h"
// #include <>
// #include <>
// #include <>
// #include <>


int main(int argc, char* argv[])
{
    HashTable hashtable;

    for (int i = 1; i < argc; i++)
    {
        std::string command = argv[i];
        if (command[0] == 'A')
        {
            hashtable.insert(command.substr(1));
        }
        else if (command[0] == 'D')
        {
            hashtable.remove(command.substr(1));
        }
    }

    hashtable.print();

    return 0;
}