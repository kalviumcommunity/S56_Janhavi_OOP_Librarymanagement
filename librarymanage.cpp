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
    Item() : title(""), author(""), itemID(0) {}
    Item(string t, string a, int id) : title(t), author(a), itemID(id) {}

    string getTitle() const { return title; }
    void setTitle(const string& t) { title = t; }

    string getAuthor() const { return author; }
    void setAuthor(const string& a) { author = a; }

    int getItemID() const { return itemID; }
    void setItemID(int id) { itemID = id; }

    virtual void displayDetails() const = 0;
    virtual ~Item() = default; // Virtual destructor for proper cleanup
};

// Book class definition
class Book : public Item {
public:
    Book() : Item() {}
    Book(string t, string a, int id) : Item(t, a, id) {}

    void displayDetails() const override {
        cout << "Item ID: " << itemID << ", Title: " << title << ", Author: " << author << "\n";
    }
};

// Magazine class definition
class Magazine : public Item {
private:
    int issueNumber;

public:
    Magazine() : Item(), issueNumber(0) {}
    Magazine(string t, string a, int id, int issue) : Item(t, a, id), issueNumber(issue) {}

    int getIssueNumber() const { return issueNumber; }
    void setIssueNumber(int issue) { issueNumber = issue; }

    void displayDetails() const override {
        cout << "Item ID: " << itemID << ", Title: " << title << ", Author: " << author 
             << ", Issue Number: " << issueNumber << "\n";
    }
};

// New class: Newspaper, extending Item
class Newspaper : public Item {
private:
    string date;

public:
    Newspaper(string t, string a, int id, string d) : Item(t, a, id), date(d) {}

    void displayDetails() const override {
        cout << "Item ID: " << itemID << ", Title: " << title << ", Author: " << author 
             << ", Date: " << date << "\n";
    }
};

// BorrowManager class to handle borrowing functionality
class BorrowManager {
public:
    void borrowItem(Book* book) {
        cout << book->getTitle() << " has been borrowed.\n";
    }

    void returnItem(Book* book) {
        cout << book->getTitle() << " has been returned.\n";
    }
};

// Library class definition
class Library {
private:
    vector<Item*> items;
    static int libraryCount;

public:
    Library() { ++libraryCount; }

    ~Library() {
        for (Item* item : items) {
            delete item;
        }
        --libraryCount;
        cout << "Destructor called for Library.\n";
    }

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

    static int getLibraryCount() {
        return libraryCount;
    }
};

// Initialize static variable
int Library::libraryCount = 0;

int main() {
    Library myLibrary;
    BorrowManager borrowManager;
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Add Magazine\n";
        cout << "3. Add Newspaper\n";
        cout << "4. Remove Item\n";
        cout << "5. Borrow Book\n";
        cout << "6. Return Book\n";
        cout << "7. Display Items\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        string title, author, date;
        int id, issueNumber;

        switch (choice) {
            case 1:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter author name: ";
                getline(cin, author);
                myLibrary.addItem(new Book(title, author, id));
                break;
            case 2:
                cout << "Enter magazine ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter magazine title: ";
                getline(cin, title);
                cout << "Enter author name: ";
                getline(cin, author);
                cout << "Enter issue number: ";
                cin >> issueNumber;
                cin.ignore();
                myLibrary.addItem(new Magazine(title, author, id, issueNumber));
                break;
            case 3:
                cout << "Enter newspaper ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter newspaper title: ";
                getline(cin, title);
                cout << "Enter author name: ";
                getline(cin, author);
                cout << "Enter date: ";
                getline(cin, date);
                myLibrary.addItem(new Newspaper(title, author, id, date));
                break;
            case 4:
                cout << "Enter item title to remove: ";
                getline(cin, title);
                myLibrary.removeItem(title);
                break;
            case 5:
                cout << "Enter book title to borrow: ";
                getline(cin, title);
                for (Item* item : myLibrary.getItems()) {
                    Book* book = dynamic_cast<Book*>(item);
                    if (book && book->getTitle() == title) {
                        borrowManager.borrowItem(book);
                        break;
                    }
                }
                break;
            case 6:
                cout << "Enter book title to return: ";
                getline(cin, title);
                for (Item* item : myLibrary.getItems()) {
                    Book* book = dynamic_cast<Book*>(item);
                    if (book && book->getTitle() == title) {
                        borrowManager.returnItem(book);
                        break;
                    }
                }
                break;
            case 7:
                myLibrary.displayItems();
                break;
            case 8:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}
