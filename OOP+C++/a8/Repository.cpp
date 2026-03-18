#include "Repository.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Validator.h"

using namespace std;

void Repo::addCoat(const Coat& c)
{
    if (Validator::DoesCoatExist(this->coats, c.getSize(), c.getPhoto()))
        throw RepoException("Coat already exists!");

    this->coats.push_back(c);
}

void Repo::removeCoat(const string& size, const string& photo)
{
    auto it = find_if(coats.begin(), coats.end(),
        [&size, &photo](const Coat& c) {
            return c.getSize() == size && c.getPhoto() == photo;
        });

    if (it != coats.end()) {
        coats.erase(it);
    }
    else {
        throw RepoException("Coat not found for removal!");
    }
}

void Repo::updateCoat(const string& size, const string& color, int price, int quantity, const string& photo)
{
    auto it = find_if(coats.begin(), coats.end(),
        [&size, &photo](const Coat& c) {
            return c.getSize() == size && c.getPhoto() == photo;
        });

    if (it != coats.end()) {
        it->setPrice(price);
        it->setQuantity(quantity);
        it->setColor(color);
    }
    else {
        throw RepoException("Coat not found for update!");
    }
}

void Repo::save()
{
    ofstream fout(this->fileName);
    for (const Coat& c : this->coats) {
        fout << c;
    }
}

void Repo::load()
{
    ifstream fin(this->fileName);
    Coat c;
    while (fin >> c) {
        this->coats.push_back(c);
    }
}
