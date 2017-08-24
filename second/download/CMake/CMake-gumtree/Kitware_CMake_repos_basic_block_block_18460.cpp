(ch == '.' && saw_digit) {
      if (octets == 4)
        return UV_EINVAL;
      *++tp = 0;
      saw_digit = 0;
    }