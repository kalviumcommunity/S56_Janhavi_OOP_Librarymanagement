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
    void displayDetails() const {
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
    void displayDetails() const {
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

    // Function to display magazine details
    void displayDetails() const {
        Item::displayDetails();
        cout << "Issue Number: " << issueNumber << "\n";
    }
};

// Library class definition (unchanged)
class Library {
private:
    Book** books;
    int bookCount;
    int maxBooks;

    // Static variable to count the number of Library instances
    static int libraryCount;

public:
    // Default constructor
    Library(int max) : bookCount(0), maxBooks(max) {
        books = new Book*[maxBooks];  // Dynamically allocate array of pointers
        for (int i = 0; i < maxBooks; ++i) {
            books[i] = nullptr;
        }
        ++libraryCount;
    }

    // Copy constructor (if needed)
    Library(const Library& other) : bookCount(other.bookCount), maxBooks(other.maxBooks) {
        books = new Book*[maxBooks];
        for (int i = 0; i < bookCount; ++i) {
            books[i] = new Book(*other.books[i]);  // Use Book's copy constructor
        }
        ++libraryCount;
        cout << "Copy constructor called for Library.\n";
    }

    // Destructor
    ~Library() {
        for (int i = 0; i < bookCount; ++i) {
            delete books[i];  // Free each allocated Book object
        }
        delete[] books;  // Free the array of Book pointers
        --libraryCount;
        cout << "Destructor called for Library.\n";
    }

    // Function to add a book to the library
    void addBook(const string& title, const string& author, int id) {
        if (bookCount < maxBooks) {
            books[bookCount] = new Book(title, author, id);  // Allocate a new Book
            bookCount++;
            cout << "Book added: " << title << "\n";
        } else {
            cout << "Library is full, cannot add more books.\n";
        }
    }

    // Function to remove a book from the library
    void removeBook(const string& title) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i]->getTitle() == title) {
                delete books[i];  // Free the memory of the Book object
                for (int j = i; j < bookCount - 1; ++j) {
                    books[j] = books[j + 1];
                }
                books[bookCount - 1] = nullptr;
                bookCount--;
                cout << "Book removed: " << title << "\n";
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Function to display all books in the library
    void displayBooks() const {
        cout << "Library Collection:\n";
        for (int i = 0; i < bookCount; ++i) {
            books[i]->displayDetails();
        }
    }

    // Function to borrow a book from the library
    void borrowBook(const string& title) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i]->getTitle() == title) {
                books[i]->borrowBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Function to return a book to the library
    void returnBook(const string& title) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i]->getTitle() == title) {
                books[i]->returnBook();
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
        cout << "2. Remove Book\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Display Books\n";
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
                myLibrary->addBook(title, author, id);
                break;
            case 2:
                cout << "Enter book title to remove: ";
                getline(cin, title);
                myLibrary->removeBook(title);
                break;
            case 3:
                cout << "Enter book title to borrow: ";
                getline(cin, title);
                myLibrary->borrowBook(title);
                break;
            case 4:
                cout << "Enter book title to return: ";
                getline(cin, title);
                myLibrary->returnBook(title);
                break;
            case 5:
                myLibrary->displayBooks();
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

                // Create a Magazine object and display its details
                Magazine mag(title, author, id, issueNumber);
                mag.displayDetails();
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
