#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "MinHeap.h"

using namespace std;


int main()
{

//int d = 3;
MinHeap m(3);
m.add(1,1);
std::cout << m.peek();
m.remove();


for(int i = 0; i<m.size(); i++){
	std::cout << m[i] << std::endl;
}

	return 0;
}