#include <iostream>
#include <string>
using namespace std;

const int MAX_BOOKS = 25;  // Maximum number of books the library can hold

// Book class definition
class Book {
    // Private data members
    string title;
    string author;
    bool isBorrowed;

public:
    // Constructor
    Book() : title(""), author(""), isBorrowed(false) {}

    Book(string t, string a) : title(t), author(a), isBorrowed(false) {}

    // Member function to borrow the book
    void borrowBook() {
        if (!isBorrowed) {
            isBorrowed = true;
            cout << title << " has been borrowed.\n";
        } else {
            cout << title << " is already borrowed.\n";
        }
    }

    // Member function to return the book
    void returnBook() {
        if (isBorrowed) {
            isBorrowed = false;
            cout << title << " has been returned.\n";
        } else {
            cout << title << " was not borrowed.\n";
        }
    }

    // Member function to display book details
    void displayDetails() const {
        if (!title.empty()) {
            cout << "Title: " << title << ", Author: " << author;
            if (isBorrowed) {
                cout << " (Borrowed)\n";
            } else {
                cout << " (Available)\n";
            }
        }
    }

    // Getter function to access the title (used in Library class)
    string getTitle() const {
        return title;
    }

    // Function to check if a book exists
    bool isBookExists() const {
        return !title.empty();
    }
};

// Library class definition
class Library {
    // Private data members
    Book books[MAX_BOOKS];
    int bookCount;

public:
    // Constructor to initialize the library with no books
    Library() : bookCount(0) {}

    // Member function to add a book to the library
    void addBook(string title, string author) {
        if (bookCount < MAX_BOOKS) {
            books[bookCount] = Book(title, author);
            bookCount++;
            cout << "Book added: " << title << "\n";
        } else {
            cout << "Library is full, cannot add more books.\n";
        }
    }

    // Member function to remove a book from the library by title
    void removeBook(string title) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getTitle() == title) {
                books[i] = Book();  // Mark this book slot as empty
                cout << "Book removed: " << title << "\n";
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Member function to display all books in the library
    void displayBooks() const {
        cout << "Library Collection:\n";
        for (int i = 0; i < bookCount; ++i) {
            books[i].displayDetails();
        }
    }

    // Member function to borrow a book by title
    void borrowBook(string title) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getTitle() == title && books[i].isBookExists()) {
                books[i].borrowBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Member function to return a book by title
    void returnBook(string title) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i].getTitle() == title && books[i].isBookExists()) {
                books[i].returnBook();
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
                cin.ignore();  // To ignore the leftover newline character from previous input
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
