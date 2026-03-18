#include "Coat.h"
#include <string>
#include <iostream>
using namespace std;

// Default constructor initializing all attributes with default values
Coat::Coat()
{
	this->size = "";
	this->color = "";
	this->price = 0;
	this->quantity = 0;
	this->photo = "";
}

// Constructor initializing the coat with given attributes
Coat::Coat(const string& size, const string& color, int price, int quantity, const string& photo)
{
	this->size = size;
	this->color = color;
	this->price = price;
	this->quantity = quantity;
	this->photo = photo;
}

// Sets the size of the coat
void Coat::setSize(string size)
{
	this->size = size;
}

// Sets the color of the coat
void Coat::setColor(string color)
{
	this->color = color;
}

// Sets the price of the coat
void Coat::setPrice(int price)
{
	this->price = price;
}

// Sets the quantity of coats available
void Coat::setQuantity(int quantity)
{
	this->quantity = quantity;
}

// Sets the photo URL of the coat
void Coat::setPhoto(string photo)
{
	this->photo = photo;
}

ostream& operator<<(ostream& out, const Coat& c)
{
	out << c.getSize() << "," << c.getColor() << "," << c.getPrice() << "," << c.getQuantity() << "," << c.getPhoto() << endl;
	return out;
}

istream& operator>>(istream& in, Coat& c)
{
	string size, color, photo;
	int price, quantity;
	getline(in, size, ',');
	getline(in, color, ',');
	in >> price;
	in.ignore();
	in >> quantity;
	in.ignore();
	getline(in, photo);
	c = Coat(size, color, price, quantity, photo);
	return in;

}
