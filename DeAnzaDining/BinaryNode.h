#pragma once
template <typename T>
class BinaryNode
{
private:
	T* _data;					// Data Attribute
	BinaryNode<T> *leftptr;		// pointer to next node
	BinaryNode<T> *rightptr;	// pointer to the previous node
public:
	BinaryNode(T* data = nullptr, BinaryNode<T>* left = nullptr, BinaryNode<T>* right = nullptr):
		_data(data),
		leftptr(left),
		rightptr(right)
	{}
	//setter for data
	void data(T& d) {
		_data = *d;
	}
	//getter for data
	T& data() {
		return *_data;
	}
	//setter for left node
	void left(BinaryNode<T>* l) {
		leftptr = l;
	}
	//getter for left node
	BinaryNode<T>* left() {
		return leftptr;
	}
	//setter for right node
	void right(BinaryNode<T>* r) {
		rightptr = r;
	}
	//getter for right node
	BinaryNode<T>* right() {
		return rightptr;
	}
	//is node a leaf (lacks left and right node)
	bool is_leaf() {
		if (leftptr == nullptr && rightptr == nullptr)
			return true;
		return false;

	}
};