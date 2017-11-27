static double dtime(void) /* {{{ */
{
  struct timespec ts = {0};

  if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
    perror("clock_gettime");

  return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}