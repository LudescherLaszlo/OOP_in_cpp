#pragma once
#include <string>
#include <vector>
#include <exception>
#include <string>
#include "Coat.h"
using namespace std;
class Validator {
public:
	static bool DoesCoatExist(vector<Coat> coats, string size, string photo)
	{
		for (Coat c : coats)
		{
			if (c.getSize() == size && c.getPhoto() == photo)return true;
		}
		return false;
	}
};
class RepoException : public exception {
private:
	string message;
public:
	RepoException(string message) : message("Repository:" + message) {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};