{
    flags = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  }