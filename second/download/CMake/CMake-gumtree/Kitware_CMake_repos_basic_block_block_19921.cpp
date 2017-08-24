{
  struct sockaddr sa;
  struct stat s;
  socklen_t len;
  int type;

  if (file < 0)
    return UV_UNKNOWN_HANDLE;

  if (isatty(file))
    return UV_TTY;

  if (fstat(file, &s))
    return UV_UNKNOWN_HANDLE;

  if (S_ISREG(s.st_mode))
    return UV_FILE;

  if (S_ISCHR(s.st_mode))
    return UV_FILE;  /* XXX UV_NAMED_PIPE? */

  if (S_ISFIFO(s.st_mode))
    return UV_NAMED_PIPE;

  if (!S_ISSOCK(s.st_mode))
    return UV_UNKNOWN_HANDLE;

  len = sizeof(type);
  if (getsockopt(file, SOL_SOCKET, SO_TYPE, &type, &len))
    return UV_UNKNOWN_HANDLE;

  len = sizeof(sa);
  if (getsockname(file, &sa, &len))
    return UV_UNKNOWN_HANDLE;

  if (type == SOCK_DGRAM)
    if (sa.sa_family == AF_INET || sa.sa_family == AF_INET6)
      return UV_UDP;

  if (type == SOCK_STREAM) {
#if defined(_AIX) || defined(__DragonFly__)
    /* on AIX/DragonFly the getsockname call returns an empty sa structure
     * for sockets of type AF_UNIX.  For all other types it will
     * return a properly filled in structure.
     */
    if (len == 0)
      return UV_NAMED_PIPE;
#endif /* defined(_AIX) || defined(__DragonFly__) */

    if (sa.sa_family == AF_INET || sa.sa_family == AF_INET6)
      return UV_TCP;
    if (sa.sa_family == AF_UNIX)
      return UV_NAMED_PIPE;
  }

  return UV_UNKNOWN_HANDLE;
}