#pragma once
#include "LinkedList.h"

using namespace std;

template <class T>
class HashNode {
private:
	string key_value;
	T* dataptr;
public:
	HashNode(string& key, T* data):
		key_value(key),
		dataptr(data)
	{}
	void key(string& key) {
		key_value = key;
	}
	string key() {
		return key_value;
	}
	void data(T* data){
		dataptr = data;
	}
	T* data() {
		return dataptr;
	}
	bool operator==(HashNode<T> k) {
		return key() == k.key();
	}
	bool operator<(HashNode<T> k) {
		return key() < k.key();
	}
};