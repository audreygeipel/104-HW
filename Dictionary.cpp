//
// Dictionary class implementation from Jamie's solution
//

#include <string>
#include <fstream>
#include <iostream>

#include "Dictionary.h"
#include "Exceptions.h"
#include "Util.h"

Dictionary::Dictionary(std::string dictionary_file_name):
words()
{
	std::ifstream dictFileStream(dictionary_file_name);

	if(!dictFileStream)
	{
		throw FileException("DICTIONARY");
	}

	while(!dictFileStream.eof())
	{
		std::string word;
		dictFileStream >> word;

		if (dictFileStream.eof() && word.empty())
		{
			break;
		}

		makeLowercase(word);
		words.insert(word);
		//std::cout << word << std::endl;
		//TrieNode* test = words.prefix(word);
		//std::cout << test->inSet << std::endl;
	}

}

Dictionary::~Dictionary()
{
	// default destructor is OK
}

bool Dictionary::isLegalWord(std::string const &word)
{
	
	std::string lowercaseWord(word);
	makeLowercase(lowercaseWord);

	TrieNode* check = words.prefix(lowercaseWord);

if(check == nullptr){

	return false;
}

	return check->inSet;

//	return words.find(lowercaseWord) != words.end();
}

TrieSet Dictionary::getTrie(){
	return words;
}