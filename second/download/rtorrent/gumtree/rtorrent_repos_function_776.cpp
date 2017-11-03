bool operator () (char c) {
    return !std::isgraph(c) || c == ':';
  }