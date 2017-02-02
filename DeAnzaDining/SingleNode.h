#pragma once

using namespace std;

template <class T>
class SingleNode{
private:
	T* _data;
	SingleNode<T>* _next;
public:
	SingleNode(T& data = T(), SingleNode<T>* next = nullptr);
	~SingleNode() {}
	T& data();								//data getter
	SingleNode<T>* next();						//next node getter
	void data(T& data);						//data setter
	void next(SingleNode<T>* next);				//next node setter
};

//constructor
template<class T> SingleNode<T>::SingleNode(T& data, SingleNode<T>* next) :
	_data(&data),
	_next(next)
{}
//getter for data
template <class T> T& SingleNode<T>::data() {
	return *_data;
}

//getter for pointer
template <class T> SingleNode<T>* SingleNode<T>::next() {
	return _next;
}

//setter for data
template <class T> void SingleNode<T>::data(T& data) {
	_data = &data;
}

//setter for pointer
template <class T> void SingleNode<T>::next(SingleNode<T>* next) {
	_next = next;
}