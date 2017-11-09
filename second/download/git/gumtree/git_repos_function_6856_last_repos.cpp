static void init_malloc_global_mutex() {
  for (;;) {
    long stat = malloc_global_mutex_status;
    if (stat > 0)
      return;
    /* transition to < 0 while initializing, then to > 0) */
    if (stat == 0 &&
	interlockedcompareexchange(&malloc_global_mutex_status, -1, 0) == 0) {
      InitializeCriticalSection(&malloc_global_mutex);
      interlockedexchange(&malloc_global_mutex_status,1);
      return;
    }
    SleepEx(0, FALSE);
  }
}