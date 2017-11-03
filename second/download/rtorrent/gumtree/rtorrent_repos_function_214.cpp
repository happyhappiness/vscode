bool operator () (char c) const {
    return c == ' ' || c == '\t';
  }