{
      DEBUGF(fprintf(stderr,
                     "Error: polarsslthreadlock_unlock_function failed\n"));
      return 0; /* pthread_mutex_unlock failed */
    }