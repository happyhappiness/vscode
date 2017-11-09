static struct timeval tvnow(void)
{
  struct timeval now;

  /* time() returns the value of time in seconds since the epoch */
  now.tv_sec = (long)time(NULL);
  now.tv_usec = 0;

  return now;
}