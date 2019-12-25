//
// Player class implementation from Jamie's solution
//

#include "Player.h"
#include "Exceptions.h"
#include "Util.h"
#include "Board.h"
#include "Dictionary.h"
#include "Move.h"
#include <iostream>


Player::Player(std::string const & name, size_t maxTiles, int t):
_name(name),
_maxTiles(maxTiles),
_type(t),
_points(0),
_hand()
{

}

Player::~Player()
{
	// delete any remaining tiles
	for(std::multimap<char, Tile *>::const_iterator tileIter = _hand.cbegin(); tileIter != _hand.cend(); ++tileIter)
	{
		delete tileIter->second;
	}
}

std::multimap<char, Tile *> Player::getHand(){
	return  _hand;
}

void Player::addPoints(unsigned int points)
{
	_points += points;
}

void Player::subtractPoints(unsigned int pointsToSubtract)
{
	if(pointsToSubtract > _points)
	{
		_points = 0;
	}
	else
	{
		_points -= pointsToSubtract;
	}
}

std::string Player::getName() const
{
	return _name;
}

unsigned int Player::getPoints() const
{
	return _points;
}

size_t Player::getNumTiles() const
{
	return _hand.size();
}

size_t Player::getMaxTiles() const
{
	return _maxTiles;
}

unsigned int Player::remainingPoints() const
{
	unsigned int remainingPoints = 0;

	for(std::multimap<char, Tile *>::const_iterator tileIter = _hand.cbegin(); tileIter != _hand.cend(); ++tileIter)
	{
		remainingPoints += tileIter->second->getPoints();
	}

	return remainingPoints;
}

std::set<Tile*> Player::getHandTiles() const
{
	std::set<Tile *> tileSet;

	// add elements from multimap to set
	for(std::multimap<char, Tile *>::const_iterator tileIter = _hand.cbegin(); tileIter != _hand.cend(); ++tileIter)
	{
		tileSet.insert(tileIter->second);
	}

	return tileSet;
}

bool Player::hasTiles(std::string const & move, bool resolveBlanks) const
{

	std::string uppercaseMove = move;
	makeUppercase(uppercaseMove);

	for(size_t charIndex = 0; charIndex < uppercaseMove.length(); ++charIndex)
	{
		if(uppercaseMove[charIndex] == '?' && resolveBlanks)
		{
			ConstHandSearchResult blankSearchResult = _hand.equal_range('?');

			if(blankSearchResult.first == blankSearchResult.second)
			{
				return false;
			}

			// skip next character
			++charIndex;
		}
		else
		{
			ConstHandSearchResult charSearchResult = _hand.equal_range(uppercaseMove[charIndex]);

			if(charSearchResult.first == charSearchResult.second)
			{
				return false;
			}

		}

	}

	return true;

}

std::vector<Tile *> Player::takeTiles(std::string const & move, bool resolveBlanks)
{
	// before we make any modifications, check that it is actually possible
	// to make the given move.

	std::string uppercaseMove = move;
	makeUppercase(uppercaseMove);

	if(!hasTiles(uppercaseMove, resolveBlanks))
	{
		throw MoveException("WRONGTILES");
	}

	std::vector<Tile *> tilesRequested;

	for(size_t charIndex = 0; charIndex < uppercaseMove.length(); ++charIndex)
	{
		if(uppercaseMove[charIndex] == '?' && resolveBlanks)
		{
			HandSearchResult blankSearchResult = _hand.equal_range('?');

			++charIndex;

			// remove the blank tile and assign a letter to it
			Tile * blankTile = blankSearchResult.first->second;
			_hand.erase(blankSearchResult.first);
			blankTile->useAs(uppercaseMove[charIndex]);

			tilesRequested.push_back(blankTile);

		}
		else
		{
			HandSearchResult charSearchResult = _hand.equal_range(uppercaseMove[charIndex]);

			Tile * charTile = charSearchResult.first->second;
			_hand.erase(charSearchResult.first);
			tilesRequested.push_back(charTile);
		}

	}

	return tilesRequested;

}

void Player::addTiles(std::vector<Tile *> const & tilesToAdd)
{
	if(_hand.size() + tilesToAdd.size() > _maxTiles)
	{
		throw MoveException("TILELIMIT");
	}

	for(std::vector<Tile *>::const_iterator newTileIter = tilesToAdd.begin(); newTileIter != tilesToAdd.end(); ++newTileIter)
	{
		Tile * newTile = *newTileIter;
		_hand.emplace(std::toupper(newTile->getLetter()), newTile);
	}
}

