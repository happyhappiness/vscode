{
    ret = pthread_mutex_lock(&mutex_buf[n]);
    if(ret) {
      DEBUGF(fprintf(stderr,
                     "Error: polarsslthreadlock_lock_function failed\n"));
      return 0; /* pthread_mutex_lock failed */
    }
  }