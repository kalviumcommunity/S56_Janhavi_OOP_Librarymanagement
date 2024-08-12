# Library Management System 📔

## Overview 📄
The **Library Management System** is a console-based application designed to manage a library's inventory and facilitate borrowing and returning books. Developed in C++, this project serves as a practical demonstration of key Object-Oriented Programming (OOP) principles, including encapsulation, abstraction, inheritance, and polymorphism. It provides a user-friendly interface for performing essential library management tasks through a text-based system.

## Objectives 🎯
The primary goal of this project is to create a functional, easy-to-use system that allows users to efficiently manage a library's collection. The application is designed to handle common library operations, making it an ideal example of how OOP principles can be applied to solve real-world problems.

## Language
- **C++**

## Features 🧾

### Book Management
- **Add New Books**: Allows users to add new books to the library's collection, including details such as title and author.
- **Remove Books**: Provides the functionality to remove books that are no longer available in the library.

### Borrowing and Returning
- **Borrow Books**: Users can borrow books, and the system will update the book's status to "borrowed".
- **Return Books**: Once a book is returned, its status is updated back to "available".

### Status Display
- **View Book Status**: Displays the current status of all books, showing which are available and which are currently borrowed.

## Use Cases 📕

1. **Add Book**  
   - *Description*: A user adds a new book to the library’s collection.
   - *Outcome*: The book is added to the inventory, and its details are stored in the system.

2. **Remove Book**  
   - *Description*: A user removes a book from the library’s collection.
   - *Outcome*: The book is removed from the inventory, and it is no longer available for borrowing.

3. **Borrow Book**  
   - *Description*: A user borrows a book from the library.
   - *Outcome*: The book’s status is updated to "borrowed", and it is no longer available for others until returned.

4. **Return Book**  
   - *Description*: A user returns a previously borrowed book.
   - *Outcome*: The book’s status is updated to "available", making it accessible to others.

5. **Display Status**  
   - *Description*: A user views the current status of all books in the library.
   - *Outcome*: The system displays a list of available books and those that are currently borrowed.
