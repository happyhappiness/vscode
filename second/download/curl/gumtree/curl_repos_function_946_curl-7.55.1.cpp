void tool_go_sleep(long ms)
{
#if defined(MSDOS)
  delay(ms);
#elif defined(WIN32)
  Sleep(ms);
#elif defined(HAVE_POLL_FINE)
  (void)poll((void *)0, 0, (int)ms);
#else
  struct timeval timeout;
  timeout.tv_sec = ms / 1000L;
  ms = ms % 1000L;
  timeout.tv_usec = (int)ms * 1000;
  select(0, NULL,  NULL, NULL, &timeout);
#endif
}