{
  int err;
  int fd;

  fd = uv__inotify_init1(UV__IN_NONBLOCK | UV__IN_CLOEXEC);
  if (fd != -1)
    return fd;

  if (errno != ENOSYS)
    return -errno;

  fd = uv__inotify_init();
  if (fd == -1)
    return -errno;

  err = uv__cloexec(fd, 1);
  if (err == 0)
    err = uv__nonblock(fd, 1);

  if (err) {
    uv__close(fd);
    return err;
  }

  return fd;
}