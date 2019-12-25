#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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


int detect(char** array, bool** visited, int r, int c, int i, int j, char letter){

		if( i < 0 || i >= r || j < 0 || j >= c){
				return 0;
			}
		
		if(array[i][j] != letter){
				return 0;
			}
		
		else if(visited[i][j] == true){
				return 0;
			}
			
		else if(array[i][j] == letter){
				visited[i][j] = true;
				return (1 + detect(array, visited, r, c, i+1, j, array[i][j]) + detect(array, visited, r, c, i-1, j, array[i][j]) + detect(array, visited, r, c, i ,j+1, array[i][j]) +detect(array, visited, r, c, i, j-1, array[i][j]));
			}

return 0;

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

std::vector < std::pair <char, int> > countrymap;

//read in map to array
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


//set up a grid of bools saying whether a node has been visited or not
bool** visited = new bool*[rows];
	for(int i = 0; i < rows; ++i){
	    visited[i] = new bool[columns];
	}
for(int i = 0; i <rows; i ++){
	for(int j = 0; j <columns; j++){
		visited[i][j] = false;
	}//end of j for
}//end of i for


//go through the map, adding a new country when you hit a new letter, and using the detect function to find the size.
for(int i = 0; i <rows; i++){
	for(int j = 0; j <columns; j++){
			
			if(visited[i][j] == false){
				char name = array[i][j];
				std::pair <char,int> newcountry;
				newcountry.first = name;

				int size = detect(array, visited, rows, columns, i, j, array[i][j]);
				newcountry.second = size;

				countrymap.push_back(newcountry);

			}//end of if
		}//end of j
	}//end of i

			
//find the largest country
int largest = 0;
int place = 0;

for(unsigned int i = 0; i< countrymap.size();i++){
	if(countrymap[i].second > largest){
		largest = countrymap[i].second;
		place = i;
	}
}

//print out
std::cout << countrymap[place].second << std::endl;



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
steps:
1 input: number of countries, rows, columns
2. use of vector of pairs
3. for loops go through rows and columns
4. when you find a new country (new letter, unvisited), use detect function to find the size
5. put that country and size in the vector of pairs
6. see which one is largest
*/