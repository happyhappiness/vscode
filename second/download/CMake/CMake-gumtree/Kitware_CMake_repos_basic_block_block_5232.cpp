f(ret != AUTH_OK) {
      /* Mechanism has dumped the error to stderr, don't error here. */
      return -1;
    }