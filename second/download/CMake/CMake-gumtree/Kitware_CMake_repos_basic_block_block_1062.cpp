{
      if ((foundNonZero || *out != '0') && out < end) {
        ++out;
        foundNonZero = true;
      }
      foundDigit = true;
    }