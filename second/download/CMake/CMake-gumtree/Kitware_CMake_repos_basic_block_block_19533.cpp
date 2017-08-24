do
    r = write(s->fake_fd, "x", 1);
  while (r == -1 && errno == EINTR);