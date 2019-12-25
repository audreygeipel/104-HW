/*
 * Board.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */
#include "Board.h"
#include "ConsolePrinter.h"
#include <string>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

	Board::Board (std::string board_file_name){
		
		std::stringstream ss;

		std::ifstream myfile;

		myfile.open(board_file_name);

		myfile >> x;
		myfile >> y;
		myfile >> sx;
		myfile >> sy;
			

board = new Square**[x];


for (size_t i = 0; i<x; i++){
	board[i] = new Square*[y];
}
string extra;
getline(myfile,extra);

//build the board by reading in a line at a time
for(size_t i = 0; i<x;i++){
		std::string line;
		getline(myfile, line);
for(size_t j = 0; j<y;j++){
		if((i+1) == sx && (j+1) == sy){
			if(line[j] == '.'){
			board[j][i] = new Square(1,1,true);
			}
			else if(line[j] == '2'){
				board[j][i] = new Square(2,1,true);
			}
			else if(line[j] == '3'){
				board[j][i] = new Square(3,1,true);
			}
			else if(line[j] == 'd'){
				board[j][i] = new Square(1,2,true);
			}
			else if(line[j] == 't'){
				board[j][i] = new Square(1,3,true);
			}
		}
		else if(line[j] == '.'){
			board[j][i] = new Square(1,1,false);
		}
		else if(line[j] == '2'){
			board[j][i] = new Square(2,1,false);
		}
		else if(line[j] == '3'){
			board[j][i] = new Square(3,1,false);
		}
		else if(line[j] == 'd'){
			board[j][i] = new Square(1,2,false);
		}
		else if(line[j] == 't'){
			board[j][i] = new Square(1,3,false);
		}

	}
}

	}

	Board::~Board (){
for(size_t i = 0; i<x; i++){
		delete[] board[i];
	}
delete[] board;

	}

	size_t Board::getSX(){
		return sx;
	}
	size_t Board::getSY(){
		return sy;
	}

	/* returns a vector of all words that would be formed by executing the
           given move. The first element of the pair is a string containing the word
           formed, and the second element is the score that that word earns
           (with all multipliers, but not the 50-point bonus for all letters).

       Words returned are all in uppercase.

	   The last entry of the vector is always the "main" word formed
	   in the direction chosen by the user; the others could be in arbitrary
	   order. (This is helpful for backtracking search.)

	   This function does not check that the words formed are actually in the dictionary.
	   The words returned from this function must be checked against the dictionary to
	   determine if the move is legal.	*/
/*	std::vector<std::pair<std::string, unsigned int>> Board::getPlaceMoveResults(const PlaceMove &m) const{

	}
*/
	/* Executes the given move by taking tiles and placing them on the board.
	   This function does not check for correctness of the move, so could
	   segfault or cause other errors if called for an incorrect move.
	   When a blank tile '?' is placed on the board, it is treated as a letter,
	   i.e., the corresponding square has that letter (with score 0) placed on it.
	*/
	//void Board::executePlaceMove (const PlaceMove & m){
		/*if (m.horizontal == true){
			for(int i = 0; i < m.word.size(); i++){
				//board[m.r+i][]
				//tileString[i]; 

			}
		}
		else if(m.horizontal == false){
			for(int i = 0; i < m.word.size(); i++){
				//board[m.c+i]
				//tileString[i]; 
			}

		}*/
	//}

	/* Returns a pointer to the Square object representing the
       (y,x) position of the board. Indexing starts at 1 here.
	   This is needed only to display the board. */
	Square * Board::getSquare (size_t x, size_t y) const{
		return board[x-1][y-1];
	}

	/* Returns the number of rows of the board.*/
	size_t Board::getRows() const{
		return x;
	}

	/* Returns the number of columns of the board.*/
	size_t Board::getColumns() const{
		return y;
	}
