static FORCEINLINE void win32_release_lock (MLOCK_T *sl) {
  assert(sl->threadid == CURRENT_THREAD);
  assert(sl->l != 0);
  if (--sl->c == 0) {
    sl->threadid = 0;
    interlockedexchange (&sl->l, 0);
  }
}