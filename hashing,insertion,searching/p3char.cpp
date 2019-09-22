#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "BookCharacter.h"

using namespace std;

void BookCharacter::readFile(const char *filename){
	ifstream file;
	string temp;
	string token;
	int i = 0;
	int j = 0;
	file.open(filename);
	if(!file.is_open()){
		cout << "Sorry file could not opened!" << endl;
		return;
	}
	while(getline(file,temp)){
		stringstream ss(temp);
		while(getline(ss,token,'\t')){
			if(i == 0){
				content[j].page_no = token;
			}
			else if(i == 1){
				content[j].line_no = token;
			}
			else if(i == 2){
				content[j].index = token;
			}
			else if(i == 3){
				content[j].character = token;
			}
			i++;
		}
		i = 0;
		j++;
	}
}

unsigned long BookCharacter::hashKey(string page_no,string line_no,string index){
  int key;
  key = atoi((page_no + line_no + index).c_str());
  return key;
}
