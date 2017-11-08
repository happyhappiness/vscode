int polarsslthreadlock_thread_cleanup(void)
{
  int i;
  int ret;

  if(!mutex_buf)
    return 0; /* error, no threads locks defined */

#ifdef HAVE_PTHREAD_H
  for(i = 0; i < NUMT; i++) {
    ret = pthread_mutex_destroy(&mutex_buf[i]);
    if(ret)
      return 0; /* pthread_mutex_destroy failed */
  }
#elif defined(HAVE_PROCESS_H)
  for(i = 0; i < NUMT; i++) {
    ret = CloseHandle(mutex_buf[i]);
    if(!ret)
      return 0; /* CloseHandle failed */
  }
#endif /* HAVE_PTHREAD_H */
  free(mutex_buf);
  mutex_buf = NULL;

  return 1; /* OK */
}