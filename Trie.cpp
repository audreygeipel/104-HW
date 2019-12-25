#include <fstream>
#include <string>
#include <iostream>

#include "Trie.h"


  TrieSet::TrieSet (){ // a constructor for an empty trie
  	root = new TrieNode;
  	root->parent = nullptr;
  	root->inSet = false;

  	for(int i = 0; i<26; i++){
  		root->children[i] = nullptr;
  	}

  } 
  
void TrieSet::deletethatShit(TrieNode* r){
  	/*if(r == nullptr){
  		return;
  	}

  	for(int i = 0; i<26; i++){
  		if(r->children[i] != nullptr){
        deletethatShit(r->children[i]);
      }
  	}
  	delete r;*/
  }

  TrieSet::~TrieSet (){
  	deletethatShit(root);
  } // destructor

 

  void TrieSet::print(TrieNode* p){
  	while(p->parent != nullptr){
  		std::cout << p->l;
  		p = p->parent;
  	}
  	std::cout << std::endl;

  }

  char TrieSet::getL(TrieNode* n){
    return n->l;
  }

  TrieNode* TrieSet::getRoot(){
    return root;
  }


  void TrieSet::insert(std::string input){
   /* Add this string to the set.
      Do nothing if the string is already in the set. */

//return if it's not a thing
  	if(root == nullptr){
  		return;
  	}
   
   //make the input all lowercase
  	for(unsigned int i = 0; i< input.size(); i++){
  		input[i] = tolower(input[i]);
  	}

//set a temp to traverse, starting at the root 
  	TrieNode* temp = root;

//go into the trie for a depth = length of input
  	for(unsigned int j = 0; j<input.size(); j++){
  	//if there's not already a letter at the child that corresponds to the letter of input
    	if(temp->children[input[j]-97] == nullptr){
  			//create a new node and add in the letter if it's not there
        TrieNode* letter = new TrieNode;
  			letter->inSet = false;
  			letter->parent = temp;
        letter->l = input[j];
  			for(unsigned int l = 0; l<26; l++){
  				letter->children[l] = nullptr;
  				}

  			temp->children[input[j] - 97] = letter;
  			}// end of if

      //if the letter's already there, just hop down and keep going 
  			temp = temp->children[input[j]-97];
	  	}//end of for

//at the end of all this business, set inSet to true bc it's the end of the word
	  temp->inSet = true;
	//print(temp);
	//std::cout << input[input.size() -1] << temp->parent << std::endl;
  }

  void TrieSet::remove (std::string input){
	/* Removes this string from the set.
      Do nothing if the string is not already in the set. */

  	if(root == nullptr){
  		return;
  	}

  	for(unsigned int i = 0; i < input.size(); i++){
  		input[i] = tolower(input[i]);
  	}

  	TrieNode* temp = root;

  	for(unsigned int j = 0; j<input.size(); j++){

  		if(temp->children[input[j]-97] == nullptr){
  				return;
  			}
  		temp = temp->children[input[j]-97];
	  	}//end of for


	for(unsigned int x = 0; x<input.size(); x++){
		
		for(unsigned int c = 0; c<26; c++){
			if(temp->children[c] != nullptr){ //if the temp has a child, you're done. leave it 
				temp->inSet = false;       //alone and let it live out its life with its children
        return;							
			}
		}//end of alphabet for

		temp = temp->parent; //move temp up a level
		delete temp->children[input[input.size()-x ]-97]; //delete the node with the last letter

	}//end of move up for


  }

  TrieNode* TrieSet::prefix(std::string px){
 	/*returns the TrieNode matching the provided string, or returns NULL 
      if it is not the prefix of a word in the Trie. */

	if(root == nullptr){
  		return NULL;
  	}

  	for(unsigned int i = 0; i < px.size(); i++){
  		px[i] = tolower(px[i]);
  	}
  	TrieNode* temp = root;

  	for(unsigned int j = 0; j<px.size(); j++){


  		if(temp->children[px[j]-97] == nullptr){
  				return NULL;
  			}

  		temp = temp->children[px[j]-97];

	  	}//end of for

	return temp;
  }
  