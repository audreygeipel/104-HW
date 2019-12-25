#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Dictionary.h"


	/* The constructor gets passed the name of the file from which
	   to read the word list. */
	Dictionary::Dictionary (std::string dictionary_file_name){

		std::stringstream ss;

		std::ifstream myfile;

		myfile.open(dictionary_file_name);


		std::string line;
		std::string word;

		while(getline(myfile,line)){
			myfile >> word;
			wordlist.push_back(word);
		}
		
	}

	Dictionary::~Dictionary (){
		//for(unsigned int i = 0; i<wordlist.size(); i++){
			//delete[] wordlist;
		//}
	}

	/* Checks whether the given word is in the dictionary, and returns true if so.
	   Case should not matter. Must run in O(logn) for the number of words in the dictionary. */
	bool Dictionary::isLegalWord (std::string const & word) const{

		for(unsigned int i = 0; i <wordlist.size(); i++){
			if(wordlist[i] == word){
				return true;
			}
		}
		return false;
	}


