#pragma once
#include "Repository.h"
#include <vector>
#include "action.h"
#include <memory>

class UserService {
private:
    Repo& allCoatsRepo;
    Repo& basketRepo;
    int price;
    vector <unique_ptr<action>> undostack;
    vector <unique_ptr<action>> redostack;

public:
    UserService(Repo& allCoatsRepo, Repo& basketRepo);

    ~UserService() = default;

    std::vector<Coat> getCoats() const;
    std::vector<Coat> getCoatsFromBasket() const;
    void addCoatToBasket(const string& size, const string& color, int price, int quantity, const string& photo);
    Coat getNextCoat(string& size, Coat& currentCoat);
    int getPrice() const { return price; }
    Repo& getAllCoatsRepo() const { return allCoatsRepo; }
    Repo& getBasketRepo() const { return basketRepo; }
    void Undo();
    void Redo();
    //file
    void saveBasketToHTML(const std::string& filename) const;
    // std::string generateBasketHTML() const;


};