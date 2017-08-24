(bufsize > *size) {
      *size = bufsize;
      return UV_ENOBUFS;
    }