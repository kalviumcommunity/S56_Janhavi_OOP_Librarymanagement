#include <iostream>
#include <string>
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
    Item** items;
    int itemCount;
    int maxItems;
    static int libraryCount;

public:
    Library(int max) : itemCount(0), maxItems(max) {
        items = new Item*[maxItems];
        for (int i = 0; i < maxItems; ++i) {
            items[i] = nullptr;
        }
        ++libraryCount;
    }

    ~Library() {
        for (int i = 0; i < itemCount; ++i) {
            delete items[i];
        }
        delete[] items;
        --libraryCount;
        cout << "Destructor called for Library.\n";
    }

    void addItem(const string& title, const string& author, int id) {
        if (itemCount < maxItems) {
            items[itemCount++] = new Book(title, author, id);
            cout << "Book added: " << title << "\n";
        } else {
            cout << "Library is full, cannot add more books.\n";
        }
    }

    void addItem(const string& title, const string& author, int id, int issueNumber) {
        if (itemCount < maxItems) {
            items[itemCount++] = new Magazine(title, author, id, issueNumber);
            cout << "Magazine added: " << title << "\n";
        } else {
            cout << "Library is full, cannot add more items.\n";
        }
    }

    void removeItem(const string& title) {
        for (int i = 0; i < itemCount; ++i) {
            if (items[i]->getTitle() == title) {
                delete items[i];
                for (int j = i; j < itemCount - 1; ++j) {
                    items[j] = items[j + 1];
                }
                items[--itemCount] = nullptr;
                cout << "Item removed: " << title << "\n";
                return;
            }
        }
        cout << "Item not found: " << title << "\n";
    }

    void displayItems() const {
        cout << "Library Collection:\n";
        for (int i = 0; i < itemCount; ++i) {
            items[i]->displayDetails();
        }
    }

    static int getLibraryCount() {
        return libraryCount;
    }
};

// Initialize static variable
int Library::libraryCount = 0;

int main() {
    Library* myLibrary = new Library(25);
    BorrowManager borrowManager;
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Item\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Display Items\n";
        cout << "6. Add Magazine\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        string title, author;
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
                myLibrary->addItem(title, author, id);
                break;
            case 2:
                cout << "Enter item title to remove: ";
                getline(cin, title);
                myLibrary->removeItem(title);
                break;
            case 3:
                cout << "Enter book title to borrow: ";
                getline(cin, title);
                borrowManager.borrowItem(dynamic_cast<Book*>(myLibrary));  
                break;
            case 4:
                cout << "Enter book title to return: ";
                getline(cin, title);
                borrowManager.returnItem(dynamic_cast<Book*>(myLibrary));
                break;
            case 5:
                myLibrary->displayItems();
                break;
            case 6:
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
                myLibrary->addItem(title, author, id, issueNumber);
                break;
            case 7:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    delete myLibrary;
    return 0;
}
