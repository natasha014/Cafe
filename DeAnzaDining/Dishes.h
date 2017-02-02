#pragma once
#include <string>
using namespace std;

class Dishes
{
private:
	string _name;
	double _price;
	bool _vegan;
	int _calories;
	string _category;
public:
	Dishes(string n = "", double p = 0, bool v = false, int cal = 0, string c = ""); 
	~Dishes() {};
	string name();
	double price();
	string category();
	int calories();
	bool vegan();
	void name(string n);
	void price(double p);
	void category(string c);
	void vegan(bool v);
	void calories(int c);
	bool operator > (const Dishes& compare) const {
		if (_name > compare._name)
		{
			return true;
		}
		else {
			return false;
		}
	}
	bool operator < (const Dishes& compare) const {
		if (_name < compare._name)
		{
			return true;
		}
		else {
			return false;
		}
	}
	bool operator == (const Dishes& compare) const {
		if (_name == compare._name)
		{
			return true;
		}
		else {
			return false;
		}
	}
	friend ostream& operator << (ostream& strm, const Dishes& print);
};



