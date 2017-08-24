{
#endif
  pthread_t tid[2];
  pthread_create(&tid[0], 0, runner, (void*)1);
  pthread_create(&tid[1], 0, runner, (void*)2);

#if defined(__BEOS__) && !defined(__ZETA__) /* (no usleep on BeOS 5.) */
  usleep(1); /* for strange behavior on single-processor sun */
#endif

  pthread_join(tid[0], 0);
  pthread_join(tid[1], 0);
  if (ac > 1000) {
    return *av[0];
  }
  return res;
}