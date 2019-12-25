#include "stackint.h"


	StackInt::StackInt(){}

	StackInt::~StackInt(){}


	bool StackInt::empty() const{
		if(list.empty() == true){
			return true;
		}
		return false;
	}

	void StackInt::push(const int& val){
		list.push_back(val);
	}

	int StackInt::top() const{
		int top = list.size();
		int topval = list.get(top-1);

		return topval;
	}

	void StackInt::pop(){
		size_t top = list.size();
		list.remove(top-1);

	}
