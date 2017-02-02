#pragma once

#include <string>
#include "HashNode.h"
#include "LinkedList.h"

using namespace std;

const int DEFAULT_SIZE = 512;
const int HASH_A = 16;
const int HASH_B = 18;
const int HASH_C = 271;

template<class T>
class HashTable
{
private:
	int size;
	HashNode<T> bucket[];
public:
	HashTable(int arraySize = DEFAULT_SIZE) :
		size(arraySize),
		bucket(new HashNode<T>[size])
	{}
	int hashFunction(string& keyValue) {
		int value = 0;
		for (int i = 0; i < keyValue.length(); i++)
		{
			value += keyValue.at(i);
		}
		return (((HASH_A * value) + HASH_B) % HASH_C) % size;
	}

	void add(T* add, string keyvalue) {
		int hashed = hashFunction(keyvalue);
		bucket->keyValue = keyvalue;

		// collision resolusion 
		if (bucket[hashed].link.find(*add) == -1)
			bucket[hashed].link.add(add);
		else
			cout << "The item is already in the List!" << endl;

	}
	void print(string keyvalue=" ") {
		if (keyvalue == " ") {
			for (int i = 0; i < size; i++)
				if (!bucket[i].link.isEmpty()) {
					cout << "             ----------------------Displaying Bucket " << i << "---------------------------" << endl;
					bucket[i].link.traverse();
				}
		}
		/*int hashed = hashFunction(keyvalue);
		cout << "             ----------------------Displaying Bucket "<< hashed<< "---------------------------"<< endl;
		bucket[hashed].link.traverse();
*/
	}
	T* find(const T& data, string key_value) {
		//cout << "test" << keyValue << endl;
		int index = hashFunction(key_value);
		if (*(bucket[index].link.get(bucket[index].link.find(data))) == data)
			return bucket[index].link.get(bucket[index].link.find(data));
		else
			return nullptr;
	}
	void remove(const T& data, string key_value) {
		int index = hashFunction(keyvalue);
		bucket[index].link.remove(bucket[index].link.find(discard));
	}






};