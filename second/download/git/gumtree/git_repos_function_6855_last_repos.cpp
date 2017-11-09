static int pthread_init_lock (MLOCK_T *sl) {
  pthread_mutexattr_t attr;
  if (pthread_mutexattr_init(&attr)) return 1;
  if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE)) return 1;
  if (pthread_mutex_init(sl, &attr)) return 1;
  if (pthread_mutexattr_destroy(&attr)) return 1;
  return 0;
}