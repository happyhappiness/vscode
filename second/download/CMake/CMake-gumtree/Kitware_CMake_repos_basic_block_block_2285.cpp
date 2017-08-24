(c[0] == '/' || c[0] == '\\') {
    // Unix path (or Windows path w/out drive letter).
    if (root) {
      *root = "/";
    }
    c += 1;
  }