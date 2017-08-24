(len1 >= len2) {
    const char* ptr = str1 + len1 - len2;
    do {
      if (!strncmp(ptr, str2, len2)) {
        return ptr;
      }
    } while (ptr-- != str1);
  }