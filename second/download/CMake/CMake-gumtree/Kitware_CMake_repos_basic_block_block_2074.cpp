(size_t i = 1; i < s.size(); i++) {
      if (isupper(s[i]) && !isspace(s[i - 1]) && !isupper(s[i - 1])) {
        n += ' ';
      }
      n += s[i];
    }