e(*ptr && (*ptr != ':')) {
      *ptr = (char)TOLOWER(*ptr);
      ptr++;
    }