(current_ != end_) {
    Char c = getNextChar();
    if (c == '\r' || c == '\n')
      break;
  }