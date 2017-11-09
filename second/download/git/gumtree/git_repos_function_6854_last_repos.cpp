static FORCEINLINE int win32_try_lock (MLOCK_T *sl) {
  if(sl->l != 0) {
      if (sl->threadid == CURRENT_THREAD) {
	++sl->c;
	return 1;
      }
  }
  else {
    if (!interlockedexchange(&sl->l, 1)){
      assert(!sl->threadid);
      sl->threadid = CURRENT_THREAD;
      sl->c = 1;
      return 1;
    }
  }
  return 0;
}