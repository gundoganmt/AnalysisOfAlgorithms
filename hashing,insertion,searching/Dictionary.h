#include <iostream>
#include "BookCharacter.h"

class Dictionary{
  private:
    static const int tableSize = 131071;
    typedef struct dct{
      unsigned long key;
      std::string value;
    }*hashptr;
    hashptr hash_table[tableSize];
  public:
    Dictionary();
    void writefile(BookCharacter,string);
    void lookup(BookCharacter);
    void insertItem(BookCharacter);
};
