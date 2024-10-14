#include <iostream>
#include <string>
using namespace std;

// Base class: Item
class Item {
protected:
    string title;
    string author;
    int itemID;

public:
    // Default constructor
    Item() : title(""), author(""), itemID(0) {}

    // Parameterized constructor
    Item(string t, string a, int id) : title(t), author(a), itemID(id) {}

    // Accessors and mutators for title, author, and itemID
    string getTitle() const { return title; }
    void setTitle(const string& t) { title = t; }

    string getAuthor() const { return author; }
    void setAuthor(const string& a) { author = a; }

    int getItemID() const { return itemID; }
    void setItemID(int id) { itemID = id; }

    // Display function
    virtual void displayDetails() const {
        cout << "Item ID: " << itemID << ", Title: " << title << ", Author: " << author << "\n";
    }
};

// Book class definition (Single Inheritance from Item)
class Book : public Item {
private:
    bool isBorrowed;

public:
    // Default constructor
    Book() : Item(), isBorrowed(false) {}

    // Parameterized constructor
    Book(string t, string a, int id) : Item(t, a, id), isBorrowed(false) {}

    // Accessor and mutator for isBorrowed
    bool getIsBorrowed() const { return isBorrowed; }
    void setIsBorrowed(bool borrowed) { isBorrowed = borrowed; }

    // Function to borrow a book
    void borrowBook() {
        if (!isBorrowed) {
            isBorrowed = true;
            cout << title << " has been borrowed.\n";
        } else {
            cout << title << " is already borrowed.\n";
        }
    }

    // Function to return a book
    void returnBook() {
        if (isBorrowed) {
            isBorrowed = false;
            cout << title << " has been returned.\n";
        } else {
            cout << title << " was not borrowed.\n";
        }
    }

    // Function to display book details
    void displayDetails() const override {
        Item::displayDetails();
        cout << (isBorrowed ? " (Borrowed)\n" : " (Available)\n");
    }
};


// Magazine class definition (Hierarchical Inheritance from Item)
class Magazine : public Item {
private:
    int issueNumber;

public:
    // Default constructor
    Magazine() : Item(), issueNumber(0) {}

    // Parameterized constructor
    Magazine(string t, string a, int id, int issue) : Item(t, a, id), issueNumber(issue) {}

    // Accessor and mutator for issueNumber
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
        Item::displayDetails();
        cout << "Issue Number: " << issueNumber << "\n";
    }
};

// Library class definition
class Library {
private:
    Item** items;      // Changed from Book** to Item** to store both Books and Magazines
    int itemCount;
    int maxItems;

    // Static variable to count the number of Library instances
    static int libraryCount;

public:
    // Default constructor
    Library(int max) : itemCount(0), maxItems(max) {
        items = new Item*[maxItems];  // Dynamically allocate array of pointers
        for (int i = 0; i < maxItems; ++i) {
            items[i] = nullptr;
        }
        ++libraryCount;
    }

    // Copy constructor
    Library(const Library& other) : itemCount(other.itemCount), maxItems(other.maxItems) {
        items = new Item*[maxItems];
        for (int i = 0; i < itemCount; ++i) {
            items[i] = other.items[i]->clone();  // Use clone method for polymorphic copy
        }
        ++libraryCount;
        cout << "Copy constructor called for Library.\n";
    }

    // Destructor
    ~Library() {
        for (int i = 0; i < itemCount; ++i) {
            delete items[i];  // Free each allocated Item object
        }
        delete[] items;  // Free the array of Item pointers
        --libraryCount;
        cout << "Destructor called for Library.\n";
    }

    // Overloaded function to add a Book to the library
    void addItem(const string& title, const string& author, int id) {
        if (itemCount < maxItems) {
            items[itemCount] = new Book(title, author, id);  // Allocate a new Book
            itemCount++;
            cout << "Book added: " << title << "\n";
        } else {
            cout << "Library is full, cannot add more books.\n";
        }
    }

    // Overloaded function to add a Magazine to the library
    void addItem(const string& title, const string& author, int id, int issueNumber) {
        if (itemCount < maxItems) {
            items[itemCount] = new Magazine(title, author, id, issueNumber);  // Allocate a new Magazine
            itemCount++;
            cout << "Magazine added: " << title << "\n";
        } else {
            cout << "Library is full, cannot add more items.\n";
        }
    }

    // Function to remove an item from the library
    void removeItem(const string& title) {
        for (int i = 0; i < itemCount; ++i) {
            if (items[i]->getTitle() == title) {
                delete items[i];  // Free the memory of the Item object
                for (int j = i; j < itemCount - 1; ++j) {
                    items[j] = items[j + 1];
                }
                items[itemCount - 1] = nullptr;
                itemCount--;
                cout << "Item removed: " << title << "\n";
                return;
            }
        }
        cout << "Item not found: " << title << "\n";
    }

    // Function to display all items in the library
    void displayItems() const {
        cout << "Library Collection:\n";
        for (int i = 0; i < itemCount; ++i) {
            items[i]->displayDetails();
        }
    }

    // Function to borrow a book from the library
    void borrowItem(const string& title) {
        for (int i = 0; i < itemCount; ++i) {
            Book* book = dynamic_cast<Book*>(items[i]);
            if (book && book->getTitle() == title) {
                book->borrowBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Function to return a book to the library
    void returnItem(const string& title) {
        for (int i = 0; i < itemCount; ++i) {
            Book* book = dynamic_cast<Book*>(items[i]);
            if (book && book->getTitle() == title) {
                book->returnBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Static function to get the count of Library instances
    static int getLibraryCount() {
        return libraryCount;
    }
};

// Initialize static variable
int Library::libraryCount = 0;

int main() {
    Library* myLibrary = new Library(25); // Dynamically allocate Library object
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
                myLibrary->borrowItem(title);
                break;
            case 4:
                cout << "Enter book title to return: ";
                getline(cin, title);
                myLibrary->returnItem(title);
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

    // Free the dynamically allocated Library object
    delete myLibrary;

    return 0;
}
