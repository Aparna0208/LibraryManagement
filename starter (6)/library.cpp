
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "library.h"
#include "lms_utilities.h"

void Library::add_book(Book book) {
    books.push_back(std::move(book));
}

void Library::register_member(Member member) {

    members.push_back(member);
}

bool Library::borrow_book(const std::string& isbn, int member_id, std::string& message) {
    Book* found_book = nullptr;
    for (Book& b : books) {
        if (b.get_isbn() == isbn) {
            found_book = &b;
            break;
        }
    }

    if (found_book == nullptr) {
        message = "Book ISBN: " + isbn + " not available";
        return false;
    }

    bool member_exists = false;
    for (const Member& m : members) {
        if (m.get_id() == member_id) {
            member_exists = true;
            break;
        }
    }

    std::stringstream ss;
    ss << member_id;
    std::string member_id_str = ss.str();

    if (!member_exists) {
        message = "Member " + member_id_str + " not found";
        return false;
    }

    if (found_book->is_available()) {
        bool borrowed = found_book->borrow_book();
        if (borrowed) {
            message = "Book ISBN: " + isbn + " borrowed by Member ID: " + member_id_str;
            return true;
        }
        message = "Book ISBN: " + isbn + " is already borrowed."; 
        return false;
    } else {
        message = "Book ISBN: " + isbn + " not available";
        return false;
    }
}

bool Library::return_book(const std::string& isbn, std::string& message) {
    Book* found_book = nullptr;
    for (Book& b : books) {
        if (b.get_isbn() == isbn) {
            found_book = &b;
            break;
        }
    }

    if (found_book == nullptr) {
        message = "Book ISBN: " + isbn + " not found";
        return false;
    }

    if (found_book->is_available()) {
        message = "Book ISBN: " + isbn + " still available (cannot be returned)";
        return false;
    } else {
        bool returned = found_book->return_book();
        if (returned) {
            message =  "Book \"" + found_book->get_title() + "\" returned";
            return true;
        }
        message = "Book \"" + found_book->get_title() + "\" failed to return";
        return false;
    }
}

void Library::display_available_books(std::ostream& os) {
    for (const auto& book : books) {
        if (book.is_available()) {
            os << book << std::endl;
        }
    }
}

void Library::display_library_members(std::ostream& os) {
    for (const auto& member : members) {
        os << member << std::endl;
    }
}

bool Library::is_book_available(const std::string& isbn) {
    for (const Book& b : books) {
        if (b.get_isbn() == isbn) {
            return b.is_available();
        }
    }
    return false;
}