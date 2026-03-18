#include "UserService.h"
#include <algorithm>
#include <stdexcept>
#include<fstream>
#include <sstream>
#include <iomanip>

using namespace std;

UserService::UserService(Repo& allCoatsRepo, Repo& basketRepo)
    : allCoatsRepo{ allCoatsRepo }, basketRepo{ basketRepo }, price(0) {
    for (const auto& coat : basketRepo.getCoats()) {
        this->price += coat.getPrice();
    }
}


vector<Coat> UserService::getCoats() const
{
    return this->getAllCoatsRepo().getCoats();
}

vector<Coat> UserService::getCoatsFromBasket() const
{

    return this->getBasketRepo().getCoats();
}

void UserService::addCoatToBasket(const string& size, const string& color, int price, int quantity, const string& photo)
{
    Coat m{ size, color, price, quantity, photo };
    this->basketRepo.addCoat(m);
    this->price += price;
    this->basketRepo.save();
    this->undostack.push_back(make_unique<ActionAdd>(basketRepo, m));
    this->redostack.clear();
}

Coat UserService::getNextCoat(string& size, Coat& currentCoat)
{
    const auto& coats = this->getCoats();
    if (coats.empty()) {
        throw runtime_error("No coats found.");
    }

    bool empty = (size == "");
    bool pastCurrent = (currentCoat.getColor().empty());

    // Find the current coat's position
    auto currentIt = find_if(coats.begin(), coats.end(),
        [&currentCoat](const Coat& c) {
            return c.getPhoto() == currentCoat.getPhoto() &&
                c.getSize() == currentCoat.getSize();
        });

    // Determine where to start searching
    auto startIt = coats.begin();
    if (currentIt != coats.end()) {
        startIt = next(currentIt);
        if (startIt == coats.end()) {
            startIt = coats.begin();
        }
    }

    // Iterate through the coats to find the next suitable one
    for (auto it = startIt; it != coats.end(); ++it) {
        if ((empty || it->getSize() == size) && (pastCurrent || &(*it) != &(*currentIt))) {
            return *it;
        }
    }

    // If we didn't find anything in the first pass, try from beginning
    for (auto it = coats.begin(); it != startIt; ++it) {
        if ((empty || it->getSize() == size) && (pastCurrent || &(*it) != &(*currentIt))) {
            return *it;
        }
    }
    if (currentCoat.getColor().empty() == false)
    {
        return *currentIt;
    }

    throw runtime_error("No coats found for the given size.");
}

void UserService::Undo()
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
void UserService::Redo()
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