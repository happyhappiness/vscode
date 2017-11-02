int polarssl_init(void)
{
  return polarsslthreadlock_thread_setup();
}