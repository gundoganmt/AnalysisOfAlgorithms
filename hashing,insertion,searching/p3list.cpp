#include <iostream>
#include <string>
#include "List.h"

using namespace std;

List::List(){
  head = NULL;
}

void List::insertList(BookCharacter chr){
  for(int i = 0; i < 131071; i++){
    listptr newnode = new list;
    newnode->key = chr.hashKey(chr.content[i].page_no,chr.content[i].line_no,chr.content[i].index);
    newnode->value = chr.content[i].character;
    newnode->next = head;
    head = newnode;
  }
}

void List::writefile(BookCharacter chr, string value){
  ofstream output;
  output.open("ds-set-output-list.txt");
  if(!output.is_open()){
    cout << "output file is not created" << endl;
    return;
  }
  for(int i = 0; i < 131071; i++){
    output << chr.content[i].page_no << "\t" << chr.content[i].line_no << "\t" << chr.content[i].index << "\t" << value << endl;
  }
}

void List::lookup(BookCharacter chr){
  unsigned long key;
  listptr traverse = head;
  for(int i = 0; i < 131071; i++){
    key = chr.hashKey(chr.content[i].page_no,chr.content[i].line_no,chr.content[i].index);
    while(traverse->key != key){
      traverse = traverse->next;
    }
    writefile(chr,traverse->value);
    traverse = head;
  }
}

void List::print(){
  listptr traverse = head;
  while(traverse != NULL){
    traverse = traverse->next;
  }
}
