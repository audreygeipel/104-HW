
/*
Go through line by line and add color if it hasn't been used. check around it and make sure it hasn't been used

STL Map
iterator to go through map
iter->first = key
iter.second = value

map<A, 1>

backtracj if you find out they meet

recursively look at each line

call recursive function on each character*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cstring>


bool contains(std::vector<std::pair<char, int> > countrymap, char array){

	for(unsigned int k = 0; k<countrymap.size(); k++){
		if(countrymap[k].first == array){
			return true;
		}
	}

	return false;
}

int find(std::vector<std::pair<char, int> > countrymap, char array){

int i = 0;

for(unsigned int k = 0; k<countrymap.size(); k++){
		if(countrymap[k].first == array){
			i = k;
			return i;
		}
	}

	return i;
}

std::vector<char> findNeighbors(char** array, bool** visited, std::vector<char> &neigh, int r, int c, int i, int j, char letter){

		if( i < 0 || i >= r || j < 0 || j >= c){
				return neigh;
			}
		
		if(array[i][j] != letter){
			for(unsigned int k = 0; k<neigh.size();k++){
				if (array[i][j] == neigh[k]){
					return neigh;
				}
			}
			neigh.push_back(array[i][j]);
			return neigh;
			}
		
		else if(visited[i][j] == true){
				return neigh;
			}
			
		else if(array[i][j] == letter){
				visited[i][j] = true;
				findNeighbors(array, visited, neigh, r, c, i+1, j, letter);
				findNeighbors(array, visited, neigh, r, c, i-1, j, letter);
				findNeighbors(array, visited, neigh, r, c, i, j+1, letter);
				findNeighbors(array, visited, neigh, r, c, i, j-1, letter);
				return neigh;
			}

return neigh;

}

bool areNeighbors(char letter, char check, std::vector<std::pair<char, std::vector<char>>> adjacency){

//find the index the letter you are on is at
int current = 0;

for(unsigned int k = 0; k < adjacency.size(); k++){
	if(adjacency[k].first == letter){
		current = k;
	}
}

//go through that index's neighbors
for(unsigned int i = 0; i<adjacency[current].second.size(); i++){
	if(adjacency[current].second[i] == check){
		return true;
		}
	}

	return false;
}

std::vector<std::pair<char, int>> alphabetize(std::vector<std::pair<char, int>> countrymap){
	
//I'm sorry, this is due in 5 hours and I can't figure out how to do it more elegantly
char compare[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

std::vector<std::pair<char, int>> alphabet;


for(unsigned int j = 0; j<countrymap.size(); j++){

	for(unsigned int i = 0; i<countrymap.size(); i++){

		if(countrymap[i].first == compare[j]){
			alphabet.push_back(countrymap[i]);
				}
			}
		}


return alphabet;

}
int getColor(std::vector<std::pair<char, int>> countrymap, char letter){

for(unsigned int i = 0; i<countrymap.size(); i++){
	if(countrymap[i].first == letter){
		return countrymap[i].second;
	}
}
return 0;
}

bool checkSolution(std::vector<std::pair<char, int>> countrymap, std::vector<std::pair<char, std::vector<char>>> adjacency){

for(unsigned int i = 0; i< countrymap.size(); i++){
	for(unsigned int j = 0; j<adjacency[i].second.size(); j++){
		if(getColor(countrymap, countrymap[i].first) == getColor(countrymap, adjacency[i].second[j])){
			return false;
		}

	}
}

	return true;
}





int main(int argc, char *argv[])
{

if(argc <2){
		std::cout << "put filename in command line" << std::endl;
	}

char* filename;
std::ifstream myfile;
filename = argv[1];
myfile.open(filename);

int countries;
int rows;
int columns;

myfile >> countries;
myfile >> rows;
myfile >> columns;


std::string line;
getline(myfile, line);

std::vector<std::pair<char, int>> countrymap;
std::vector<std::pair<char, std::vector<char>>> adjacency;


char** array = new char*[rows];
	for(int i = 0; i < rows; ++i){
	    array[i] = new char[columns];
	}
for(int i = 0; i <rows; i ++){
	getline(myfile, line);
	for(int j = 0; j <columns; j++){
		array[i][j] = line[j];
	}//end of j for

}//end of i for


//create grid of bools
bool** visited = new bool*[rows];
	for(int i = 0; i < rows; ++i){
	    visited[i] = new bool[columns];
	}
for(int i = 0; i <rows; i ++){
	for(int j = 0; j <columns; j++){
		visited[i][j] = false;
	}//end of j for

}//end of i for


std::vector<char> neigh;

//go through the grid and create and adjacency list of neighbors for each country
for(int i = 0; i <rows; i++){
	for(int j = 0; j <columns; j++){
			
			if(visited[i][j] == false){
				char name = array[i][j];
				std::pair<char, std::vector<char>> newcountry;
				newcountry.first = name;

				neigh = findNeighbors(array, visited, neigh, rows, columns, i, j, array[i][j]);
				newcountry.second = neigh;

				adjacency.push_back(newcountry);
				neigh.clear();
			}//end of if
		}//end of j
	}//end of i

//Assign every country color 1
for(unsigned int i = 0; i<adjacency.size(); i++){

	std::pair<char, int> newcolor;
	newcolor.first = adjacency[i].first;
	newcolor.second = 1;

	countrymap.push_back(newcolor);
}


//while there are unchecked configurations
while(checkSolution(countrymap, adjacency) == false){
//go through and check neighbors
//if there are neighbors with the same color, change it
for(unsigned int k = 0; k < countrymap.size(); k++){
for(unsigned int n = 0; n < countrymap.size(); n++){

	if(areNeighbors(countrymap[k].first, countrymap[n].first, adjacency) == true){
		if(countrymap[k].second == countrymap[n].second){
			countrymap[n].second++;
			if(countrymap[n].second >4){
			countrymap[n].second = 1;
			}
		}//end of if
	}//end of second if
}//end of n for

}//end of k for
std::cout << "whie" << std::endl;
}//end of while

std::vector<std::pair<char, int>> answer = alphabetize(countrymap);
/*
const char a = 'A';
const char b = 'B';
if(strcmp(a,b) < 0 ) {
	std::cout << "this works" << std::endl;
}
*/

for(unsigned int i = 0; i< countrymap.size();i++){
	std::cout << answer[i].first << " " << answer[i].second << std::endl;
}


for(int j = 0; j <rows; j++){
		delete[] array[j];
	}//end of j for
delete[] array;

	for(int j = 0; j <rows; j++){
		delete[] visited[j];
	}//end of j for
delete[] visited;



	return 0;


}



/*
use of vector of pairs?

input: number of countries, rows, columns

for loop goes through rows and columns

looks at first and all contiguous elements. If they are the same, adds to the count. 

increment value in map
*/