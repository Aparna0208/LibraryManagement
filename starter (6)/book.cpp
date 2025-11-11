#include <stdexcept>
#include <string>
#include <iostream>
#include "book.h"
static void validate_book_params(const std::string& title, const std::string& isbn, 
                                 const std::string& author_first, const std::string& author_last) {
    if (title.empty()) throw std::invalid_argument("Invalid title");
    for (char c : title) {
      if (!std::isalpha(c) && !std::isspace(static_cast<unsigned char>(c)) && c != ':' && c != '-') {
        throw std::invalid_argument("Invalid title");
      }
    }
    if (author_first.empty() && author_last.empty()) {
        throw std::invalid_argument("Invalid author");
    }
    for (char c : author_first + author_last) {
        if (!std::isalpha(static_cast<unsigned char>(c))) {
         throw std::invalid_argument("Invalid author");
        }
    }
   if (!(isbn.size() == 10 || isbn.size() == 13)) {
        throw std::invalid_argument("Invalid ISBN");
   }



   for (char c : isbn) {
        if (!std::isdigit(c)) {
            throw std::invalid_argument("Invalid ISBN");


        }
   }

}



Book::Book(std::string title,
           std::string author_first_name, 
           std::string author_last_name,
           std::string isbn,
           bool available)
    : title(title),
      author(AuthorName{author_first_name, author_last_name}), 
      isbn(isbn),
      available(available) { validate_book_params(title, isbn, author_first_name, author_last_name);
}

Book::Book(std::string title,
           AuthorName author,
           std::string isbn,
           bool available)
    : title(title),
      author(author), 
      isbn(isbn),
      available(available) {
          validate_book_params(title, isbn, author.first_name, author.last_name);
}
std::string Book::get_title() const {
   // TODO(student)
   return title;
}

AuthorName Book::get_author() const {

   return author;
}

std::string Book::get_isbn() const {
  
   return isbn;
}

bool Book::is_available() const {
   return available;
}

bool Book::borrow_book() {
 
   if (available) {
        available = false;  
        return true;        
    }


    return false;  
}

bool Book::return_book() {
   if (!available) {
        available = true;  
        return true;        
    }
    return false;        
}

std::ostream& operator<<(std::ostream& os, const Book& b) {
    os << "title: \"" << b.get_title() << "\" by ";
    
    if (!b.get_author().first_name.empty()) {
        os << b.get_author().first_name << " ";
    }
    
    os << b.get_author().last_name
       << ", isbn: " << b.get_isbn();
    

            return os;
}