#include <iostream>
#include "BookCharacter.h"

class List{
  private:
    typedef struct list{
      unsigned long key;
      std::string value;
      list *next;
    }*listptr;
    listptr head;
  public:
    List();
    void writefile(BookCharacter,string);
    void lookup(BookCharacter);
    void insertList(BookCharacter);
    void print();
};
