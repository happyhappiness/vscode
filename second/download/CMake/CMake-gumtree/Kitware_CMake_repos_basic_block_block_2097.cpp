(*ptr) {
      const char* ptr2 = toreplace;
      while (*ptr2) {
        if (*ptr == *ptr2) {
          *ptr = replacement;
        }
        ++ptr2;
      }
      ++ptr;
    }