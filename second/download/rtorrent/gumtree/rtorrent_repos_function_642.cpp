char*
print_string(char* first, char* last, char* str) {
  if (first == last)
    return first;

  // We don't have any nice simple functions for copying strings that
  // return the end address.
  while (first + 1 != last && *str != '\0')
    *(first++) = *(str++);

  *first = '\0';

  return first;
}