static int gettimeofday(struct timeval *tp, void *nothing)
{
  (void)nothing; /* we don't support specific time-zones */
  tp->tv_sec = (long)time(NULL);
  tp->tv_usec = 0;
  return 0;
}