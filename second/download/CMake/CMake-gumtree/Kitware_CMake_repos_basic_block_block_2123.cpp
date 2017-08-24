{
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