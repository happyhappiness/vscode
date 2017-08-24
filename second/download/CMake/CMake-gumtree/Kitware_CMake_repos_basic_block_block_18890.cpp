{
#if defined(__linux__)
  /* utimesat() has nanosecond resolution but we stick to microseconds
   * for the sake of consistency with other platforms.
   */
  static int no_utimesat;
  struct timespec ts[2];
  struct timeval tv[2];
  char path[sizeof("/proc/self/fd/") + 3 * sizeof(int)];
  int r;

  if (no_utimesat)
    goto skip;

  ts[0].tv_sec  = req->atime;
  ts[0].tv_nsec = (uint64_t)(req->atime * 1000000) % 1000000 * 1000;
  ts[1].tv_sec  = req->mtime;
  ts[1].tv_nsec = (uint64_t)(req->mtime * 1000000) % 1000000 * 1000;

  r = uv__utimesat(req->file, NULL, ts, 0);
  if (r == 0)
    return r;

  if (errno != ENOSYS)
    return r;

  no_utimesat = 1;

skip:

  tv[0].tv_sec  = req->atime;
  tv[0].tv_usec = (uint64_t)(req->atime * 1000000) % 1000000;
  tv[1].tv_sec  = req->mtime;
  tv[1].tv_usec = (uint64_t)(req->mtime * 1000000) % 1000000;
  snprintf(path, sizeof(path), "/proc/self/fd/%d", (int) req->file);

  r = utimes(path, tv);
  if (r == 0)
    return r;

  switch (errno) {
  case ENOENT:
    if (fcntl(req->file, F_GETFL) == -1 && errno == EBADF)
      break;
    /* Fall through. */

  case EACCES:
  case ENOTDIR:
    errno = ENOSYS;
    break;
  }

  return r;

#elif defined(__APPLE__)                                                      \
    || defined(__DragonFly__)                                                 \
    || defined(__FreeBSD__)                                                   \
    || defined(__FreeBSD_kernel__)                                            \
    || defined(__NetBSD__)                                                    \
    || defined(__OpenBSD__)                                                   \
    || defined(__sun)
  struct timeval tv[2];
  tv[0].tv_sec  = req->atime;
  tv[0].tv_usec = (uint64_t)(req->atime * 1000000) % 1000000;
  tv[1].tv_sec  = req->mtime;
  tv[1].tv_usec = (uint64_t)(req->mtime * 1000000) % 1000000;
# if defined(__sun)
  return futimesat(req->file, NULL, tv);
# else
  return futimes(req->file, tv);
# endif
#elif defined(_AIX71)
  struct timespec ts[2];
  ts[0].tv_sec  = req->atime;
  ts[0].tv_nsec = (uint64_t)(req->atime * 1000000) % 1000000 * 1000;
  ts[1].tv_sec  = req->mtime;
  ts[1].tv_nsec = (uint64_t)(req->mtime * 1000000) % 1000000 * 1000;
  return futimens(req->file, ts);
#elif defined(__MVS__)
  attrib_t atr;
  memset(&atr, 0, sizeof(atr));
  atr.att_mtimechg = 1;
  atr.att_atimechg = 1;
  atr.att_mtime = req->mtime;
  atr.att_atime = req->atime;
  return __fchattr(req->file, &atr, sizeof(atr));
#else
  errno = ENOSYS;
  return -1;
#endif
}