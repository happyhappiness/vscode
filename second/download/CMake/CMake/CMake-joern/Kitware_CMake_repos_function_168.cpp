int Curl_polarsslthreadlock_lock_function(int n)
{
  int ret;
#ifdef HAVE_PTHREAD_H
  if(n < NUMT) {
    ret = pthread_mutex_lock(&mutex_buf[n]);
    if(ret) {
      DEBUGF(fprintf(stderr,
                     "Error: polarsslthreadlock_lock_function failed\n"));
      return 0; /* pthread_mutex_lock failed */
    }
  }
#elif defined(HAVE_PROCESS_H)
  if(n < NUMT) {
    ret = (WaitForSingleObject(mutex_buf[n], INFINITE)==WAIT_FAILED?1:0);
    if(ret) {
      DEBUGF(fprintf(stderr,
                     "Error: polarsslthreadlock_lock_function failed\n"));
      return 0; /* pthread_mutex_lock failed */
    }
  }
#endif /* HAVE_PTHREAD_H */
  return 1; /* OK */
}