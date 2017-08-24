do
    n = read(fd, buf, sizeof(buf) - 1);
  while (n == -1 && errno == EINTR);