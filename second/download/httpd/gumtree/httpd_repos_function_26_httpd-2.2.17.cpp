int timedif(struct timeval a, struct timeval b)
{
  register int us,s;

  us = a.tv_usec - b.tv_usec;
  us /= 1000;
  s = a.tv_sec - b.tv_sec;
  s *= 1000;
  return s+us;
}