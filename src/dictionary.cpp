#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"


Dictionary::Dictionary(string filename)
{
	string s;
	ifstream file(filename);
	if(file)
		while (getline(file, s))
			insert(s);
	else
		throw std::invalid_argument("Something went wrong(((");
	file.close();
}
