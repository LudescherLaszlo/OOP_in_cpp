#pragma once
#include "Coat.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include "Validator.h"

class Repo {
protected:
    std::vector<Coat> coats;
    string fileName;
public:
    Repo(string fileName) {
        this->fileName = fileName;
        this->load();
    }
    ~Repo() = default;

    void addCoat(const Coat& c);
    void removeCoat(const string& size, const string& photo);
    void updateCoat(const string& size, const string& color, int price, int quantity, const string& photo);

    std::vector<Coat> getCoats() const { return coats; }
    size_t getSize() const { return coats.size(); }
    virtual void save();
    void load();
    virtual string filePath() const { return this->fileName; }

};

class CSVRepo : public Repo {
public:
    CSVRepo(const string& fileName) : Repo(fileName) {}

    void save() override {
        std::ofstream file(this->fileName + ".csv");
        file << "Size,Color,Price,Quantity,Photo\n";
        for (const Coat& c : this->getCoats()) {
            file << c; 
        }
    }

    string filePath() const {
        return this->fileName + ".csv";
    }
};

class HTMLRepo : public Repo {
public:
    HTMLRepo(const string& fileName) : Repo(fileName) {}

    void save() override {
        std::ofstream file(this->fileName + ".html");
        file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Coats</title>\n</head>\n<body>\n";
        file << "<table border=\"1\">\n";
        file << "<tr><th>Size</th><th>Color</th><th>Price</th><th>Quantity</th><th>Photo</th></tr>\n";
        for (const Coat& c : this->getCoats()) {
            file << "<tr>";
            file << "<td>" << c.getSize() << "</td>";
            file << "<td>" << c.getColor() << "</td>";
            file << "<td>" << c.getPrice() << "</td>";
            file << "<td>" << c.getQuantity() << "</td>";
            file << "<td><a href=\"" << c.getPhoto() << "\">Link</a></td>";
            file << "</tr>\n";
        }
        file << "</table>\n</body>\n</html>";
    }

    string filePath() const {
        return this->fileName + ".html";
    }
};