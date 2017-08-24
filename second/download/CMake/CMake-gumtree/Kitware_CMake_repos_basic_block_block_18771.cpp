do
    r = fcntl(fd, F_SETFD, flags);
  while (r == -1 && errno == EINTR);