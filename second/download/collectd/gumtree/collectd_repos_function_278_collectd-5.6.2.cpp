static void time_normalize(struct timespec *ts) /* {{{ */
{
  while (ts->tv_nsec < 0) {
    if (ts->tv_sec == 0) {
      ts->tv_nsec = 0;
      return;
    }

    ts->tv_sec -= 1;
    ts->tv_nsec += 1000000000;
  }

  while (ts->tv_nsec >= 1000000000) {
    ts->tv_sec += 1;
    ts->tv_nsec -= 1000000000;
  }
}