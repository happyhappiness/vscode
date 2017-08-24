(!saw_digit) {
        if (++octets > 4)
          return UV_EINVAL;
        saw_digit = 1;
      }