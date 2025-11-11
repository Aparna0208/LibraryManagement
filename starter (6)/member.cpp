#include <stdexcept>
#include <iostream>  
#include "member.h"

static bool is_valid_name_char(char c) { 
return std::isalpha(c);
}

static void validate_name(const std::string& first_name, const std::string& last_name) {
    if (first_name.empty() && last_name.empty()) {
throw std::invalid_argument("Invalid name");
    }

    auto check_name = [](const std::string& name) {
        for (char c : name) {

            if (!is_valid_name_char(c)) {

                return false;
            }
        }
        return true;
    };

    if (!check_name(first_name) || !check_name(last_name)) {
    throw std::invalid_argument("Invalid name");
    }
}

static void validate_id(int id) {
    if (id < 1000) {
     throw std::invalid_argument("Invalid id");
    }
}
Member::Member(std::string first_name,
               std::string last_name,
               int id)
    : name(MemberName{first_name, last_name}), 
      id(id) {
    
    validate_name(first_name, last_name);
    validate_id(id);
}
Member::Member(MemberName name,
               int id)
    : name(name), 
      id(id) {
    
    validate_name(name.first_name, name.last_name);
    validate_id(id);
}

MemberName Member::get_name() const {
    return name;
}

int Member::get_id() const {
    return id;
}

std::ostream& operator<<(std::ostream& os, const Member& member) {
    os << "Member: ";
    if (!member.get_name().first_name.empty()) {
        os << member.get_name().first_name << " ";
    }
    os << member.get_name().last_name

       << ", id: " << member.get_id();
    
    return os;
}