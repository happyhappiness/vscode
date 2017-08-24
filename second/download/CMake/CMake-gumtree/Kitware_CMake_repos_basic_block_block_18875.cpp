{
  int r;
  struct timespec sp;
  r = clock_gettime(CLOCK_MONOTONIC, &sp);
  if (r)
    return -errno;

  *uptime = sp.tv_sec;
  return 0;
}