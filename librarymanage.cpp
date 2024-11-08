#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Abstract Base class: Item
class Item {
protected:
    string title;
    string author;
    int itemID;

public:
    Item(string t = "", string a = "", int id = 0) : title(t), author(a), itemID(id) {}

    virtual string getTitle() const { return title; }
    virtual void displayDetails() const = 0;
    virtual ~Item() = default;
};

// Base class for items that can be borrowed
class Borrowable : public Item {
private:
    bool isBorrowed;

public:
    Borrowable(string t, string a, int id) : Item(t, a, id), isBorrowed(false) {}

    bool getIsBorrowed() const { return isBorrowed; }
    void borrow() { isBorrowed = true; }
    void returnItem() { isBorrowed = false; }
};

// Book class, extending Borrowable
class Book : public Borrowable {
public:
    Book(string t, string a, int id) : Borrowable(t, a, id) {}

    void displayDetails() const override {
        cout << "Book - ID: " << itemID << ", Title: " << title 
             << ", Author: " << author << ", Status: " 
             << (getIsBorrowed() ? "Borrowed" : "Available") << "\n";
    }
};
// Magazine class definition (Hierarchical Inheritance from Item)

// Magazine class, also Borrowable
class Magazine : public Borrowable {
class Magazine : public Item {

private:
    int issueNumber;

public:

    Magazine(string t, string a, int id, int issue) : Borrowable(t, a, id), issueNumber(issue) {}
    Magazine() : Item(), issueNumber(0) {}
    Magazine(string t, string a, int id, int issue) : Item(t, a, id), issueNumber(issue) {}

    int getIssueNumber() const { return issueNumber; }
    void setIssueNumber(int issue) { issueNumber = issue; }
    // Function to check if the book exists (is not empty)
    bool isBookExists() const {
        return !title.empty();
    // Function to get the title of the book
    string getTitle() const {
        return this->title;
    }

    // Function to check if the book exists (is not empty)
    bool isBookExists() const {
        return !this->title.empty();
    }


    // Function to display magazine details
    void displayDetails() const override {
        cout << "Magazine - ID: " << itemID << ", Title: " << title 
             << ", Author: " << author << ", Issue: " << issueNumber 
             << ", Status: " << (getIsBorrowed() ? "Borrowed" : "Available") << "\n";
    }
};

// Newspaper class that does not extend Borrowable (cannot be borrowed)
class Newspaper : public Item {
private:
    string date;

public:
    Newspaper(string t, string a, int id, string d) : Item(t, a, id), date(d) {}

    void displayDetails() const override {
        cout << "Newspaper - ID: " << itemID << ", Title: " << title 
             << ", Author: " << author << ", Date: " << date << "\n";
    }
};

// BorrowManager, managing any item that extends Borrowable
class BorrowManager {
public:
    void borrowItem(Borrowable* item) {
        if (item->getIsBorrowed()) {
            cout << item->getTitle() << " is already borrowed.\n";
        } else {
            item->borrow();
            cout << item->getTitle() << " has been borrowed.\n";
        }
    }

    void returnItem(Borrowable* item) {
        if (!item->getIsBorrowed()) {
            cout << item->getTitle() << " is already available.\n";
        } else {
            item->returnItem();
            cout << item->getTitle() << " has been returned.\n";
        }
    }
};

// LibraryManager class definition to manage library items
class LibraryManager {
private:
    vector<Item*> items;

public:
    void addItem(Item* item) {
        items.push_back(item);
        cout << "Item added: " << item->getTitle() << "\n";
    }

    void removeItem(const string& title) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getTitle() == title) {
                delete *it;
                items.erase(it);
                cout << "Item removed: " << title << "\n";
                return;
            }
        }
        cout << "Item not found: " << title << "\n";
    }

    void displayItems() const {
        cout << "Library Collection:\n";
        for (const Item* item : items) {
            item->displayDetails();
        }
    }

    ~LibraryManager() {
        for (Item* item : items) {
            delete item;
        }
        cout << "Library destroyed.\n";
    }
};

// Main function to demonstrate the library management system
int main() {
    LibraryManager myLibrary;
    BorrowManager borrowManager;

    // Adding different types of items to the library
    myLibrary.addItem(new Book("The Great Gatsby", "F. Scott Fitzgerald", 101));
    myLibrary.addItem(new Magazine("National Geographic", "Various Authors", 202, 2021));
    myLibrary.addItem(new Newspaper("The Times", "Times Staff", 303, "2023-11-08"));

    // Display all items
    myLibrary.displayItems();

    // Borrow and return a book
    cout << "\nBorrowing and returning 'The Great Gatsby':\n";
    for (Item* item : myLibrary.items) {
        if (Book* book = dynamic_cast<Book*>(item)) {
            borrowManager.borrowItem(book);
            borrowManager.returnItem(book);
        }
    }

    return 0;
}
