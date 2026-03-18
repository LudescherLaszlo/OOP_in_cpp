#pragma once
#include "Repository.h"
#include <vector>
#include "action.h"
#include <memory>
class Service
{
private:
	Repo& repo;
	vector <unique_ptr<action>> undostack;
	vector <unique_ptr<action>> redostack;
public:
	explicit Service(Repo& repo);
	Service() = default;
	~Service();
	Repo getRepo() const { return repo; }
	void addCoat(const string& size, const string& color, int price, int quantity, const string& photo);
	void removeCoat(const string& size, const string& photo);
	void updateCoat(const string& size, const string& color, int price, int quantity, const string& photo);
	vector<Coat> getCoats() const;
	void initCoats();
	void Undo();
	void Redo();

};
