int Curl_polarsslthreadlock_unlock_function(int n)
{
  int ret;
#ifdef HAVE_PTHREAD_H
  if(n < NUMT) {
    ret = pthread_mutex_unlock(&mutex_buf[n]);
    if(ret) {
      DEBUGF(fprintf(stderr,
                     "Error: polarsslthreadlock_unlock_function failed\n"));
      return 0; /* pthread_mutex_unlock failed */
    }
  }
#elif defined(HAVE_PROCESS_H)
  if(n < NUMT) {
    ret = ReleaseMutex(mutex_buf[n]);
    if(!ret) {
      DEBUGF(fprintf(stderr,
                     "Error: polarsslthreadlock_unlock_function failed\n"));
      return 0; /* pthread_mutex_lock failed */
    }
  }
#endif /* HAVE_PTHREAD_H */
  return 1; /* OK */
}