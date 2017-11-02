int polarsslthreadlock_thread_setup(void)
{
  int i;
  int ret;

  mutex_buf = malloc(NUMT * sizeof(POLARSSL_MUTEX_T));
  if(!mutex_buf)
    return 0;     /* error, no number of threads defined */

#ifdef HAVE_PTHREAD_H
  for(i = 0;  i < NUMT;  i++) {
    ret = pthread_mutex_init(&mutex_buf[i], NULL);
    if(ret)
      return 0; /* pthread_mutex_init failed */
  }
#elif defined(HAVE_PROCESS_H)
  for(i = 0;  i < NUMT;  i++) {
    mutex_buf[i] = CreateMutex(0, FALSE, 0);
    if(mutex_buf[i] == 0)
      return 0;  /* CreateMutex failed */
  }
#endif /* HAVE_PTHREAD_H */

  return 1; /* OK */
}