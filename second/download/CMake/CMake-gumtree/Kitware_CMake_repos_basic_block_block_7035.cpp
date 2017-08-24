{
    ret = pthread_mutex_unlock(&mutex_buf[n]);
    if(ret) {
      DEBUGF(fprintf(stderr,
                     "Error: polarsslthreadlock_unlock_function failed\n"));
      return 0; /* pthread_mutex_unlock failed */
    }
  }