int Player::getType(){

	return _type;
}



std::vector<std::string> Player::findWords(std::multimap<char, Tile *> _hand, Board * board, Dictionary * dictionary){


	std::vector<std::string> possiblemoves;
	std::vector<char> letters;
	std::multimap<char, Tile *>::iterator it;
	std::vector<std::string> found;
 
	for(it = _hand.begin(); it != _hand.end(); it++){
		letters.push_back(it->first);
	}


	for(unsigned int x = 1; x<= board->getRows(); x++){
		for(unsigned int y = 1; y<=board->getColumns(); y++){
			Square * check = board->getSquare(x,y);
			
			if(check->isOccupied()){
				
				letters.push_back(check->getLetter());

				found = useTheTrie(letters, dictionary);

				letters.pop_back();

				for(unsigned int h = 0; h<found.size(); h++){
					possiblemoves.push_back(found[h]);
				}
			}

		}
	}
return possiblemoves;
}



std::vector<std::string> Player::useTheTrie(std::vector<char> letters, Dictionary * dictionary){


std::vector<std::string> wordsfound;

//std::cout <<"HERE" << std::endl;
	TrieSet legalwords = dictionary->getTrie();

//std::vector<char> check;

for(unsigned int k = 0; k<letters.size(); k++){
	letters[k] = tolower(letters[k]);
}
//std::cout << std::endl;

	for(unsigned int i = 0; i< letters.size(); i++){
		//set the first letter
		if(letters[i] == '?'){
			i++;
		}
		//temp = dictionary.root->children[letters[i]-97];
		TrieNode * temp = legalwords.getRoot();
		//std::cout << "root is " << legalwords.getL(legalwords.getRoot()) << std::endl;

		temp = temp->children[letters[i]-97];
		//std::cout << "first temp is: " << legalwords.getL(legalwords.getRoot()) <<std::endl;

		std::string singleword = "";
		//take out letter each time and make it recursive
		//put the first letter in a string
		singleword += letters[i];

		//std::cout << "first letter: " << singleword << std::endl;

		for(unsigned int j = 0; j<letters.size(); j++){
			if(letters[j] == '?'){
				j++;
			}
			if(temp->inSet == true){
				if(dictionary->isLegalWord(singleword) == true){
						
						if((int)singleword.find(letters[letters.size()-1]) != -1){
							wordsfound.push_back(singleword);
						}
						//std::cout << singleword << std::endl;
					}
				}

			if(temp->children[letters[j]-97] != nullptr){
				temp = temp->children[letters[j]-97];
				singleword += letters[j];
				//std::cout << letters[j];
			}
			
		}//end of j for

		//std::cout << std::endl;
	}

	return wordsfound;
}


void Player::CPUSmove(std::vector<std::string> w, Board * board, Bag * bag, Dictionary * dictionary){

	Move * playerMove = nullptr;

	if(w.empty() == true){
		// first construct the move, which could throw an exception
		std::string p = "pass";
		playerMove = Move::parseMove(p, *this);
	}
	//first construct the move, which could throw an exception
	std::string t = w[0];

	std::string x = "9";
	std::string y = "9";
	//first construct the move, which could throw an exception
	std::string m = "place | " + x + " " + y + " " + t;	playerMove = Move::parseMove(m, *this);

	// now execute it, which could also throw exceptions
	playerMove->execute(*board, *bag, *dictionary);


}

void Player::CPULmove(std::vector<std::string> w, Board * board, Bag * bag, Dictionary * dictionary){

	Move * playerMove = nullptr;

	if(w.empty() == true){
		// first construct the move, which could throw an exception
		std::string p = "pass";
		playerMove = Move::parseMove(p, *this);
	}

	std::string t = w[0];

	for(unsigned int i = 0; i<w.size(); i++){
		if(w[i].length() > t.length()){
			t = w[i];
		}
	}
	std::string x = "9";
	std::string y = "9";
	//first construct the move, which could throw an exception
	std::string m = "place | " + x + " " + y + " " + t;
	playerMove = Move::parseMove(m, *this);

	// now execute it, which could also throw exceptions
	playerMove->execute(*board, *bag, *dictionary);




}