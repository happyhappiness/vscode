{
#if defined(__linux__)
  static int no_eventfd2;
  static int no_eventfd;
  int fd;

  if (no_eventfd2)
    goto skip_eventfd2;

  fd = uv__eventfd2(0, UV__EFD_CLOEXEC | UV__EFD_NONBLOCK);
  if (fd != -1)
    return fd;

  if (errno != ENOSYS)
    return -errno;

  no_eventfd2 = 1;

skip_eventfd2:

  if (no_eventfd)
    goto skip_eventfd;

  fd = uv__eventfd(0);
  if (fd != -1) {
    uv__cloexec(fd, 1);
    uv__nonblock(fd, 1);
    return fd;
  }

  if (errno != ENOSYS)
    return -errno;

  no_eventfd = 1;

skip_eventfd:

#endif

  return -ENOSYS;
}