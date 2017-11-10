static FORCEINLINE int win32_acquire_lock (MLOCK_T *sl) {
  int spins = 0;
  for (;;) {
    if (sl->l != 0) {
      if (sl->threadid == CURRENT_THREAD) {
	++sl->c;
	return 0;
      }
    }
    else {
      if (!interlockedexchange(&sl->l, 1)) {
	assert(!sl->threadid);
		sl->c=CURRENT_THREAD;
	sl->threadid = CURRENT_THREAD;
	sl->c = 1;
	return 0;
      }
    }
    if ((++spins & SPINS_PER_YIELD) == 0)
      SleepEx(0, FALSE);
  }
}