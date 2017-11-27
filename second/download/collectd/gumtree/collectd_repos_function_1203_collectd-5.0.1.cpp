static int64_t rrd_get_random_variation (void)
{
  double dbl_timeout;
  cdtime_t ctm_timeout;
  double rand_fact;
  _Bool negative;
  int64_t ret;

  if (random_timeout <= 0)
    return (0);

  /* Assure that "cache_timeout + random_variation" is never negative. */
  if (random_timeout > cache_timeout)
  {
	  INFO ("rrdtool plugin: Adjusting \"RandomTimeout\" to %.3f seconds.",
			  CDTIME_T_TO_DOUBLE (cache_timeout));
	  random_timeout = cache_timeout;
  }

  /* This seems a bit complicated, but "random_timeout" is likely larger than
   * RAND_MAX, so we can't simply use modulo here. */
  dbl_timeout = CDTIME_T_TO_DOUBLE (random_timeout);
  rand_fact = ((double) random ())
    / ((double) RAND_MAX);
  negative = (_Bool) (random () % 2);

  ctm_timeout = DOUBLE_TO_CDTIME_T (dbl_timeout * rand_fact);

  ret = (int64_t) ctm_timeout;
  if (negative)
    ret *= -1;

  return (ret);
}