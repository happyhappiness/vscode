void polarssl_cleanup(void)
{
  (void)polarsslthreadlock_thread_cleanup();
}