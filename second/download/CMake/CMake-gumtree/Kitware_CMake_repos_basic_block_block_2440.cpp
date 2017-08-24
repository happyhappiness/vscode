(p = new_string; *p != 0; ++p) {
    *p = CM_CAST(char, tolower(*p));
  }