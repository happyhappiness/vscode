r(i = 0; i < NUMT; i++) {
    ret = pthread_mutex_destroy(&mutex_buf[i]);
    if(ret)
      return 0; /* pthread_mutex_destroy failed */
  }