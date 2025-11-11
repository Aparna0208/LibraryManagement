// provided. do not change. do not submit.
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "library.h"
#include "lms_utilities.h"

int process_library(const std::vector<std::string>& filenames) {
    const std::string& library_books = filenames[0];
    const std::string& library_members = filenames[1];
    const std::string& borrowed_books = filenames[2];
    const std::string& returned_books = filenames[3];

    Library library;

    // Add books to the library
    read_list_of_books(library, library_books);

    // Register members
    read_list_of_members(library, library_members);

    // Display members
    std::cout << "\nMembers of the library:" << std::endl;
    library.display_library_members();

    // Display all available books before borrowing:
    std::cout << "\nAvailable books in the library:" << std::endl;
    library.display_available_books();

    // Borrow books
    std::cout << "\nBorrowing books..." << std::endl;
    read_list_of_borrowed_books(library, borrowed_books);

    // Display all available books after borrowing
    std::cout << "\nAvailable books in the library after borrowing:" << std::endl;
    library.display_available_books();

    // Return books
    std::cout << "\nReturning books..." << std::endl;
    read_list_of_returned_books(library, returned_books);

    // Display all available books after returning
    std::cout << "\nAvailable books in the library after returning:" << std::endl;
    library.display_available_books();

    return 0;
}

void print_usage() {
    std::cout << "\nThe program requires these 4 files:\n";
    std::cout << " 1. A file containing a list of library books\n";
    std::cout << "    in this format: \n";
    std::cout << "    - the first line contains the book title\n";
    std::cout << "    - the second line contains the author's first name\n";
    std::cout << "      and last name separated by space\n";
    std::cout << "    - the third line contains the book ISBN\n";
    std::cout << " 2. A file containing a list of members' names,\n";
    std::cout << "    each name in a separate line\n";
    std::cout << " 3. A file containing a list of borrowed books\n";
    std::cout << "    in this format in each line:\n";
    std::cout << "    - the book ISBN\n";
    std::cout << "    - the member's ID borrowing the book\n";
    std::cout << " 4. A file containing a list of returned books\n";
    std::cout << "    with the book ISBN in each line\n";
    std::cout << " If they are not provided (empty line), default files are used.\n";
    std::cout << std::endl;
}

int main(int argc, char**) {
    if (argc > 1) {
        print_usage();
    }

    std::vector<std::string> defaults = {
        "library_books_1.txt",
        "library_members_1.txt",
        "borrowed_books_1.txt",
        "returned_books_1.txt",
    };
    std::vector<std::string> filenames;

    for (size_t count = 0; count < 4; count += 1) {
        std::string filename{};
        std::getline(std::cin, filename);
        if (filename.empty()) {
            filenames.push_back(defaults[count]);
        } else {
            filenames.push_back(filename);
        }
    }

    try {
        return process_library(filenames);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Uncaught exception" << std::endl;
        return 99;
    }

    return 0;
}
