#pragma once

#include <iostream>
#include "SingleNode.h"
using namespace std;

template <class T>
class LinkedList{
protected:
	SingleNode<T>* head;							//first element of the list
public:
	LinkedList();							//creates an empty list
	~LinkedList();

	int size();								//returns amount of elements in list
	T& get(int loc = size() - 1);			//get the data at loc. assumes loc < size

	int find(const T data);					//finds data in list. returns the node containing the data (-1 if failed to find)
	void add(T& data, int loc = 0);	//adds element at loc. assumes 0 < loc <= size
	void remove(int loc = 0);		//remove element at loc. assumes 0 < loc < size
	void drop();							//clear the list
	bool isEmpty();							//check if the list is empty
	friend ostream& operator<<<>(ostream& os, const LinkedList<T> ll);
	T& operator[](int i);
											//insert content of linkedlist in 
	void printNode(int loc);				//display the content of node in cout using the operator<< of the content

};

template <class T>
LinkedList<T>::LinkedList() :
	head(nullptr)
{}

template <class T> LinkedList<T>::~LinkedList() {
	//drop();
}

template <class T> int LinkedList<T>::size() {
	/*
	Pre:None
	Post:None
	Purpose:returns the number of nodes in the linked list
	*/
	int size = 0;
	SingleNode<T>* current = head;
	while (current != nullptr) {
		size++;
		current = current->next();
	}
	return size;
}

template <class T> T& LinkedList<T>::get(int loc) {
	/*
	Pre: location of the node being accessed
	Post: Reference to the data in the node
	Purpose: Gets the data stored in a particular node
	*/
	if (loc < 0 && loc > size() - 1) {
		throw range_error("LinkedList<T>::get(): Location Out of Bound (0 to size() - 1)");
		return head->data();
	}
	SingleNode<T>* current = head;
	for (int i = 0; i < loc; i++)
		current = current->next();
	return current->data();
}

template <class T> int LinkedList<T>::find(const T data) {
	/*
	Pre: Data that is to be found
	Post:location of that data in the  list
	Purpose: finds the location of data in the list
	*/
	int loc = 0;
	SingleNode<T>* current = head;
	while (current != nullptr) {
		if (current->data() == data)
			return loc;
		loc++;
		current = current->next();
	}
	return -1;
}

template <class T> void LinkedList<T>::add(T& data, int loc) {
	/*
	Pre: data to be added, and the location to be added at
	Post: none
	Purpose: adds a node at the given location
	*/
	if (loc < 0 && loc > size()) {
		throw range_error("LinkedList<T>::add(): Location Out of Bound (0 to size())");
		return;
	}
	SingleNode<T>* last = nullptr;
	SingleNode<T>* current = head;
	for (int i = 0; i < loc && current != nullptr; i++) {
		last = current;
		current = current->next();
	}
	SingleNode<T>* node = new SingleNode<T>(data, current);
	if (loc > 0)
		last->next(node);
	else
		head = node;
}

template <class T> void LinkedList<T>::remove(int loc) {
	/*
	Pre: location of node to be removed
	Post:none
	Purpose: removes node for a given location in the list;
	*/
	if (loc < 0 && loc > size() - 1) {
		throw range_error("LinkedList::<T>remove():  Location Out of Bound (0 to size() - 1)");
		return;
	}
	SingleNode<T>* last = nullptr;
	SingleNode<T>* current = head;
	SingleNode<T>* next = current->next();
	for (int i = 0; i < loc && current != nullptr; i++) {
		last = current;
		current = current->next();
		next = current->next();
	}
	delete current;
	current = nullptr;
	if (loc > 0)
		last->next(next);
	else
		head = next;
}

template <class T> void LinkedList<T>::drop() {
	/*
	Pre:None
	Post:None
	Purpose:Clears the list of all nodes
	*/
	while (head != nullptr)
		remove(0);
}

template <class T> ostream& operator<<<>(ostream& os, const LinkedList<T> ll)
{
	/*
	Pre: reference to output stream, the head of the list
	Post: reference to output stream
	Purpose: to display the linked list
	*/
	SingleNode<T>* current = ll.head;
	while (current != nullptr) {
		os << current->data() << endl;
		current = current->next();
	}
	return os;

}

template <class T> bool LinkedList<T>::isEmpty() {
	/*
	Pre:None
	Post: true/false depending on whether list is empty
	Purpose: to check whether list is empty.
	*/
	if (head == nullptr)
		return true;
	return false;
}

template<class T>
T& LinkedList<T>::operator[](int i)
{
	return get(i);
}

template <class T> void LinkedList<T>::printNode(int loc) {
	cout << get(loc);
}
