#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include <set>
#include <iomanip> // setw


#include "dictionary.h"

using namespace std;

void lower(string& s);
string stripPunct(const string& s);
void checkSpelling(ifstream& in, Dictionary& dict);



// program arguments to run, example: main.exe ../../res/wordlist.txt ../../res/test.txt
int main(int argc, char* argv[]) {
	
	// Output usage message if improper command line args were given.
	if (argc != 3)
    {
		cerr << "Usage: " << argv[0] << " wordlist_filename input_file\n";
		return EXIT_FAILURE;
	}

	ifstream inf(argv[2]);
	if (! inf) 
    {
		cerr << "Could not open " << argv[2] << "\n";
		return EXIT_FAILURE;
	}
	
	// Read dictionary, but let user know what we are working on.
	cout << "Loading dictionary, this may take awhile...\n";

	Dictionary d(argv[1]);
    
	checkSpelling(inf, d);

	inf.close();

	return EXIT_SUCCESS;
}

void checkSpelling(ifstream& in, Dictionary& dict) {

	int line_number = 0;

	while (in) 
    {
		line_number++;
		set<string> totest;
		string line;
		getline(in, line);

  	    stringstream ss (stringstream::in | stringstream::out);
		ss << line;
		
		string word;
		string working_word;
		char c;
		while (ss >> word) 
        {
            if(!dict.search(word))
			{
            	std::cout << "The word '" + word + "' may be misspelled\n";
            	std::cout << "Possible corrections:\n";
            	for(int i = 0; i < word.length() - 1; i++)
				{
            		working_word = word;
            		c = working_word[i];
            		working_word[i] = working_word[i + 1];
            		working_word[i + 1] = c;
            		if(dict.search(working_word))
            			std::cout << working_word + "\n";
				}
				for(int i = 0; i < word.length(); i++)
				{
					working_word = word;
					working_word.erase(i,1);
					if(dict.search(working_word))
						std::cout << working_word + "\n";
				}
				for(int i = 0; i < word.length(); i++)
				{
					for(char ch = 'a'; ch <= 'z'; ch++)
					{
						working_word = word;
						working_word[i] = ch;
						if (dict.search(working_word))
							std::cout << working_word + "\n";
					}
				}
				for(int i = 0; i < word.length(); i++)
				{
					for(char ch = 'a'; ch <= 'z'; ch++)
					{
						working_word = word;
						working_word.insert(i, string(1, ch));
						if (dict.search(working_word))
							std::cout << working_word + "\n";
					}
				}
			}
		}
	}
}

void lower(string& s) {

    // Ensures that a word is lowercase
	for (int i = 0; i < s.length(); i++)
    {
		s[i] = tolower(s[i]);
	}
}

string stripPunct(const string& s) {

	// Remove any single trailing
	// punctuation character from a word.  
	if (ispunct(s[s.length() - 1]) ) 
    {
		return s.substr (0, s.length() - 1);
	}
	else 
    {
		return s;
	}
}
