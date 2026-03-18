#include "Service.h"
#include <iostream>
#include <string>
using namespace std;
Service::Service(Repo& repo) : repo{ repo } {
	if (this->repo.getCoats().empty()) {
		initCoats();
	}
}
Service::~Service() = default;

void Service::addCoat(const string& size, const string& color, int price, int quantity, const string& photo)
{
	//Add a Coat to the repository
	Coat m{ size,color,price,quantity,photo };
	this->repo.addCoat(m);
	this->repo.save();
	this->undostack.push_back(make_unique<ActionAdd>(repo, m));
	this->redostack.clear();
}
void Service::removeCoat(const string& size, const string& photo)
{
	Coat c{ size, "", 1, 1, photo };
	for (auto a : repo.getCoats())
	{
		if ((a.getSize() == size) && (a.getPhoto() == photo))
			c = a;
	}
	//Remove a Coat from the repository
	this->repo.removeCoat(size, photo);
	this->repo.save();
	this->undostack.push_back(make_unique<ActionRemove>(repo, c));
	this->redostack.clear();
}
void Service::updateCoat(const string& size, const string& color, int price, int quantity, const string& photo)
{
	//Update a Coat from the repository
	this->repo.updateCoat(size, color, price, quantity, photo);
	this->repo.save();
	Coat c{ size, color, price, quantity, photo };
	Coat lc{};
	for (auto a : repo.getCoats())
	{
		if ( (a.getSize() == size ) && (a.getPhoto()==photo))
			lc = a;
	}
	this->undostack.push_back(make_unique<ActionUpdate>(repo,c,lc ));
	this->redostack.clear();
}
void Service::Undo()
{
	if (!undostack.empty())
	{
		auto action = move(undostack.back());
		undostack.pop_back();
		action->executeUndo();
		redostack.push_back(move(action));
	}
	else {
		throw RepoException("Nothign to Undo!");
	}
}
void Service::Redo()
{
	if (!redostack.empty())
	{
		auto action = move(redostack.back());
		redostack.pop_back();
		action->executeRedo();
		undostack.push_back(move(action));
	}
	else {
		throw RepoException("Nothign to Redo!");
	}
}
vector<Coat> Service::getCoats() const
{

	//Return all Coats from the repository
	return this->repo.getCoats();
}
void Service::initCoats()
{
	this->addCoat("S", "red", 100, 10, "photo1");
	this->addCoat("M", "blue", 200, 20, "photo2");
	this->addCoat("L", "green", 300, 30, "photo3");
	this->addCoat("XL", "yellow", 400, 40, "photo4");
	this->addCoat("XXL", "purple", 500, 50, "photo5");
	this->addCoat("XXXL", "orange", 600, 60, "photo6");
	this->addCoat("XS", "pink", 700, 70, "photo7");
	this->addCoat("XXXS", "brown", 800, 80, "photo8");
	this->addCoat("XXXXL", "gray", 900, 90, "photo9");
	this->addCoat("XXXXXL", "black", 1000, 100, "photo10");
	this->addCoat("S", "gray", 1100, 15, "photo11");
	this->addCoat("M", "red", 1200, 250, "photo12");
	this->addCoat("L", "purple", 1300, 350, "photo13");
	this->addCoat("XL", "yellow", 1400, 550, "photo14");
}

