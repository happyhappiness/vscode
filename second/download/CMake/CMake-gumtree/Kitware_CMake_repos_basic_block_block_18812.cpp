{
  int r;
#if defined(__FreeBSD__) && __FreeBSD__ >= 10
  r = dup3(oldfd, newfd, O_CLOEXEC);
  if (r == -1)
    return -errno;
  return r;
#elif defined(__FreeBSD__) && defined(F_DUP2FD_CLOEXEC)
  r = fcntl(oldfd, F_DUP2FD_CLOEXEC, newfd);
  if (r != -1)
    return r;
  if (errno != EINVAL)
    return -errno;
  /* Fall through. */
#elif defined(__linux__)
  static int no_dup3;
  if (!no_dup3) {
    do
      r = uv__dup3(oldfd, newfd, UV__O_CLOEXEC);
    while (r == -1 && errno == EBUSY);
    if (r != -1)
      return r;
    if (errno != ENOSYS)
      return -errno;
    /* Fall through. */
    no_dup3 = 1;
  }
#endif
  {
    int err;
    do
      r = dup2(oldfd, newfd);
#if defined(__linux__)
    while (r == -1 && errno == EBUSY);
#else
    while (0);  /* Never retry. */
#endif

    if (r == -1)
      return -errno;

    err = uv__cloexec(newfd, 1);
    if (err) {
      uv__close(newfd);
      return err;
    }

    return r;
  }
}