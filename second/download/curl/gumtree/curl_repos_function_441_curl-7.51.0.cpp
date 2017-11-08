void wait_ms(int ms)
{
  struct timeval t;
  t.tv_sec = ms/1000;
  ms -= (int)t.tv_sec * 1000;
  t.tv_usec = ms * 1000;
  select_wrapper(0, NULL, NULL, NULL, &t);
}