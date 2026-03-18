# Coat Store Management System 

A robust desktop application built in C++ with the Qt framework for managing a clothing store's inventory and facilitating a user shopping experience. This project demonstrates strong Object-Oriented Programming (OOP) principles, layered architecture, and the implementation of design patterns.


## Project Overview

This application features a dual-mode interface (Admin and User) that interacts with a persistent local database. 
* **Administrators** can manage the store's inventory (add, remove, update coats).
* **Users** can browse available coats (filtered by size), add items to a shopping basket, calculate their total price, and export their shopping basket to external files (CSV or HTML).

## Key Features

### Administrator Mode
* **CRUD Operations:** Add, delete, and update coats in the store's inventory.
* **Persistent Storage:** Inventory is automatically saved and loaded from a local text file.
* **Undo/Redo:** Fully functional multi-level Undo and Redo capabilities for all operations using the **Command Design Pattern**.

### User Mode
* **Smart Browsing:** Users can iterate through available coats one by one. If a specific size is entered, only coats of that size are displayed.
* **Shopping Basket:** Add displayed coats to a personal shopping basket and track the total price in real-time.
* **Data Export:** Choose to save the shopping basket as a `.csv` or `.html` file at startup.
* **External Integration:** Click a button to instantly open the saved basket file in the system's default application (e.g., Excel for CSV or Chrome for HTML) or view a coat's photo link directly in the browser.
* **Basket Undo/Redo:** Users can also undo or redo their actions of adding items to the basket.

## Technical Architecture & Concepts Used

* **Language:** C++ (using C++11/C++14 features like `std::unique_ptr`, lambda expressions, and STL algorithms).
* **GUI Framework:** Qt 6 (Widgets, Layouts, QTableView, QAbstractTableModel, QShortcut).
* **Layered Architecture:** The codebase is strictly divided into Domain (`Coat`), Repository (`Repo`, `CSVRepo`, `HTMLRepo`), Service/Controller (`Service`, `UserService`), and Presentation (`QTUI`) layers.
* **Polymorphism & Inheritance:** Implemented in the Repository layer to dynamically handle exporting to either `.csv` or `.html` formats using the same interface.
* **Command Design Pattern:** The `Action` base class and its derived classes (`ActionAdd`, `ActionRemove`, `ActionUpdate`) encapsulate requests as objects, allowing for clean and scalable Undo/Redo functionality.

## Getting Started

### Prerequisites
* A C++ compiler supporting C++14 or higher (e.g., MSVC, GCC).
* [Qt Framework](https://www.qt.io/download) (Qt 5 or Qt 6) configured with your IDE.
* Visual Studio or Qt Creator.

### Running the Project
1. Clone the repository.
2. Open the `.sln` file in Visual Studio (with the Qt Visual Studio Tools extension installed) or open the `.pro` / `CMakeLists.txt` file in Qt Creator.
3. Build and Run the project.
4. On startup, a prompt will ask if you want to use a **CSV** or **HTML** file for the shopping basket. Choose your preference and the main GUI will launch.
