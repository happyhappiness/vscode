(c[0] && c[1] == ':') {
    // Path relative to a windows drive working directory.
    if (root) {
      (*root) = "_:";
      (*root)[0] = c[0];
    }
    c += 2;
  }