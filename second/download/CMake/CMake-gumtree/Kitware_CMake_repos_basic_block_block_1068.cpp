{
    foundDigit = true;
    is.ignore();
    if ((is.peek() == 'x' || is.peek() == 'X') && (base == 0 || base == 16)) {
      base = 16;
      foundDigit = false;
      is.ignore();
    } else if (base == 0) {
      base = 8;
    }
  }