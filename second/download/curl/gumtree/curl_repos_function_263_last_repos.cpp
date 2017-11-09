static unsigned long thread_id(void)
{
  unsigned long ret;

  ret = (unsigned long)pthread_self();
  return ret;
}