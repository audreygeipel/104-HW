
all: cave

cave: cave.cpp
	g++ -Wall -g -std=c++11 cave.cpp -o cave
