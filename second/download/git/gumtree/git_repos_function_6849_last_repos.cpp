static FORCEINLINE int pthread_try_lock (MLOCK_T *sl) {
  volatile unsigned int* lp = &sl->l;
  if (*lp != 0) {
      if (sl->threadid == CURRENT_THREAD) {
	++sl->c;
	return 1;
      }
  }
  else {
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
      return 1;
    }
  }
  return 0;
}