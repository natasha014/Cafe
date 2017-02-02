#include "Dishes.h"

Dishes::Dishes(string n, double p, bool v, int cal, string c) :
	_name(n),
	_price(p),
	_category(c),
	_vegan(v),
	_calories(cal)
{}
string Dishes::name()
{
	return _name;
}


double Dishes::price()
{
	return _price;
}
string Dishes::category()
{
	return _category;

}
bool Dishes::vegan()
{
	return _vegan;

}

int Dishes::calories()
{
	return _calories;

}
void Dishes::name(string n)
{
	_name = n;

}
void Dishes::price(double p)
{
	_price = p;

}
void Dishes::category(string c)
{
	_category = c;
}
void Dishes::vegan(bool v)
{
	_vegan = v;


}
void Dishes::calories(int c)
{
	_calories = c;

}