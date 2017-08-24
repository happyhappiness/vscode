{
  struct sockaddr_un sa;
  socklen_t addrlen;
  int err;

  addrlen = sizeof(sa);
  memset(&sa, 0, addrlen);
  err = func(uv__stream_fd(handle), (struct sockaddr*) &sa, &addrlen);
  if (err < 0) {
    *size = 0;
    return -errno;
  }

#if defined(__linux__)
  if (sa.sun_path[0] == 0)
    /* Linux abstract namespace */
    addrlen -= offsetof(struct sockaddr_un, sun_path);
  else
#endif
    addrlen = strlen(sa.sun_path);


  if (addrlen >= *size) {
    *size = addrlen + 1;
    return UV_ENOBUFS;
  }

  memcpy(buffer, sa.sun_path, addrlen);
  *size = addrlen;

  /* only null-terminate if it's not an abstract socket */
  if (buffer[0] != '\0')
    buffer[addrlen] = '\0';

  return 0;
}