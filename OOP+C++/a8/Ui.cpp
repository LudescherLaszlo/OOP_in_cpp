/*
#include "UI.h"
#include <cstring>
#include <string>
#include <limits>
#include <windows.h>
using namespace std;
UI::UI(Service& service, UserService& userService) : service(service), userService(userService)
{
}


UI::~UI() = default;
void read(string& size, string& color, int& price, int& quantity, string& photo)
{
	cout << "Size: ";
	cin >> size;
	cout << "Color: ";
	cin >> color;
	cout << "Price: ";
	cin >> price;
	if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); throw exception("Price must be intiger!"); }
	cout << "Quantity: ";
	cin >> quantity;
	if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); throw exception("Quantity must be intiger!"); }
	cout << "Photo: ";
	cin >> photo;
}
void UI::adminUI()
{
	while (true)
	{
		cout << "1.Add coat" << endl;
		cout << "2.Remove coat" << endl;
		cout << "3.Update coat" << endl;
		cout << "4.Show all coats" << endl;
		cout << "0.Exit" << endl;
		int option;
		string size, color, photo;
		int price, quantity;
		vector<Coat> coats;
		cout << "Choose an option: ";
		cin >> option;
		if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "Option must be intiger!" << endl; }
		else {
			switch (option)
			{
			case 1:


				try { read(size, color, price, quantity, photo); }
				catch (exception a) { cout << a.what() << endl; break; }
				try { this->service.addCoat(size, color, price, quantity, photo); }
				catch (const RepoException& e) { cout << e.what() << endl; }
				break;
			case 2:
				cout << "Size: ";
				cin >> size;
				cout << "Photo: ";
				cin >> photo;
				try { this->service.removeCoat(size, photo); }
				catch (const RepoException& e) { cout << e.what() << endl; }


				break;
			case 3:
				try { read(size, color, price, quantity, photo); }
				catch (exception a) { cout << a.what() << endl; break; }
				try { this->service.updateCoat(size, color, price, quantity, photo); }
				catch (const RepoException& e) { cout << e.what() << endl; }
				break;
			case 4:
				coats = this->service.getCoats();
				for (int i = 0; i < coats.size(); i++)
				{
					Coat m = coats[i];
					cout << m.getSize() << " | " << m.getColor() << " | " << m.getPrice() << " | " << m.getQuantity() << " | " << m.getPhoto() << endl;
					cout << endl;
				}
				break;
			case 0:
				return;
			}
		}
	}
}


//--------------------------------USER UI--------------------------------
// Trim from start (in place)
void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		[](unsigned char ch) { return !std::isspace(ch); }));
}

// Trim from end (in place)
void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),
		[](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

// Trim both ends (in place)
void trim(std::string& s) {
	ltrim(s);
	rtrim(s);
}
void UI::userUI()
{
	string size = "";
	Coat currentCoat;
	while (true)
	{
		cout << "1.Show next coat by size (if size is empty consider all)" << endl;
		cout << "2.Add coat to basket" << endl;
		cout << "3.Don't add coat to basket" << endl;
		cout << "4.See the shopping basket and the total price of the items" << endl;
		cout << "5.Open shopping basket file" << endl;
		cout << "0.Exit" << endl;
		int option;
		string color, photo;
		int price, quantity;
		vector<Coat> coats;
		cout << "Choose an option: ";
		cin >> option;
		if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "Option must be intiger!" << endl; }
		else {
			switch (option)
			{
			case 1:
				cout << "Size: ";
				cin.ignore(10000, '\n');

				cout << "Enter a string (can be empty): ";
				getline(cin, size);

				//cout << size << endl;
				try {
					currentCoat = this->userService.getNextCoat(size, currentCoat);
				}
				catch (exception a) {
					cout << a.what() << endl;
					break;
				}
				cout << currentCoat.getSize() << " | " << currentCoat.getColor() << " | " << currentCoat.getPrice() << " | " << currentCoat.getQuantity() << " | " << currentCoat.getPhoto() << endl;
				cout << endl;

				break;
			case 2:
				if (currentCoat.getColor() == "")
				{
					cout << "First select a coat!\n";
				}
				else
				{
					try {
						this->userService.addCoatToBasket(currentCoat.getSize(), currentCoat.getColor(), currentCoat.getPrice(), currentCoat.getQuantity(), currentCoat.getPhoto());
					}
					catch (exception a) {
						cout << a.what() << endl;
						break;
					}
					cout << "Coat added\n";
					cout << "Current price of the basket:" << this->userService.getPrice() << endl;
				}
				break;
			case 3:
				if (currentCoat.getColor() == "")
				{
					cout << "First select a coat!\n";
					break;
				}

				cout << "The selected size is:" << size << endl;
				cout << "The next coat is" << endl;
				try {
					currentCoat = this->userService.getNextCoat(size, currentCoat);
				}
				catch (exception a) {
					cout << a.what() << endl;
					break;
				}
				cout << currentCoat.getSize() << " | " << currentCoat.getColor() << " | " << currentCoat.getPrice() << " | " << currentCoat.getQuantity() << " | " << currentCoat.getPhoto() << endl;
				cout << endl;

				break;
			case 4:
				for (int i = 0; i < this->userService.getCoatsFromBasket().size(); i++)
				{
					Coat m = this->userService.getCoatsFromBasket()[i];
					cout << m.getSize() << " | " << m.getColor() << " | " << m.getPrice() << " | " << m.getQuantity() << " | " << m.getPhoto() << endl;
					cout << endl;
				}
				cout << "Current price of the basket:" << this->userService.getPrice() << endl << endl;
			case 5: {
				string filePath = this->userService.getBasketRepo().filePath();// returns full path with .csv or .html
				ShellExecuteA(NULL, "open", filePath.c_str(), NULL, NULL, SW_SHOWNORMAL);
				break;
			}

				  break;
			case 0:
				return;
			}
		}
	}

}
void UI::run()
{
	while (true)
	{
		cout << "1.Admin" << endl;
		cout << "2.User" << endl;
		cout << "0.Exit" << endl;
		int option;
		cout << "Choose an option: ";
		cin >> option;
		if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); cout << "Option must be intiger!" << endl; }
		else {
			switch (option)
			{
			case 1:
				this->adminUI();
				break;
			case 2:
				this->userUI();
				break;
			case 0:
				return;
			}
		}
	}
}


*/