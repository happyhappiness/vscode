static int curlTimerCallback(CURLM *multi, long timeout_ms, void *userp)
{
  struct timeval* timeout = userp;

  (void)multi; /* unused */
  if(timeout_ms != -1) {
    *timeout = tutil_tvnow();
    timeout->tv_usec += timeout_ms * 1000;
  }
  else {
    timeout->tv_sec = -1;
  }
  return 0;
}