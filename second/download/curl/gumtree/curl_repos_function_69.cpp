struct timeval tvnow ()
{
 struct timeval now;
#ifdef HAVE_GETTIMEOFDAY
 gettimeofday (&now, NULL);
#else
 now.tv_sec = (long) time(NULL);
 now.tv_usec = 0;
#endif
 return now;
}