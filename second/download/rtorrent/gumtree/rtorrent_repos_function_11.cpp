inline char*
path_expand(const char* src, char* first, char* last) {
  if (*src == '~') {
    char* home = std::getenv("HOME");

    if (home == NULL)
      return first;

    first += strlcpy(first, home, std::distance(first, last));

    if (first > last)
      return last;

    src++;
  }

  return std::min(first + strlcpy(first, src, std::distance(first, last)), last);
}