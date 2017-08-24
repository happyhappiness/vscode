{
  int yes;

#if defined(SO_REUSEPORT) && !defined(__linux__)
  yes = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(yes)))
    return -errno;
#else
  yes = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)))
    return -errno;
#endif

  return 0;
}