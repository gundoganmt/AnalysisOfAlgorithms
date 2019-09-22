#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary(){
  for(int i = 0; i < tableSize; i++){
    hash_table[i] = new dct;
    hash_table[i]->key = 0;
    hash_table[i]->value = "";
  }
}
void Dictionary::insertItem(BookCharacter chr){
  int j = 1;
  float A = (sqrt(5)-1)/2;
  unsigned long key;
  int index;
  int collision = 0;
  for(int i = 0; i < tableSize; i++){
    key = chr.hashKey(chr.content[i].page_no,chr.content[i].line_no,chr.content[i].index);
    index = floor( tableSize * ( fmod((double)key*A,1) ));
    if(index < 0)
      index*=-1;
    while(hash_table[index]->key != 0){
      index = fmod(((index + 7*j + 3*j*j)),tableSize);
      if(index < 0)
        index*=-1;
      j++;
      collision++;
    }
    if(i == 1000){
      cout << " average number of collision(first 1000 item) | " << collision << endl;
    }
    else if(i == 10000){
      cout << " average number of collision(first 10000 item) | " << collision << endl;
    }
    else if(i == 100000){
      cout << " average number of collision(first 100000 item) | " << collision << endl;
    }
    else if(i == tableSize-1){
      cout << " average number of collision(overall) | " << collision << endl;
    }
    hash_table[index]->key = key;
    hash_table[index]->value = chr.content[i].character;
    j = 1;
  }
}

void Dictionary::writefile(BookCharacter chr, string value){
  ofstream output;
  output.open("ds-set-output-dict.txt");
  if(!output.is_open()){
    cout << "output file is not created" << endl;
    return;
  }
  for(int i = 0; i < tableSize; i++){
    output << chr.content[i].page_no << "\t" << chr.content[i].line_no << "\t" << chr.content[i].index << "\t" << value << endl;
  }
}

void Dictionary::lookup(BookCharacter chr){
  unsigned long key;
  int j = 0;
  float A = (sqrt(5)-1)/2;
  int index;
  for(int i = 0; i < tableSize; i++){
    key = chr.hashKey(chr.content[i].page_no,chr.content[i].line_no,chr.content[i].index);
    index = floor( tableSize * ( fmod((double)key*A,1) ));
    if(index < 0)
      index*=-1;
    while(hash_table[index]->key != key){
      index = fmod(((index + 7*j + 3*j*j)),tableSize);
      if(index < 0)
        index*=-1;
      j++;
    }

    //writefile(chr,hash_table[index]->value);
  }
}
