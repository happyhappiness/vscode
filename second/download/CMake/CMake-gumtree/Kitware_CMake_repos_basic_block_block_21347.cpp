(r > (int) *size) {
    *size = r;
    return UV_ENOBUFS;
  }