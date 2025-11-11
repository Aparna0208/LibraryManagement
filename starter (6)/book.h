// provided. do not change. do not submit.
#ifndef PROVIDED_BOOK_H_
#define PROVIDED_BOOK_H_

#include <iostream>
#include <string>

struct AuthorName {
    std::string first_name;
    std::string last_name;
};

class Book {
    std::string title;
    AuthorName author;
    std::string isbn;
    bool available;

 public:
    Book(std::string title,
         std::string author_first_name,
         std::string author_last_name,
         std::string isbn,
         bool available = true);
    Book(std::string title,
         AuthorName author,
         std::string isbn,
         bool available = true);
    std::string get_title() const;
    AuthorName get_author() const;
    std::string get_isbn() const;
    bool is_available() const;
    bool borrow_book();
    bool return_book();
};

std::ostream& operator<<(std::ostream& os, const Book& book);

#endif  // PROVIDED_BOOK_H_
