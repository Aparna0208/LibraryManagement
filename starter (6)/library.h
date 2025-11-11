// provided. do not change. do not submit.
#ifndef PROVIDED_LIBRARY_H_
#define PROVIDED_LIBRARY_H_

#include <iostream>
#include <string>
#include <vector>
#include "book.h"
#include "member.h"

class Library {
    std::vector<Book> books{};
    std::vector<Member> members{};

 public:
    void add_book(Book book);
    void register_member(Member member);
    bool borrow_book(const std::string& isbn, int member_id, std::string& message);
    bool return_book(const std::string& isbn, std::string& message);
    void display_available_books(std::ostream& = std::cout);
    void display_library_members(std::ostream& = std::cout);
    bool is_book_available(const std::string& isbn);

    // for testing purposes only
    const std::vector<Book>& get_books() { return books; }
    const std::vector<Member>& get_members() { return members; }
};

#endif  // PROVIDED_LIBRARY_H_
