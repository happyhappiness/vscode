(putenv(buf) < 0 && errno != EINVAL) {
    err = errno;
  }