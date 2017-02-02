#pragma once

#include "LinkedList.h"
using namespace std;

template <class T>
class Stack: protected LinkedList<T>
{
public:
	Stack();					//creates an empty stack
	void push(T& data);			//push the data to the top of stack
	T& pop();					//pop the data from the top of stack
	T& peek();					//gives the data of the top element without popping
	using LinkedList<T>::isEmpty;
	using LinkedList<T>::size;
	using LinkedList<T>::drop;
};

template<class T> Stack<T>::Stack() :
	LinkedList()
{}

template <class T> void Stack<T>::push(T& data) {
	add(data);
}

template <class T> T& Stack<T>::pop() {
	if (isEmpty())
		throw underflow_error("Stack<T>::pop(): No Nodes on Stack");
	T* data = &get(0);
	remove();
	return *data;
}

template <class T> T& Stack<T>::peek() {
	if (isEmpty())
		throw underflow_error("Stack<T>::peek(): No Nodes on Stack");
	return get(0);
}
