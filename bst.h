#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{


	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
  		virtual void insert(const std::pair<Key, Value>& keyValuePair); //TODO
        virtual void remove(const Key& key); //TODO
  		void clear(); //TODO
  		void print() const;
  		bool isBalanced() const; //TODO
  	private:
  		void clearHelp(Node<Key, Value>* n);
  		bool balancedHelp(Node<Key,Value>* no) const;
  		int Depth(Node<Key,Value>* n) const;


	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<Key,Value>& operator*() const;
				std::pair<Key,Value>* operator->() const;

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;

				friend class BinarySearchTree<Key, Value>;
		};

	public:
		iterator begin() const;
		iterator end() const;
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	public:
		void print() {this->printRoot(this->mRoot);}

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	// TODO
	mRoot = nullptr;

}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	// TODO
	clear();	
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	Node<Key, Value>* search = mRoot;
	// TODO

	//theres nothing there!
if(mRoot == nullptr){
	mRoot = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr);
	mRoot->setRight(nullptr);
	mRoot->setLeft(nullptr);
	return;
}
//there is only a smol root node!
if(mRoot->getLeft() == nullptr && keyValuePair.first < mRoot->getKey()){
	Node<Key, Value>* kvp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, mRoot);
	kvp->setRight(nullptr);
	kvp->setLeft(nullptr);
	mRoot->setLeft(kvp);
	return;
}
if(mRoot->getRight() == nullptr && keyValuePair.first > mRoot->getKey()){
	Node<Key, Value>* kvp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, mRoot);
	kvp->setRight(nullptr);
	kvp->setLeft(nullptr);
	mRoot->setRight(kvp);
	return;
}
//you have a tree!
	while(search !=NULL){
		
		if(search->getKey() < keyValuePair.first){
			if(search->getRight() == NULL){
				break;
			}
			search = search->getRight();			
 		}
 		else if(search->getKey() > keyValuePair.first){
			if(search->getLeft() == NULL){
				break;
			}
			search = search->getLeft();
 		}
 		else if(search->getKey() == keyValuePair.first){
 			search->setValue(keyValuePair.second);
 			return;
 		}
	}

	if(keyValuePair.first < search->getKey()){
		Node<Key, Value>* kvp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, search);
		kvp->setRight(nullptr);
		kvp->setLeft(nullptr);
		search->setLeft(kvp);
		return;
	}
	if(keyValuePair.first > search->getKey()){
		Node<Key, Value>* kvp = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, search);
		kvp->setRight(nullptr);
		kvp->setLeft(nullptr);
		search->setRight(kvp);
		return;
	}

}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	// TODO
if(mRoot == NULL){
	return;
}

if(internalFind(key) == nullptr){
	return;
}


Node<Key, Value>* search = mRoot;


while(search->getLeft() != NULL || search->getRight() != NULL){

	if(key > search->getKey()){
		search = search->getRight();
	}
	if(key < search->getKey()){
		search = search->getLeft();
	}
	if(key == search->getKey()){
		break;
		}
	}//end of while


//if it is just the root
	if(search->getParent() == NULL && search->getLeft() == NULL && search->getRight() == NULL){
		//mRoot->setParent(nullptr);
		//mRoot = nullptr;
		delete mRoot;
		mRoot = nullptr;
		return;
	}
//if you're removing the root but it has two children
	else if(search->getParent() == NULL && search->getLeft() != NULL && search->getRight() !=NULL){
			
			Node<Key, Value>* pre = search->getLeft();
			//std::cout << search->getRight()->getValue() << std::endl;
			//find predecessor
			while(pre->getRight() != NULL){
				pre = pre->getRight();
				}
			/*
			if(pre == NULL){
				pre = search->getRight();
			}*/

			if(pre->getLeft() != NULL){
				pre->getParent()->setLeft(pre->getLeft());
				mRoot = pre;
			}

			mRoot = pre;
			pre->setParent(nullptr);
				//std::cout << "root value " << mRoot->getValue() << std::endl;

			pre->setRight(search->getRight());
				//std::cout << "right value should be " << search->getRight()->getValue() << std::endl;
				//std::cout << "right value " << mRoot->getRight()->getValue() << std::endl;
			
			if(pre != search->getLeft()){
				pre->setLeft(search->getLeft());
				}

				//std::cout << "left value " << mRoot->getLeft()->getValue() << std::endl;

		search->getRight()->setParent(pre);
			//std::cout << "right's parent set" << std::endl;

		if(search->getLeft() != pre){
			//std::cout << "set left" <<std::endl;
			search->getLeft()->setParent(pre);
		}else{
			search->setLeft(pre->getLeft());
			search->getLeft()->setParent(pre);
		}
	/*	
		if(pre->getLeft() != NULL){
			}
			else{
				Node<Key, Value>* del = search->getLeft();
				while(del->getRight() != NULL){
					del = pre->getRight();
				}
				del->getParent()->setRight(nullptr);
			}*/
			

				delete search;
				return;
	}

