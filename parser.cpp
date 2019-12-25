#include <fstream>
#include <istream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "stackint.h"

using namespace std;

int get_number(StackInt &stk, string line, unsigned int &i){
	stringstream a(line.substr(i));
    	int number;
		a >> number;
    
    //this while loop advances i the number of digits that the number is
    	int decimal = number;
    	while((decimal/10) != 0){
    		i++;
    		decimal = decimal/10;
    		}
//this while loop makes sure that the shifts get precedence 
   	//and immediately perform their function on the number
    	if(stk.empty() == false){
    		while(stk.top() == -5 || stk.top() == -6){
			if(stk.top() == -5){
				number = number*2;
				stk.pop();
				}
			else if(stk.top() == -6){
				number = number/2;
				stk.pop();
    			}
    			else{
    				break;
    			}
    			break;
    		}
    	}

    return number;
}

void math_paren(StackInt &stk, int answer, bool &malformed){
	int pluscount = 0;
	int multcount = 0;

		while(stk.top() != -1){
			if(stk.top() == -5){
				stk.pop();
				answer = answer*2;
				//stk.pop();
			    }
			else if(stk.top() == -6){
				stk.pop();
				answer = answer/2;
				//stk.pop();
    			}
    		else if(stk.top() == -3){
				stk.pop();
			//make sure that stk.top is actually a number
				if(stk.top() >=0){
					answer = answer + stk.top();
					stk.pop();
					pluscount++;
				}
				else if(stk.top() < 0){
					malformed = true;
					break;
				}
			    	}
			else if(stk.top() == -4){
				stk.pop();
			//make sure that stk.top is actually a number
				if(stk.top() >= 0){
					answer = answer*stk.top();
					stk.pop();
					multcount++;
				}
				else if(stk.top() < 0){
					malformed = true;
					break;
				}
			  }
			else{
				answer = stk.top();			
    			stk.pop();
				}//end of last else
			}//end of while

		stk.pop(); //pop the open paren

//make sure it is not malformed
		if(pluscount > 0 && multcount > 0){
			malformed = true;
		}
		if(multcount == 0 && pluscount == 0){
			malformed = true;
		}
		stk.push(answer);
	}


int main(int argc, char *argv[])
{
const int OPEN_PAREN = -1;
const int CLOSE_PAREN = -2;
const int PLUS = -3;
const int MULTIPLY = -4;
const int SHIFTLEFT = -5; // < double the integer immediately following
const int SHIFTRIGHT = -6; // > divide the intger in two, rounding down

if(argc <2){
		cout << "put filename in command line" << endl;
	}

char* filename;
ifstream myfile;
filename = argv[1];

myfile.open(filename);

string line;
while(getline(myfile, line)){


StackInt stk;
int answer = 0;
bool malformed = false;
bool empty = false;
int parencount = 0;

if(line.empty()){
	malformed = true;
	empty = true;
	//this doesn't make it malformed, 
	//but it makes sure that a 0 doesn't get printed for empty lines
}

//for loop goes through the line and adds to the stack
for(unsigned int i = 0; i< line.size(); i++){
	if(line[i] == '('){
    	stk.push(OPEN_PAREN);
    	parencount++;
    	if(i>0 && line[i-1] >=48 && line[i-1]<=57){
			malformed = true;
    		break;
    		}
    	}
	else if(line[i] == ')'){
		parencount = parencount - 1;
		//makes sure that this is not the second function in the line
		if(line[i+1] == '('){
			malformed = true;
    		break;
			}
		if(line[i+1] >=48 && line[i+1]<=57 ){
			malformed = true;
    		break;
		}
		else{
			math_paren(stk, answer, malformed);
			}
    	}
    else if(line[i] == '+'){
    		stk.push(PLUS);
    	if(line[i+1] == ')'){
    		malformed = true;
    		break;
    	}
    	if(line[i-1] == '('){
    		malformed = true;
    		break;
    	}
    	}
	else if(line[i] == '*'){
    	stk.push(MULTIPLY);
    	if(line[i+1] == ')'){
    		malformed = true;
    		break;
    	}
    	if(line[i-1] == '('){
    		malformed = true;
    		break;
    	}
    	}

    else if(line[i] == '<'){
        stk.push(SHIFTLEFT);
    	}
	else if(line[i] == '>'){
        stk.push(SHIFTRIGHT);
    	}
  	else if(line[i]>=48 && line[i]<=57){
    	int number = get_number(stk, line, i);
	
    	stk.push(number);

    	}
    else if(line[i] == ' '){	}
    else if(line[i] == '	'){    	}
    else{
		malformed = true;
		break; 
		}
   }//end of for loop

//goes through what is in the stack not in parentheses
while(stk.empty() == false){

if(stk.top() == PLUS){
	malformed = true;
	break;
	}
else if(stk.top() == MULTIPLY){
	malformed = true;
	break;
	}
else if(stk.top() == OPEN_PAREN){
	malformed = true;
	break;	
	}
else if(stk.top() == CLOSE_PAREN){
	malformed = true;
	break;
	}
else if(stk.top() == SHIFTLEFT){
		answer = answer*2;
		stk.pop();
		}
else if(stk.top() == SHIFTRIGHT){
		answer = answer/2;
		stk.pop();
    	}
else{
	answer = stk.top();
	stk.pop();
}

} //end of while

//see if malformed
if(parencount != 0){
	malformed = true;
}

if(malformed == true && empty !=true){
	cout << "Malformed" << endl;
}
if(malformed == false){
	cout << answer << endl;
}

}//end of while getline


return 0;
}