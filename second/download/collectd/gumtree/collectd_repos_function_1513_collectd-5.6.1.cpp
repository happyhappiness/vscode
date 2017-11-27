static double dtime (void) /* {{{ */
{
  struct timeval tv = { 0 };

  if (gettimeofday (&tv, /* timezone = */ NULL) != 0)
    perror ("gettimeofday");

  return ((double) tv.tv_sec) + (((double) tv.tv_usec) / 1e6);
}