#pragma once
#include <iostream>
#include <string>
using namespace std;
class Coat
{
private:
	string size;
	string color;
	int price;
	int quantity;
	string photo;
public:
	Coat();

	Coat(const string& size, const string& color, int price, int quantity, const string& photograph);
	string getSize() const { return size; }
	string getColor() const { return color; }
	int getPrice() const { return price; }
	int getQuantity() const { return quantity; }
	string getPhoto() const { return photo; }
	void setSize(string size);
	void setColor(string color);
	void setPrice(int price);
	void setQuantity(int quantity);
	void setPhoto(string photo);
	friend ostream& operator<<(ostream& out, const Coat& c);
	friend istream& operator>>(istream& in, Coat& c);


};