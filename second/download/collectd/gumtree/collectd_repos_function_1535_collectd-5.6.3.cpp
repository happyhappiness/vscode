static int64_t rrd_get_random_variation(void) {
  if (random_timeout == 0)
    return (0);

  return (int64_t)cdrand_range(-random_timeout, random_timeout);
}