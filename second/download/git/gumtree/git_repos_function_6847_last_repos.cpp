static FORCEINLINE int pthread_acquire_lock (MLOCK_T *sl) {
  int spins = 0;
  volatile unsigned int* lp = &sl->l;
  for (;;) {
    if (*lp != 0) {
      if (sl->threadid == CURRENT_THREAD) {
	++sl->c;
	return 0;
      }
    }
    else {
      /* place args to cmpxchgl in locals to evade oddities in some gccs */
      int cmp = 0;
      int val = 1;
      int ret;
      __asm__ __volatile__  ("lock; cmpxchgl %1, %2"
			     : "=a" (ret)
			     : "r" (val), "m" (*(lp)), "0"(cmp)
			     : "memory", "cc");
      if (!ret) {
	assert(!sl->threadid);
	sl->c = 1;
	sl->threadid = CURRENT_THREAD;
	return 0;
      }
      if ((++spins & SPINS_PER_YIELD) == 0) {
#if defined (__SVR4) && defined (__sun) /* solaris */
	thr_yield();
#else
#if defined(__linux__) || defined(__FreeBSD__) || defined(__APPLE__)
	sched_yield();
#else  /* no-op yield on unknown systems */
	;
#endif /* __linux__ || __FreeBSD__ || __APPLE__ */
#endif /* solaris */
      }
    }
  }
}