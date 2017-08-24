(current_ != end_) {
    Char c = getNextChar();
    if (c == '*' && *current_ == '/')
      break;
  }