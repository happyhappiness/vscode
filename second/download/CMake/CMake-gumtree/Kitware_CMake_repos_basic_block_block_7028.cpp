r(i = 0;  i < NUMT;  i++) {
    ret = pthread_mutex_init(&mutex_buf[i], NULL);
    if(ret)
      return 0; /* pthread_mutex_init failed */
  }