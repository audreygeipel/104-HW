
all: search coloring

search: search.cpp
	g++ -Wall -g -std=c++11 search.cpp -o search

coloring: coloring.cpp
	g++ -Wall -g -std=c++11 coloring.cpp -o coloring