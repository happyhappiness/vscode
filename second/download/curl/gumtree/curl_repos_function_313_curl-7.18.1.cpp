struct timeval cutil_tvnow(void)
{
  struct timeval now;
  (void)gettimeofday(&now, NULL);
  return now;
}