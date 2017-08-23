{
      DEBUGF(fprintf(stderr,
                     "Error: polarsslthreadlock_lock_function failed\n"));
      return 0; /* pthread_mutex_lock failed */
    }