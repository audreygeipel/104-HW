#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]){

char* filename;

filename = argv[1];

//open the file
ifstream myfile(filename);
cout << filename << endl;
   
   if(myfile.fail()){
        cout << "oh no it didn't open" << endl;
        return 0;
   }

//create the string stream
   string str;
   getline(myfile, str);
   stringstream a(str);
   if(a.fail()){
    cout<< "ya failed" << endl;
    return 0;
   }

//read in the number of words
   int n;
   a >> n;
   if(a.fail()){
    cout << "once again, failure" << endl;
    return 0;
   }
   //cout << n << endl;

 //create the words string and vector to hold all the strings 
  string words = "";
  vector<string> w;

//go through the file, get n words, and add them to the stringstream
for(int i = 0; i<n; i++){
  
  getline(myfile, str);
  stringstream b(str);

//while there are still words to read in, add them to the vector
 while(b >> words){
        w.push_back(words);
  
    if(b.fail()){
      cout << "failed to read words" << endl;
      return 0;
      }
    }//end of while loop
  }//end of i loopS

//when you have all the words, cout them in reverse order
for(int i = n-1; i>=0; i--){
if (!w.empty()){
    cout << w[i] << endl;
}
}

 }