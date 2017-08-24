{
    errno = 0;
    r = connect(uv__stream_fd(handle), addr, addrlen);
  }