//if it has two children!
		else if(search->getLeft() != NULL && search->getRight() != NULL){
			Node<Key, Value>* pre = search->getLeft();

			//find predecessor
			while(pre->getRight() != NULL){
				pre = pre->getRight();
			}

			if(pre->getLeft() != NULL && search->getLeft() != pre){
				pre->getParent()->setRight(pre->getLeft());
				pre->getLeft()->setParent(pre->getParent());
			}

			pre->setParent(search->getParent());
			if(pre->getKey() < search->getParent()->getKey()){
				search->getParent()->setLeft(pre);
			}
			if(pre->getKey() > search->getParent()->getKey()){
				search->getParent()->setRight(pre);
			}
			if(search->getRight() != NULL){
				pre->setRight(search->getRight());
				search->getRight()->setParent(pre);
			}

			if(pre != search->getLeft()){
				search->getLeft()->setParent(pre);	
				pre->setLeft(search->getLeft());
			}
			delete search;
			return;
		}
		//if it only has a Left child
		else if(search->getLeft() != NULL && search->getRight() == NULL){
			//make the left child's parent the search's parent
			
			if(search->getParent() == NULL){
				mRoot = search->getLeft();
				mRoot->setParent(nullptr);
				search->getLeft()->setParent(nullptr);
				delete search;
				return;
			}

			Node<Key, Value>* rep = search->getLeft();
			Node<Key, Value>* par = search->getParent();

			
			if(search->getKey() < par->getKey()){
				par->setLeft(rep);
			}
			if(search->getKey() > par->getKey()){
				par->setRight(rep);
			}

			rep->setParent(par);

			delete search;
			
			return;

		}//if it only has a Right child
		else if(search->getRight() != NULL && search->getLeft() == NULL){
			//make the right child's parent the search's parent

			if(search->getParent() == NULL){
				mRoot = search->getRight();
				mRoot->setParent(nullptr);
				search->getRight()->setParent(nullptr);
				delete search;
				return;
			}
			
			Node<Key, Value>* rep = search->getRight();
			Node<Key, Value>* par = search->getParent();

			if(search->getKey()< par->getKey()){
				par->setLeft(rep);
			}
			if(search->getKey()> par->getKey()){
				par->setRight(rep);
			}

			rep->setParent(par);
			
			delete search;
			
			return;
		}
		//if it is a LEAF node
		else if(search->getRight() == NULL && search->getLeft() == NULL){
			if(search->getKey() < search->getParent()->getKey()){
				search->getParent()->setLeft(nullptr);
				delete search;
				return;
			}if(search->getKey() > search->getParent()->getKey()){
				search->getParent()->setRight(nullptr);
				delete search;
				return;
			}


}
}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	// TODO
	if(mRoot == NULL){
		return;
	}
	clearHelp(mRoot);

	mRoot = nullptr;

}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelp(Node<Key, Value>* n){

	if(n == NULL){
		return;
	}


if(n->getRight() != NULL){
	clearHelp(n->getRight());
}
if(n->getLeft() != NULL){
	clearHelp(n->getLeft());
}
	delete n;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	// TODO
	Node<Key, Value>* small = mRoot;

while(small->getLeft() != NULL){
		small = small->getLeft();
	}

	return small;

}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	// TODO

if(mRoot == NULL){
	return nullptr;
}
	
Node<Key, Value>* search = mRoot;


while(search != NULL){
	if(key > search->getKey()){
		if(search->getRight() == NULL){
			return nullptr;
		}
		search = search->getRight();
	}
	if(key < search->getKey()){
		if(search->getLeft() == NULL){
			return nullptr;
		}
		search = search->getLeft();
	}
	if(key == search->getKey()){
		return search;
	}
}

//if it doesn't find it
//if(search->getLeft() == NULL && search->getRight() == NULL && search->getKey() != key){
//	return nullptr;
//}

	return search;

}

/**
 * Return true iff the BST is an AVL Tree.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	// TODO
	if(balancedHelp(mRoot) == true){
		return true;
	}

	return false;

}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balancedHelp(Node<Key,Value>* no) const{

	if(no == NULL){
		return true;
	}

int rd = 0;
if(no->getRight() != NULL){
	rd = Depth(no->getRight());

}
int rl = 0;
if(no->getLeft() != NULL){
	Depth(no->getLeft());
}

	if(rd > rl + 1 || rd < rl-1 || rl > rd+1 || rl <rd-1){
		return false;
	}

	balancedHelp(no->getLeft());
	balancedHelp(no->getRight());

return true;

}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::Depth(Node<Key,Value>* n) const{
	if(n == NULL){
		return 1;
	}
	int hr = 1;
	while(n->getRight() != NULL){
		hr++;
	}
	int hl = 1;
	while(n->getLeft() != NULL){
		hl++;
	}

if(hl >= hr){
	return hl;
}else{
	return hr;
}

return 0;

}


/**
 * Lastly, we are providing you with a print function, BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->mRoot)

   It will print up to 5 levels of the tree rooted at the passed node, in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
