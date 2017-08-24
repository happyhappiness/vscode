(size_t i = 0; i < s.size(); i++) {
#if defined(_MSC_VER) && defined(_MT) && defined(_DEBUG)
    // MS has an assert that will fail if s[i] < 0; setting
    // LC_CTYPE using setlocale() does *not* help. Painful.
    if ((int)s[i] >= 0 && isalpha(s[i]) &&
        (i == 0 || ((int)s[i - 1] >= 0 && isspace(s[i - 1]))))
#else
    if (isalpha(s[i]) && (i == 0 || isspace(s[i - 1])))
#endif
    {
      n[i] = static_cast<std::string::value_type>(tolower(s[i]));
    }
  }