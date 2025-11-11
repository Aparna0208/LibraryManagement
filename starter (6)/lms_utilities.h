// provided. do not change. do not submit.
#ifndef PROVIDED_LMS_UTILITIES_H_
#define PROVIDED_LMS_UTILITIES_H_

#include <string>
#include <vector>
#include "library.h"

int read_list_of_books(Library& library, const std::string& filename);
int read_list_of_members(Library& library, const std::string& filename);
int read_list_of_borrowed_books(Library& library, const std::string& filename);
int read_list_of_returned_books(Library& library, const std::string& filename);

#endif  // PROVIDED_LMS_UTILITIES_H_
