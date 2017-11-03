bool operator () (char c) const {
    return c == '\n' || c == '\0' || c == ';';
  }