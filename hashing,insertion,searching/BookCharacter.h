#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

#ifndef BOOK_H
#define BOOK_H

#define CONTENTSIZE 131071
using namespace std;

class BookCharacter{
	private:
	    struct FileContent{
	    	string page_no;
	    	string line_no;
	    	string index;
	    	string character;
		}content[CONTENTSIZE];
	public:
		unsigned long hashKey(string,string,string);
		void readFile(const char *filename);
		friend class Dictionary;
		friend class List;
};
#endif
