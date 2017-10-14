printf("(%d) %*s: %.*s\n", n, name_entry_size - 3, tabptr + 2,
      ovector[2*n+1] - ovector[2*n], subject + ovector[2*n]);