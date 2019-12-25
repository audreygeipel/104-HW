#include "bst.h"

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

template <typename Key, typename Value>
class rotateBST: public BinarySearchTree<Key, Value>
{

protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r); 
	Node<Key, Value>* mRoot;
	std::vector<Key> traverse(Node<Key, Value>* r);

public:
	bool sameKeys(const rotateBST& t2) const;
	void transform(rotateBST& t2) const;

};

template <typename Key, typename Value>
	void rotateBST<Key,Value>::leftRotate(Node<Key, Value>* r){
		if(r->getRight() == NULL){
			return;
		}
		std::cout << "r's right child is: " << r->getRight()->getValue() << std::endl;
		std::cout << "r's left child is: " << r->getLeft()->getValue() << std::endl;

	if(r->getParent() == NULL){
//set r's right child's parent to r's parent
		mRoot = r->getRight();
		//->setParent(nullptr);
//set r's parent to it's right child
		mRoot->setParent(nullptr);
		//r->setParent(r->getRight());

//if r's right child's left child is null
		if(r->getRight()->getLeft() == NULL){
			//set r's right child's left child to r
			r->getParent()->setLeft(r);
		}
//if r's right child's left child is not null
		else if(r->getRight()->getLeft() != NULL){
			//set r's right child's left child to r's right child's
			r->getRight()->getLeft()->setParent(r);
			r->setRight(r->getRight()->getLeft());
			//set r's right child's left child to r
		}
		r->getRight()->setParent(r);
		r->getLeft()->setParent(r);
		r->getParent()->setLeft(r);


std::cout << "rotate done" << std::endl;
		std::cout << "r's parent is: " << r->getParent()->getValue() << std::endl;
		std::cout << "r's right child is: " << r->getRight()->getValue() << std::endl;
		std::cout << "r's left child is: " << r->getLeft()->getValue() << std::endl;
}
else{
	//set r's right child's parent to r's parent
		r->getRight()->setParent(r->getParent());
//set r's parent to it's right child
		r->setParent(r->getRight());

//if r's right child's left child is null
		if(r->getRight()->getLeft() == NULL){
			//set r's right child's left child to r
			r->getRight()->setLeft(r);
		}
//if r's right child's left child is not null
		else if(r->getRight()->getLeft() != NULL){
			//set r's right child to r's right child's left child
			r->getRight()->getLeft()->setParent(r);
			r->setRight(r->getRight()->getLeft());
			//set r's right child's left child to r
			//r->getRight()->setLeft(r);
			//r->getParent()->getLeft()->setParent(r);
		}
		r->getRight()->setParent(r);
		r->getLeft()->setParent(r);
		r->getParent()->setLeft(r);
		//r->getParent()->setLeft(r->getRight());

std::cout << "rotate done" << std::endl;
		std::cout << "r's parent is: " << r->getParent()->getValue() << std::endl;
		std::cout << "r's right child is: " << r->getRight()->getValue() << std::endl;
		std::cout << "r's left child is: " << r->getLeft()->getValue() << std::endl;

	}
}
/*perform a left rotation at the parameter node. If r has no right child, this function should 
do nothing. This should run in constant time.*/
template <typename Key, typename Value>
	void rotateBST<Key,Value>::rightRotate(Node<Key, Value>* r){
		if(r->getLeft() == NULL){
			return;
		}

std::cout << "r's parent is: " << r->getParent()->getValue() << std::endl;
		std::cout << "r's right child is: " << r->getRight()->getValue() << std::endl;
		std::cout << "r's left child is: " << r->getLeft()->getValue() << std::endl;

//set r's left child's parent to r's parent
		r->getLeft()->setParent(r->getParent());
//set r's parent to it's left child
		r->setParent(r->getLeft());

//if r's left child's right child is null
		if(r->getLeft()->getRight() == NULL){
			//set r's left child's right child to r
			r->getLeft()->setRight(r);
//			r->getParent()->getRight()->setParent()
		}
//if r's left child's right child is not null
		else if(r->getLeft()->getRight() != NULL){
			//set r's right child to r's right child's left child
			r->getLeft()->getRight()->setParent(r);
			r->setLeft(r->getLeft()->getRight());
			//set r's right child's left child to r
			
		}
		r->getLeft()->setParent(r);
		r->getRight()->setParent(r);
		r->getParent()->setRight(r);

std::cout << "r's parent is: " << r->getParent()->getValue() << std::endl;
		std::cout << "r's right child is: " << r->getRight()->getValue() << std::endl;
		std::cout << "r's left child is: " << r->getLeft()->getValue() << std::endl;

	}
/*perform a right rotation at the parameter node. If r has no left child, this function should 
do nothing. This should run in constant time.*/


template <typename Key, typename Value>
	bool rotateBST<Key,Value>::sameKeys(const rotateBST& t2) const{

/*		Node<Key, Value>* n = t2.mRoot;

while(n->getRight() != NULL || n->getLeft() != NULL){
		if(n->getRight() != NULL){
			if(this->internalFind(n->getRight()->getKey()) == nullptr){
				return false;
				}
			}
		if(n->getLeft() != NULL){
			if(this->internalFind(n->getLeft()->getKey()) == nullptr){
				return false;
			}
		}
		n = n->getRight();

	}
while(n->getRight() != NULL || n->getLeft() != NULL){
		if(n->getRight() != NULL){
			if(t2.internalFind(n->getRight()->getKey()) == nullptr){
				return false;
				}
			}
		if(n->getLeft() != NULL){
			if(t2.internalFind(n->getLeft()->getKey()) == nullptr){
				return false;
			}
		}
		n = n->getLeft();
	}
*/

		return true;
	}

template <typename Key, typename Value>
	std::vector<Key> rotateBST<Key,Value>::traverse(Node<Key, Value>* r){

		/*if(r == NULL){
			return;
		}

		traverse(t2.)
	*/
		return;
	}
/*given another BST, checks that the set of keys in both trees are identical. This should run in 
O(n) time, where n is the number of nodes in the tree.*/


template <typename Key, typename Value>
	void rotateBST<Key,Value>::transform(rotateBST& t2) const{
//given another BST t2, if t2 contains the same keys as the one for this, transform the BST t2
/*into the one for this using only rotations. If the BST t2 does not have the same keys as this, 
this function should do nothing and neither BST should be modified.*/	
		if(sameKeys(t2)== false){
			return;
		}

/*Perform right rotations on the root node of t2 until it has no left child.*/
		Node<Key, Value>* n = t2.mRoot;
	while(n->getLeft()!= NULL){
		while(n->getLeft() != NULL){
			t2.rightRotate(t2.internalFind(n->getKey()));
		}
		n = n->getRight();
	}
//Recursively move to the right child and repeat the above operation.
//This should produce a tree which is effectively a linked list.

//Now perform left rotations on the root node of t2, until the root of t2 is the 
//same as the root of this.
		while(t2.mRoot != this->mRoot){
			t2.leftRotate(t2.mRoot);
		}
/*Recursively do rotations on the left child and the right child until they match the node at that position of this.
This should produce the specified tree using only rotations.)*/	

		//t2.leftRotate(t2.mRoot);
	}




