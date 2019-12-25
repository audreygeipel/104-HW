#include <string>
#include <sstream>
#include <iostream>
#include <vector>

int main(){


std::cout << "Please provide input using only e,w,n, or s with no spaces:" << std::endl;

std::string line;

getline(std::cin, line);

for(unsigned int j = 0; j<line.size(); j++){
	if (line[j] != 'n' && line[j] != 's' && line[j] != 'e' && line[j] != 'w'){
		std::cout << "invalid" << std::endl;
		return 0;
	}
	else if(line[j] == ' '){
		std::cout << "invalid" << std::endl;
		return 0;
	}
}

std::vector<char> stack;
stack.push_back(line[0]);

for(unsigned int i = 1; i<line.size(); i++){
	if(line[i] == 'n' && stack.back() == 's'){
		stack.pop_back();
	}
	else if(line[i] == 's' && stack.back() == 'n'){
		stack.pop_back();
	}
	else if(line[i] == 'e' && stack.back() == 'w'){
		stack.pop_back();
	}
	else if(line[i] == 'w' && stack.back() == 'e'){
		stack.pop_back();
	}
	else{
		stack.push_back(line[i]);
	}
}

if(stack.empty() == true){
	std::cout << "Rolled up" << std::endl;
}
else{
	std::cout << "Not rolled up" << std::endl;
}


	return 0;
}

