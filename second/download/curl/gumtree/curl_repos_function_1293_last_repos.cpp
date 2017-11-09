struct curltime curlx_tvnow(void)
{
  /*
  ** time() returns the value of time in seconds since the Epoch.
  */
  struct curltime now;
  now.tv_sec = time(NULL);
  now.tv_usec = 0;
  return now;
}