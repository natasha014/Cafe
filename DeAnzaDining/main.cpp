/*C++ Project*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "BinarySearchTree.h"
#include "HashTable.h"
#include "Dishes.h"
using namespace std;

const int MAX_ELEMENT_COUNT = 1024;			//maximum amount of dish that can be on the menu
const string SAVE_LOCATION = "data.csv";	//save location of the data file
const int UNCHOSEN = -1;					//reset choice

ostream& operator << (ostream& os, const Dishes& d) {
	os << d._name << ", "
		<< d._price << ", "
		<< d._vegan << ", "
		<< d._calories << ", "
		<< d._category;
	return os;
}

void print(LinkedList<Dishes>* l);
void save(LinkedList<Dishes>* l);
void add(BinarySearchTree<Dishes>& dish_tree, HashTable<Dishes>& dish_hash, string dishes[], int& size);
void remove(BinarySearchTree<Dishes>& dish_tree, HashTable<Dishes>& dish_hash, string dishes[], int& size);
void promptModify(Dishes* d);
void modify(Dishes* d);
Dishes* search(BinarySearchTree<Dishes>& dish_tree);
Dishes* search(HashTable<Dishes>& dish_hash);


int main() {
	//setup
	ifstream ifs;
	int size = 0;
	string s_buffer;
	//get line count
	ifs.open(SAVE_LOCATION);
	if (ifs.is_open()){
		while (getline(ifs, s_buffer))
			size++;
	}
	else {
		cout << "ERROR: Cannot open file.\n";
		std::system("pause");
		return 0;
	}
	ifs.close();
	//data structure
	//for sorting/saving
	BinarySearchTree<Dishes> dish_tree = BinarySearchTree<Dishes>();
	//for retrieving
	HashTable<Dishes> dish_hash = HashTable<Dishes>(size * 5);
	//list of active dish name
	string dish_names[MAX_ELEMENT_COUNT];
	//file input holders
	string 
		name_in,
		category_in;
	double price_in;
	int calories_in;
	string vegan_in;
	bool is_vegan;
	char buffer;
	//load data from save
	ifs.open(SAVE_LOCATION);
	ifs.clear();
	ifs.seekg(0, ifs.beg);
	if (ifs.is_open())
	{
		while (getline(ifs, name_in, ','))
		{
			//get data for Dishes
			ifs >> price_in;
			ifs >> buffer;
			getline(ifs, vegan_in, ',');
			if (vegan_in == "no")
				is_vegan = false;
			else
				is_vegan = true;
			ifs >> calories_in;
			ifs >> buffer;
			getline(ifs, category_in);
			//create an entry to list of names
			dish_names[size] = name_in;
			//create the associated dish
			Dishes* dish = new Dishes(name_in, price_in, is_vegan, calories_in, category_in);
			//add to HashTable
			dish_hash.add(name_in, dish);
			//add to BST
			dish_tree.add(*dish);

			//cout << "Loading " << name_in << " to Binary Search Tree..." << endl;
		}
	}
	else {
		cout << "ERROR: Cannot open file.\n";
		std::system("pause");
		return 0;
	}
	ifs.close();
	int choice;
	string user_input;
	LinkedList<Dishes>* sorted_dishes = dish_tree.inorder();
	print(sorted_dishes);
	delete sorted_dishes;
	cout << "\nWhat would you like to do with it? ";
	do {
		cout << "Please choose from the following: \n"
			<< "1. I want to add an item.\n"
			<< "2. I want to remove an item.\n"
			<< "3. I want to search for an item.\n"
			<< "4. I want to see the menu again.\n"
			<< "5. I want to save the changes in the file.\n"
			<< "6. Quit." << endl;
		do {
			choice = UNCHOSEN;
			cin.clear();
			cin >> choice;
		} while (choice < 0 || choice > 6);
		//add to BST and HashTable
		if (choice == 1)
			add(dish_tree, dish_hash, dish_names, size);
		//remove from BST and HashTable
		if (choice == 2)
			remove(dish_tree, dish_hash, dish_names, size);
		//search for a Dish. Search by BST is for demo purpose only, and not for real use case.
		if (choice == 3){
			cout << "Search by Hash(1) or BinarySearchTree(2)?" << endl;
			cin.clear();
			cin >> choice;
			if (choice == 1) {
				Dishes* d;
				d = search(dish_hash);
				promptModify(d);
			}
			if (choice == 2) {
				Dishes* d;
				d = search(dish_tree);
				promptModify(d);
			}
		}
		//prints the data structures. Non-inorder outputs are for demo purpose only.
		if (choice == 4) {
			cout << "How would you like to print the menu? Please choose from the following.\n"
				<< "1. List the menu in Hash Table sequence.\n"
				<< "2. List data in sorted order.\n"
				<< "3. List data in pre-sorted order.\n"
				<< "4. Print menu in indented tree form." << endl;
			cin.clear();
			cin >> choice;
			if (choice == 1) {
				dish_hash.print();
			}
			if (choice == 2) {
				sorted_dishes = dish_tree.inorder();
				print(sorted_dishes);
				delete sorted_dishes;
			}
			if (choice == 3) {
				sorted_dishes = dish_tree.preorder();
				print(sorted_dishes);
				delete sorted_dishes;
			}
			if (choice == 4) {
				dish_tree.postorderPrettyPrint();
			}
			choice = 4;
		}
		//saves the data to file
		if (choice == 5) {
			sorted_dishes = dish_tree.preorder();
			save(sorted_dishes);
			delete sorted_dishes;
		}
		cout << endl;
	} while (choice != 6);
	std::system("pause");
	//delete all 
	for (int i = 0; i < size; i++)
		//if Dishes has already been deleted, this does nothing (find returns nullptr)
		delete dish_hash.find(dish_names[i]);
}

void print(LinkedList<Dishes>* l) {
	cout << "                         Dish Name       Price     Vegan    Calories   Category\n"
		<< "----------------------------------      ------     -----    --------   -------- " << endl;
	Dishes d;
	for (int i = 0; i < l->size(); i++) {
		d = (*l)[i];
		cout << setw(34) << d.name()
		<< setw(12) << fixed << setprecision(2) << d.price()
		<< setw(10);
	if (d.vegan()){
		cout << "yes";
	}
	else
		cout << "no";
	cout << ' ' << setw(11) << d.calories() << ' '
		<< setw(10) << d.category() << endl;
	}
}
void save(LinkedList<Dishes>* l) {
	ofstream ofs;
	ofs.open(SAVE_LOCATION);
	Dishes d;
	for (int i = 0; i < l->size(); i++) {
		d = (*l)[i];
		ofs << d.name() << ','
			<< d.price() << ',';
		if (d.vegan())
			ofs << "yes";
		else
			ofs << "no";
		ofs << ','
			<< d.calories() << ','
			<< d.category() << endl;
	}
	ofs.close();
}
void add(BinarySearchTree<Dishes>& dish_tree, HashTable<Dishes>& dish_hash, string dishes[], int& size) {
	string name;
	double price;
	string vegan;
	bool is_vegan;
	int calories;
	string category;
	cout << "Please enter the dish name you want to add." << endl;
	cin.ignore();
	getline(cin, name);
	cout << "Please enter the price of the dish you want to add." << endl;
	cin >> price;
	cout << "Please enter if the dish is vegan or not(enter either yes or no)" << endl;
	cin.ignore();
	getline(cin, vegan);
	if (vegan != "yes")
		is_vegan = false;
	else
		is_vegan = true;
	cout << "Please enter the calories of the dish name you want to add." << endl;
	cin >> calories;
	cout << "Please enter the category of the dish name you want to add." << endl;
	cin.ignore();
	getline(cin, category);
	dishes[size] = name;
	Dishes* d = new Dishes(name, price, is_vegan, calories, category);
	dish_hash.add(name, d);
	dish_tree.add(*d);
	size++;
}
void remove(BinarySearchTree<Dishes>& dish_tree, HashTable<Dishes>& dish_hash, string dishes[], int& size) {
	cout << "Please enter the dish name you want to remove." << endl;
	string name;
	cin.ignore();
	getline(cin, name);
	//no deletion occurs if nonexistant name is used
	Dishes* d = dish_hash.find(name);
	dish_hash.remove(name);
	dish_tree.remove(*d);
	delete d;
}
Dishes* search(BinarySearchTree<Dishes>& dish_tree) {
	cout << "Please enter the dish name you want to search." << endl;
	string name;
	cin.ignore();
	getline(cin, name);
	Dishes* temp = new Dishes(name);
	Dishes* d = dish_tree.find(*temp);
	return d;
}
Dishes* search(HashTable<Dishes>& dish_hash) {
	cout << "Please enter the dish name you want to search." << endl;
	string name;
	cin.ignore();
	getline(cin, name);
	Dishes* d = dish_hash.find(name);
	return d;
}
void promptModify(Dishes* d) {
	if (d == nullptr)
		return;
	cout << "Would you like to modify \"" << d->name() << "\"? Yes(1) or No(2)" << endl;
	int choice;
	cin.clear();
	cin >> choice;
	if (choice == 1)
		modify(d);
}
void modify(Dishes* d) {
	int choice;
	do {
		cout << "What would you like to modify?\n"
			<< "1. Price\n"
			<< "2. Vegan Status\n"
			<< "3. Calories\n"
			<< "4. Category" << endl;
		cin.clear();
		cin >> choice;
		if (choice == 1) {
			double price;
			cout << "Please enter the price of the dish you want to add." << endl;
			cin >> price;
			d->price(price);
		}
		if (choice == 2) {
			string vegan;
			bool is_vegan;
			cout << "Please enter if the dish is vegan or not(enter either yes or no)" << endl;
			cin.ignore();
			getline(cin, vegan);
			if (vegan != "yes")
				is_vegan = false;
			else
				is_vegan = true;
			d->vegan(is_vegan);
		}
		if (choice == 3) {
			int calories;
			cout << "Please enter the calories of the dish name you want to add." << endl;
			cin >> calories;
			d->calories(calories);
		}
		if (choice == 4) {
			string category;
			cout << "Please enter the category of the dish name you want to add." << endl;
			cin.ignore();
			getline(cin, category);
			d->category(category);
		}
		cout << "Would you like to modify \"" << d->name() << "\" further? Yes(1) or No(2)" << endl;
		cin.clear();
		cin >> choice;

	} while (choice != 2);
}