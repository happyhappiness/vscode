do
    saved_flags = fcntl(fd, F_GETFL);
  while (saved_flags == -1 && errno == EINTR);