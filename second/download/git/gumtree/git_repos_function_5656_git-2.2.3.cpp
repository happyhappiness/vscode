static FORCEINLINE void pthread_release_lock (MLOCK_T *sl) {
  assert(sl->l != 0);
  assert(sl->threadid == CURRENT_THREAD);
  if (--sl->c == 0) {
    sl->threadid = 0;
    volatile unsigned int* lp = &sl->l;
    int prev = 0;
    int ret;
    __asm__ __volatile__ ("lock; xchgl %0, %1"
			  : "=r" (ret)
			  : "m" (*(lp)), "0"(prev)
			  : "memory");
  }
}