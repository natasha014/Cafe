#pragma once
#include "LinkedList.h"
#include "Stack.h"
#include "BinaryNode.h"

using namespace std;

template <typename T>
class BinarySearchTree
{
private:
	BinaryNode<T>* rootptr;
protected:
	//getter for root node
	void root(BinaryNode<T>* set) {
		rootptr = set;
	}
	//setter for root node
	BinaryNode<T>* root() {
		return rootptr;
	}
public:
	//constructor
	BinarySearchTree() :
		rootptr(nullptr)
	{}
	//add a new node to the tree
	void add(T& data);
	//return the nodes pre order (tree order) in a LinkedList
	LinkedList<T>* preorder();

	//return the nodes in order (sorted order) in a LinkedList
	LinkedList<T>* inorder();
	//remove an existing node
	void remove(const T& data);
	//find a node
	//return pointer to data if found. if not found, return nullptr
	T* find(const T& data);
	//prints the indented tree in cout
	void postorderPrettyPrint() {
		postorderPrettyPrint(0, rootptr);
	}
	void postorderPrettyPrint(int indent, BinaryNode<T>* current);
};

template<class T> void BinarySearchTree<T>::add(T& data) {
	BinaryNode<T>* current = rootptr;
	//if empty tree
	if (rootptr == nullptr) {
		rootptr = new BinaryNode<T>(&data);
	}
	//doing down the tree
	while (current != nullptr) {
		//if left branch
		if (current->data() < data) {
			//empty space found
			if (current->right() == nullptr) {
				current->right(new BinaryNode<T>(&data));
				current = nullptr;
			}
			else
				current = current->right();	//go down on the right
		}
		//if right branch
		else if (current->data() > data) {
			//empty space found
			if (current->left() == nullptr) {
				current->left(new BinaryNode<T>(&data));
				current = nullptr;
			}
			else
				current = current->left();	//go down on the left
		}
		//if data node already exist
		else
			current = nullptr;				//rejects duplicate data
	}
}
template<class T> LinkedList<T>* BinarySearchTree<T>::preorder() {
	LinkedList<T>* preorder_list = new LinkedList<T>();	//returning list
	Stack<BinaryNode<T>> current_nodes = Stack<BinaryNode<T>>();	//nodes traversed
	BinaryNode<T>* current;	//current node
	if (rootptr != nullptr)
		current_nodes.push(*rootptr);	//push root on the stack
	while (!current_nodes.isEmpty()) {
		current = &current_nodes.pop();	//pop last node
		preorder_list->add(current->data(), preorder_list->size());	//add it to list
		if (current->right() != nullptr) 
			current_nodes.push(*current->right());	//go right after...
		if (current->left() != nullptr)
			current_nodes.push(*current->left());	//going left
	}
	return preorder_list;
}

template<class T> LinkedList<T>* BinarySearchTree<T>::inorder() {
	LinkedList<T>* inorder_list = new LinkedList<T>();	//returning list
	Stack<BinaryNode<T>> current_nodes = Stack<BinaryNode<T>>();	//nodes traversed
	BinaryNode<T>* current = rootptr;	//current node
	while (!current_nodes.isEmpty() || current != nullptr) {
		if (current != nullptr) {
			current_nodes.push(*current);	//push until leftmost node
			current = current->left();	
		}
	 	else {
			current = &current_nodes.pop();	//pop leftmost node
			inorder_list->add(current->data(), inorder_list->size());	//add leftmost node to list
			current = current->right();	//start to traversing right branch of leftmost node, finding leftmost node
		}
	}
	return inorder_list;
}

template<class T>
T* BinarySearchTree<T>::find(const T& data) {
	BinaryNode<T>* current = rootptr;
	while (current != nullptr) {
		//found
		if (current->data() == data) {
			return &current->data();
		}
		else {
			if (data > current->data())
				current = current->right();	//go right
			else
				current = current->left();	//go left
		}
	}
	//not found
	return nullptr;
}


template <class T>
void BinarySearchTree<T>::remove(const T& data) {
	BinaryNode<T>
		*current = rootptr,	//current node being operated on
		*last = nullptr,	//parent node of data node
		*dataptr = nullptr;	//pointer to hold the data node
	
	//finds location of data node
	while (current != nullptr) {
		//found data
		if (current->data() == data) {
			break;
		}
		//not current
		else {
			last = current;
			if (data > current->data()) {
				current = current->right();
			}
			else {
				current = current->left();
			}
		}
	}
	//if not found
	if (current == nullptr)
		return;
	//save data
	dataptr = current;
	current = nullptr;
	//left/right nodes of data node
	BinaryNode<T>
		*left_original = dataptr->left(),
		*left = dataptr->left(),
		*right_original = dataptr->right(),
		*left_last = nullptr;
	//find replacement node
	//if 0 or 1 child
	//current = nullptr or the remaining child
	if (left_original == nullptr || right_original == nullptr) {
		if (left_original != nullptr)
			current = left_original;
		else
			current = right_original;
	}
	//if 2 children
	//current = leftmost node in right tree
	//or
	//current = rightmost node in the left tree
	else {
		while (current == nullptr) {
			//find rightmost node of left tree
			if (left->right() == nullptr)
				current = left;
			else {
				left_last = left;
				left = left->right();
			}
		}

		//insert branch to node
		//disassociate child of current
		if (current == left && current != left_original) 
			left_last->right(current->left());

		//place current at where old data node was
		current->left(left_original);
		current->right(right_original);
	}

	//insert node to parent
	//if data node had parent
	if (last != nullptr) {
		if (last->left() == dataptr)
			last->left(current);
		if (last->right() == dataptr)
			last->right(current);
	}
	//if data node was root
	else
		rootptr = current;
	//delete data node
	delete dataptr;
}

template<class T>
void BinarySearchTree<T>::postorderPrettyPrint(int indent, BinaryNode<T>* current)
{
	if (current != nullptr) {
		if (current->right()) {
			postorderPrettyPrint(indent + 4, current->right());
		}
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
		if (current->right()) std::cout << " /\n" << std::setw(indent) << ' ';
		std::cout << current->data() << "\n ";
		if (current->left()) {
			std::cout << std::setw(indent) << ' ' << " \\\n";
			postorderPrettyPrint(indent + 4, current->left());
		}
	}
}