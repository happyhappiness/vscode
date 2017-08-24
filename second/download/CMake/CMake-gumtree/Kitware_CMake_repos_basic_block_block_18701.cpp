{
    uv__cloexec(fd, 1);
    uv__nonblock(fd, 1);
    return fd;
  }