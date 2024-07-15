#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

// Book class
class Book {
public:
    std::string title;
    std::string author;
    std::string isbn;
    std::string category;
    bool isAvailable;

    Book(std::string t, std::string a, std::string i, std::string c)
        : title(t), author(a), isbn(i), category(c), isAvailable(true) {}
};

// LibraryPatron class
class LibraryPatron {
public:
    std::string name;
    int patronID;
    std::vector<Book*> borrowedBooks;

    LibraryPatron(std::string n, int id)
        : name(n), patronID(id) {}

    void borrowBook(Book* book) {
        if (book->isAvailable) {
            borrowedBooks.push_back(book);
            book->isAvailable = false;
            std::cout << "Book borrowed successfully.\n";
        } else {
            std::cout << "Book is not available.\n";
        }
    }

    void returnBook(Book* book) {
        auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), book);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            book->isAvailable = true;
            std::cout << "Book returned successfully.\n";
        } else {
            std::cout << "Book not found in borrowed list.\n";
        }
    }
};

// Library class
class Library {
private:
    std::list<Book> books;
    std::list<LibraryPatron> patrons;

public:
    void addBook(const Book& book) {
        books.push_back(book);
        std::cout << "Book added successfully.\n";
    }

    void displayBooks() const {
        for (const auto& book : books) {
            std::cout << "Title: " << book.title << ", Author: " << book.author
                      << ", ISBN: " << book.isbn << ", Category: " << book.category
                      << ", Status: " << (book.isAvailable ? "Available" : "Checked out") << '\n';
        }
    }

    Book* findBookByISBN(const std::string& isbn) {
        for (auto& book : books) {
            if (book.isbn == isbn) {
                return &book;
            }
        }
        std::cout << "Book not found.\n";
        return nullptr;
    }

    void displayBooksByCategory(const std::string& category) const {
        for (const auto& book : books) {
            if (book.category == category) {
                std::cout << "Title: " << book.title << ", Author: " << book.author
                          << ", ISBN: " << book.isbn
                          << ", Status: " << (book.isAvailable ? "Available" : "Checked out") << '\n';
            }
        }
    }

    void addPatron(const LibraryPatron& patron) {
        patrons.push_back(patron);
        std::cout << "Patron added successfully.\n";
    }

    LibraryPatron* findPatronByID(int id) {
        for (auto& patron : patrons) {
            if (patron.patronID == id) {
                return &patron;
            }
        }
        std::cout << "Patron not found.\n";
        return nullptr;
    }
};

int main() {
    Library library;
    bool running = true;

    while (running) {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Check if Book is Available\n";
        std::cout << "3. Borrow Book\n";
        std::cout << "4. Return Book\n";
        std::cout << "5. List Books by Category\n";
        std::cout << "6. Add Patron\n";
        std::cout << "7. End\n";
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::cin.ignore();
                std::string title, author, isbn, category;
                std::cout << "Enter title: ";
                std::getline(std::cin, title);
                std::cout << "Enter author: ";
                std::getline(std::cin, author);
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                std::cout << "Enter category: ";
                std::getline(std::cin, category);
                library.addBook(Book(title, author, isbn, category));
                break;
            }
            case 2: {
                std::cin.ignore();
                std::string isbn;
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                Book* book = library.findBookByISBN(isbn);
                if (book) {
                    std::cout << "Title: " << book->title << ", Author: " << book->author
                              << ", ISBN: " << book->isbn << ", Category: " << book->category
                              << ", Status: " << (book->isAvailable ? "Available" : "Checked out") << '\n';
                }
                break;
            }
            case 3: {
                std::cin.ignore();
                std::string isbn;
                int patronID;
                std::cout << "Enter Patron ID: ";
                std::cin >> patronID;
                std::cin.ignore();
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                LibraryPatron* patron = library.findPatronByID(patronID);
                Book* book = library.findBookByISBN(isbn);
                if (patron && book) {
                    patron->borrowBook(book);
                }
                break;
            }
            case 4: {
                std::cin.ignore();
                std::string isbn;
                int patronID;
                std::cout << "Enter Patron ID: ";
                std::cin >> patronID;
                std::cin.ignore();
                std::cout << "Enter ISBN: ";
                std::getline(std::cin, isbn);
                LibraryPatron* patron = library.findPatronByID(patronID);
                Book* book = library.findBookByISBN(isbn);
                if (patron && book) {
                    patron->returnBook(book);
                }
                break;
            }
            case 5: {
                std::cin.ignore();
                std::string category;
                std::cout << "Enter category: ";
                std::getline(std::cin, category);
                library.displayBooksByCategory(category);
                break;
            }
            case 6: {
                std::cin.ignore();
                std::string name;
                int patronID;
                std::cout << "Enter patron name: ";
                std::getline(std::cin, name);
                std::cout << "Enter patron ID: ";
                std::cin >> patronID;
                std::cin.ignore();
                library.addPatron(LibraryPatron(name, patronID));
                break;
            }
            case 7: {
                running = false;
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    return 0;
}
