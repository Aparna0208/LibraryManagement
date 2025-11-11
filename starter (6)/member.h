// provided. do not change. do not submit.
#ifndef PROVIDED_MEMBER_H_
#define PROVIDED_MEMBER_H_

#include <iostream>
#include <string>

struct MemberName {
    std::string first_name;
    std::string last_name;
};

class Member {
    MemberName name;
    int id;

 public:
       Member(std::string first_name, std::string last_name, int id);
       Member(MemberName name, int id);
       MemberName get_name() const;
       int get_id() const;
};

std::ostream& operator<<(std::ostream& os, const Member& member);

#endif  // PROVIDED_MEMBER_H_
