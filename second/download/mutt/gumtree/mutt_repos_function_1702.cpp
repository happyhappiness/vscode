static void mutt_srandom (void)
{
  struct timeval tv;
  unsigned seed;

  gettimeofday(&tv, NULL);
  /* POSIX.1-2008 states that seed is 'unsigned' without specifying its width.
   * Use as many of the lower order bits from the current time of day as the seed.
   * If the upper bound is truncated, that is fine.
   *
   * tv_sec is integral of type integer or float.  Cast to 'long long' before
   * bitshift in case it is a float.
   */
  seed = ((LONGLONG) tv.tv_sec << 20) | tv.tv_usec;
  srandom(seed);
}