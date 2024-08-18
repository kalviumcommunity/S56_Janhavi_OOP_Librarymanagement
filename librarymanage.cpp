#include <iostream>
#include <string>
using namespace std;

const int MAX_BOOKS = 25;

// Book class definition
class Book {
private:
    string title;
    string author;
    bool isBorrowed;

    // Static variable to count the number of Book instances
    static int bookCount;

public:
    // Default constructor
    Book() : title(""), author(""), isBorrowed(false) {
        ++bookCount;
    }

    // Parameterized constructor
    Book(string t, string a) : title(t), author(a), isBorrowed(false) {
        ++bookCount;
    }

    // Destructor
    ~Book() {
        --bookCount;
    }

    // Accessor and mutator for title
    string getTitle() const {
        return title;
    }
    void setTitle(const string& t) {
        title = t;
    }

    // Accessor and mutator for author
    string getAuthor() const {
        return author;
    }
    void setAuthor(const string& a) {
        author = a;
    }

    // Accessor and mutator for isBorrowed
    bool getIsBorrowed() const {
        return isBorrowed;
    }
    void setIsBorrowed(bool borrowed) {
        isBorrowed = borrowed;
    }

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
        if (!title.empty()) {
            cout << "Title: " << title << ", Author: " << author;
            cout << (isBorrowed ? " (Borrowed)\n" : " (Available)\n");
        }
    }

    // Function to check if the book exists (is not empty)
    bool isBookExists() const {
        return !title.empty();
    }

    // Static function to get the count of Book instances
    static int getBookCount() {
        return bookCount;
    }
};

// Initialize static variable
int Book::bookCount = 0;

// Library class definition
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

    // Destructor
    ~Library() {
        for (int i = 0; i < bookCount; ++i) {
            delete books[i];  // Free each allocated Book object
        }
        delete[] books;  // Free the array of Book pointers
        --libraryCount;
    }

    // Function to add a book to the library
    void addBook(const string& title, const string& author) {
        if (bookCount < maxBooks) {
            books[bookCount] = new Book(title, author);  // Allocate a new Book
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
            if (books[i]->getTitle() == title && books[i]->isBookExists()) {
                books[i]->borrowBook();
                return;
            }
        }
        cout << "Book not found: " << title << "\n";
    }

    // Function to return a book to the library
    void returnBook(const string& title) {
        for (int i = 0; i < bookCount; ++i) {
            if (books[i]->getTitle() == title && books[i]->isBookExists()) {
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
    int numBooks;

    cout << "Enter the number of books you want to add to the Library: ";
    cin >> numBooks;
    cin.ignore();

    // Allocate an array of Book objects dynamically
    Book* myBooks = new Book[numBooks];

    // Taking input from the user for each book
    for (int i = 0; i < numBooks; ++i) {
        string title, author;

        cout << "\nEnter title for book " << i + 1 << ": ";
        getline(cin, title);
        cout << "Enter author for book " << i + 1 << ": ";
        getline(cin, author);

        myBooks[i].setTitle(title);
        myBooks[i].setAuthor(author);
    }

    // Display details of each book in the array
    cout << "\nDisplaying details of books in the array:\n";
    for (int i = 0; i < numBooks; ++i) {
        myBooks[i].displayDetails();
    }

    // Borrow a book from the array
    cout << "\nEnter the title of the book you want to borrow: ";
    string borrowTitle;
    getline(cin, borrowTitle);

    bool bookFound = false;
    for (int i = 0; i < numBooks; ++i) {
        if (myBooks[i].getTitle() == borrowTitle) {
            myBooks[i].borrowBook();
            bookFound = true;
            break;
        }
    }
    if (!bookFound) {
        cout << "Book not found in the array.\n";
    }

    // Display details again to see the updated status
    cout << "\nDisplaying details after borrowing a book:\n";
    for (int i = 0; i < numBooks; ++i) {
        myBooks[i].displayDetails();
    }

    // Return the borrowed book
    cout << "\nEnter the title of the book you want to return: ";
    string returnTitle;
    getline(cin, returnTitle);

    bookFound = false;
    for (int i = 0; i < numBooks; ++i) {
        if (myBooks[i].getTitle() == returnTitle) {
            myBooks[i].returnBook();
            bookFound = true;
            break;
        }
    }
    if (!bookFound) {
        cout << "Book not found in the array.\n";
    }

    // Display details again to see the final status
    cout << "\nDisplaying details after returning the book:\n";
    for (int i = 0; i < numBooks; ++i) {
        myBooks[i].displayDetails();
    }

    // Free the dynamically allocated array of Book objects
    delete[] myBooks;

    // Library management system menu
    Library* myLibrary = new Library(25); // Dynamically allocate Library object
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
        cin.ignore();

        string title, author;

        switch (choice) {
            case 1:
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter author name: ";
                getline(cin, author);
                myLibrary->addBook(title, author);
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
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);

    // Display the number of Book and Library instances
    cout << "\nTotal number of books created: " << Book::getBookCount() << endl;
    cout << "Total number of libraries created: " << Library::getLibraryCount() << endl;

    // Free the dynamically allocated Library object
    delete myLibrary;

    return 0;
}
