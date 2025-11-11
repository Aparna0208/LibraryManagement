#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include "book.h"
#include "member.h"
#include "library.h"
#include "lms_utilities.h"

static AuthorName parse_author_name(const std::string& full_name) {
    std::stringstream ss(full_name);
    std::string first_name;
    std::string last_name;
    
    ss >> first_name;
    
    std::string remaining_name;
    std::getline(ss, remaining_name);
    
    size_t first_char = remaining_name.find_first_not_of(" \t");
    if (std::string::npos == first_char) {
        last_name = "";
    } else {
        last_name = remaining_name.substr(first_char);
    }

    if (first_name.empty()) {
        if (last_name.empty()) {
            return {"", ""};
        }
    } else if (last_name.empty()) {
        last_name = first_name;
        first_name = "";
    }
    
    return {first_name, last_name};
}

int read_list_of_books(Library& library, const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open such a file");
    }

    std::string title;
    std::string author_full_name;
    std::string isbn;
    int successfully_read_count = 0;

    while (std::getline(ifs, title) && 
           std::getline(ifs, author_full_name) && 
           std::getline(ifs, isbn)) {
        
        try {
            AuthorName author_name = parse_author_name(author_full_name);
            
            Book new_book(title, author_name.first_name, author_name.last_name, isbn);
            library.add_book(new_book);
            successfully_read_count++;
        } catch (const std::invalid_argument& e) {
        }
    }

    return successfully_read_count;
}

int read_list_of_members(Library& library, const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open a file that does not exist");
    }

    std::string member_full_name;
    int successfully_read_count = 0;
    int current_id = 1000;

    while (std::getline(ifs, member_full_name)) {
        if (member_full_name.empty()) {
            continue;
        }

        std::stringstream ss(member_full_name);
        std::string first_name;
        std::string last_name;
        
        ss >> first_name;
        
        std::string remaining_name;
        std::getline(ss, remaining_name);
        
        size_t first_char = remaining_name.find_first_not_of(" \t");
        if (std::string::npos == first_char) {
            last_name = "";
        } else {
            last_name = remaining_name.substr(first_char);
        }

        if (last_name.empty() && !first_name.empty()) {
            last_name = first_name;
            first_name = "";
        }
        
        try {
            Member new_member(first_name, last_name, current_id);
            library.register_member(new_member);
            successfully_read_count++;
            current_id++;
        } catch (const std::invalid_argument& e) {
        }
    }

    return successfully_read_count;
}

int read_list_of_borrowed_books(Library& library, const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open a fake file");
    }

    std::string line;
    int successfully_processed_count = 0;

    while (std::getline(ifs, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string isbn;
        int member_id;
        std::string message;

        if (ss >> isbn >> member_id) {
            if (library.borrow_book(isbn, member_id, message)) {
                successfully_processed_count++;
            }
        }
    }

    return successfully_processed_count;
}

int read_list_of_returned_books(Library& library, const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        throw std::runtime_error("Cannot open this jar of pickles");
    }

    std::string isbn;
    int successfully_processed_count = 0;

    while (std::getline(ifs, isbn)) {
        if (isbn.empty()) {
            continue;
        }
        std::string message;
        if (library.return_book(isbn, message)) {
            successfully_processed_count++;
        }
    }

    return successfully_processed_count;
}