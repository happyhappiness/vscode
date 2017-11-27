static int64_t rrd_get_random_variation (void)
{
  long min;
  long max;

  if (random_timeout <= 0)
    return (0);

  /* Assure that "cache_timeout + random_variation" is never negative. */
  if (random_timeout > cache_timeout)
  {
	  INFO ("rrdtool plugin: Adjusting \"RandomTimeout\" to %.3f seconds.",
			  CDTIME_T_TO_DOUBLE (cache_timeout));
	  random_timeout = cache_timeout;
  }

  max = (long) (random_timeout / 2);
  min = max - ((long) random_timeout);

  return ((int64_t) cdrand_range (min, max));
}