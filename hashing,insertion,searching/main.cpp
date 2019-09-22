/*
	Name: Mahmut Gundogan
	No: 150110024

	Brief explanitation
		In main there is only insertion procedure. Because there are 
		some problems i am facing when initializing class veriable.  So
		i get segmentation fault which i could not solve. But i wrote
		lookup and writefile function. they are working individually. Only 
		dictionary lookup works slow.

*/

#include <iostream>
#include "Dictionary.h"
#include "List.h"
int main(){
	BookCharacter chr;
	Dictionary dict;
	List lst;
	clock_t begin;
	clock_t end;
	chr.readFile("ds-set-input.txt");
	cout << "DICTIONARY" << endl << endl;
	begin = clock();
	dict.insertItem(chr);
	end = clock();
	cout << "insertion finished after " << float(end-begin)/CLOCKS_PER_SEC << " seconds" << endl << endl;
	cout << "LIST" << endl;
	begin = clock();
	lst.insertList(chr);
	end = clock();
	cout << "insertion finished after " << float(end-begin)/CLOCKS_PER_SEC << " seconds" << endl << endl;
	return 0;
}
