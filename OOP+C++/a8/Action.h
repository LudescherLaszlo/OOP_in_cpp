#pragma once
#include "Coat.h"
#include "Repository.h"
class action {
public:
	virtual void executeUndo() const = 0;
	virtual void executeRedo() const = 0;
};
class ActionAdd :public action
{
private:
	Coat addedCoat;
	Repo& repo;
public:
	ActionAdd(Repo& r, Coat& s) :repo(r), addedCoat(s) {}
	void executeUndo() const override
	{
		repo.removeCoat(addedCoat.getSize(),addedCoat.getPhoto());
	}
	void executeRedo() const override
	{
		repo.addCoat(addedCoat);
	}
};
class ActionRemove :public action
{
private:
	Coat deletedCoat;
	Repo& repo;
public:
	ActionRemove(Repo& r, Coat& s) :repo(r), deletedCoat(s) {}
	void executeUndo() const override
	{
		repo.addCoat(deletedCoat);
	}
	void executeRedo() const override
	{
		repo.removeCoat(deletedCoat.getSize(), deletedCoat.getPhoto());
	}
};
class ActionUpdate :public action
{
private:
	Coat last;
	Coat current;
	Repo& repo;
public:
	ActionUpdate(Repo& r, Coat& c, Coat& lc) :repo(r), last(c), current(lc) {}
	void executeUndo() const override
	{
		repo.updateCoat(last.getSize(),last.getColor(),last.getPrice(),last.getQuantity(),last.getPhoto());
	}
	void executeRedo() const override
	{
		repo.updateCoat(current.getSize(), current.getColor(), current.getPrice(), current.getQuantity(), current.getPhoto());
	}
};