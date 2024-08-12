#include <iostream>
#include <string>
using namespace std;

const int MAX_BOOKS = 100;  // Maximum number of books the library can hold

// Book class definition
class Book {
    string title;
    string author;
    bool isBorrowed;

public:
    Book() : title(""), author(""), isBorrowed(false) {}

    Book(string t, string a) : title(t), author(a), isBorrowed(false) {}

    void borrowBook() {
        if (!this->isBorrowed) {
            this->isBorrowed = true;
            cout << this->title << " has been borrowed.\n";
        } else {
            cout << this->title << " is already borrowed.\n";
        }
    }

    void returnBook() {
        if (this->isBorrowed) {
            this->isBorrowed = false;
            cout << this->title << " has been returned.\n";
        } else {
            cout << this->title << " was not borrowed.\n";
        }
    }

    void displayDetails() const {
        if (!this->title.empty()) {
            cout << "Title: " << this->title << ", Author: " << this->author;
            if (this->isBorrowed) {
                cout << " (Borrowed)\n";
            } else {
                cout << " (Available)\n";
            }
        }
    }

    string getTitle() const {
        return this->title;
    }

    bool isBookExists() const {
        return !this->title.empty();
    }
};

// Library class definition
class Library {
    Book books[MAX_BOOKS];
    int bookCount;

public:
    Library() : bookCount(0) {}

    void addBook(string title, string author) {
        if (this->bookCount < MAX_BOOKS) {
            this->books[this->bookCount] = Book(title, author);
            this->bookCount++;
            cout << "Book added: " << title << "\n";
        } else {
            cout << "Library is full, cannot add more books.\n";
        }
    }

    void removeBook(string title) {
        for (int i = 0; i < this->bookCount; ++i) {
            if (this->books[i].getTitle() == title) {
                this->books[i] = Book();
                cout << "Book removed: " << title << "\n";
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    void displayBooks() const {
        cout << "Library Collection:\n";
        for (int i = 0; i < this->bookCount; ++i) {
            this->books[i].displayDetails();
        }
    }

    void borrowBook(string title) {
        for (int i = 0; i < this->bookCount; ++i) {
            if (this->books[i].getTitle() == title && this->books[i].isBookExists()) {
                this->books[i].borrowBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    void returnBook(string title) {
        for (int i = 0; i < this->bookCount; ++i) {
            if (this->books[i].getTitle() == title && this->books[i].isBookExists()) {
                this->books[i].returnBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }
};

int main() {
    Library myLibrary;
    int choice;
    
    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Display Books\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        string title, author;

        switch (choice) {
            case 1:
                cout << "Enter book title: ";
                cin.ignore(); 
                getline(cin, title);
                cout << "Enter author name: ";
                getline(cin, author);
                myLibrary.addBook(title, author);
                break;
            case 2:
                cout << "Enter book title to remove: ";
                cin.ignore();
                getline(cin, title);
                myLibrary.removeBook(title);
                break;
            case 3:
                cout << "Enter book title to borrow: ";
                cin.ignore();
                getline(cin, title);
                myLibrary.borrowBook(title);
                break;
            case 4:
                cout << "Enter book title to return: ";
                cin.ignore();
                getline(cin, title);
                myLibrary.returnBook(title);
                break;
            case 5:
                myLibrary.displayBooks();
                break;
            case 6:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
