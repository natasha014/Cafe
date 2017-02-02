#pragma once

#include <string>
#include "HashNode.h"
#include "LinkedList.h"

using namespace std;

const int DEFAULT_SIZE = 512;
const int HASH_A = 16;
const int HASH_B = 18;
const int HASH_C = 271;

template <class T>
class HashTable
{
private:
	int size;
	int collisioncount;
	LinkedList<HashNode<T>> *bucket;
public:
	HashTable(int arraySize = DEFAULT_SIZE) :
		size(arraySize),
		bucket(new LinkedList<HashNode<T>>[size]), collisioncount(0)
	{}
	//~HashTable(){}
	int getcollisioncount()
	{
		return collisioncount;
	}
	int hash(string& key_value) {
		int value = 0;
		for (int i = 0; i < key_value.length(); i++) {
			value += key_value.at(i);
		}
		return (((HASH_A * value) + HASH_B) % HASH_C) % size;
	}

	void add(string& key_value, T* data) {
		int index = hash(key_value);
		HashNode<T>* node = new HashNode<T>(key_value, data);
		// collision resolusion 
		if (bucket[index].find(*node) == -1) {
			if(bucket[index].size() != 0)
				collisioncount++;
			bucket[index].add(*node);
		}
		else
			cout << "The item is already in the List!" << endl;
	}
	void print() {
		int position;
		for (int i = 0; i < size; i++)
			if (!bucket[i].isEmpty()) {
				position = 0;
				cout << "Displaying Bucket " << i << ": " << endl;
				while (bucket[i].size() > position) {
					cout << "    " << *bucket[i][position].data() << endl;
					position++;
				}
			}
	}
	T* find(string& key_value) {
		int index = hash(key_value);
		HashNode<T>* node = new HashNode<T>(key_value, &T());
		if (bucket[index].find(*node) != -1)
			return (bucket[index].get(bucket[index].find(*node)).data());
		else
			return nullptr;
	}
	void remove(string& key_value) {
		int index = hash(key_value);
		HashNode<T>* node = new HashNode<T>(key_value, &T());
		if(bucket[index].find(*node) != -1)
			bucket[index].remove(bucket[index].find(*node));
	}

};