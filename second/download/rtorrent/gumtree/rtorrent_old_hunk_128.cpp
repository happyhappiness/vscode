#include "utils.h"

namespace display {

char*
print_string(char* first, char* last, char* str) {
  // We don't have any nice simple functions for copying strings that
  // return the end address.
  while (first != last && *str != '\0')
    *(first++) = *(str++);

  return first;
}

char*
print_hhmmss(char* first, char* last, time_t t) {
  std::tm *u = std::localtime(&t);
  
  if (u == NULL)
    //return "inv_time";
    throw torrent::internal_error("print_hhmmss(...) failed.");

  return print_buffer(first, last, "%2u:%02u:%02u", u->tm_hour, u->tm_min, u->tm_sec);
}

char*
print_ddhhmm(char* first, char* last, time_t t) {
