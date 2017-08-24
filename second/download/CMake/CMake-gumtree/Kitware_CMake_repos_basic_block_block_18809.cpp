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