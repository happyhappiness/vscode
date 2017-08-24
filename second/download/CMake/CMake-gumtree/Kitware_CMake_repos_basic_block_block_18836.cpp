(len >= *size) {
    *size = len + 1;
    return -ENOBUFS;
  }