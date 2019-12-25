/**
 * Incorrect code to identify palindromes
 */

#include <iostream>
#include <sstream>
#include <cstring> 

using namespace std;

bool helper (stringstream &input, int len)
{
	char prev;

	//if we are at the midpoint of the string, return true.
	if (len == 0) return true;

	/**
	 * If the length of the string is odd, and the next
	 * character is the midpoint of the string, consume it
	 * and return true.
	 */
	input >> prev;
	if (len == 1) return true;

	bool val = helper(input, len-2);

	//make your changes only below this line.
	//as it goes back up throguh the recursion, the prev will equal the character it
	//is checking against, so you have to take the next character in and see if it
	//matches the previous character
	char next;
	input >> next;

	//if the next character you're pulling in doesn't match the 
	//one pulled in ont he other side, then it is not a palindrome
	if (next != prev) return false;
	

	if (val == true) return true;
	
	return false;
}

//do not change the main function.
int main (int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a string of characters." << endl;
    return 1;
  }
  stringstream ss;
  ss << argv[1];
  if(helper(ss, strlen(argv[1])))
	  cout << "Palindrome" << endl;
  else cout << "Not a Palindrome" << endl;
  return 0;
}