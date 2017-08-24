(!chars_to_escape || !*chars_to_escape) {
      n.append(str);
    } else {
      n.reserve(strlen(str));
      while (*str) {
        const char* ptr = chars_to_escape;
        while (*ptr) {
          if (*str == *ptr) {
            n += escape_char;
            break;
          }
          ++ptr;
        }
        n += *str;
        ++str;
      }
    }