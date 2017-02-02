#pragma once
#include "LinkedList.h"

using namespace std;

template <class T>
class HashNode {
private:
	string key_value;
	LinkedList<T> data_list;
public:
	HashNode<T>(string key):
		key_value(key),
		data_list(LinkedList<T>())
	{}
	void key_value(const string& key) {
		key_value = key;
	}
	string key_value() {
		return key_value;
	}
	LinkedList<T>& list() {
		return data_list;
	}
};