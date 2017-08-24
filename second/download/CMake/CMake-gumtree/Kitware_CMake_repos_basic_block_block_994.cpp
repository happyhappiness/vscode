{
    std::vector<char> chars(length);
    if (kwsysEncoding_wcstombs(&chars[0], wcstr, length) > 0) {
      str = &chars[0];
    }
  }