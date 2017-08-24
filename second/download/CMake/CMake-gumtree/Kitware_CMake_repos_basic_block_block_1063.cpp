(memchr(digits, *out = (char)is.peek(), maxDigitIndex) != 0) {
      if ((foundNonZero || *out != '0') && out < end) {
        ++out;
        foundNonZero = true;
      }
      foundDigit = true;
    } else {
      break;
    }