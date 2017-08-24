{
  int r;
  struct timespec ts;

#if defined(__APPLE__) && defined(__MACH__)
  ts.tv_sec = timeout / NANOSEC;
  ts.tv_nsec = timeout % NANOSEC;
  r = pthread_cond_timedwait_relative_np(cond, mutex, &ts);
#else
  timeout += uv__hrtime(UV_CLOCK_PRECISE);
  ts.tv_sec = timeout / NANOSEC;
  ts.tv_nsec = timeout % NANOSEC;
#if defined(__ANDROID__) && defined(HAVE_PTHREAD_COND_TIMEDWAIT_MONOTONIC)
  /*
   * The bionic pthread implementation doesn't support CLOCK_MONOTONIC,
   * but has this alternative function instead.
   */
  r = pthread_cond_timedwait_monotonic_np(cond, mutex, &ts);
#else
  r = pthread_cond_timedwait(cond, mutex, &ts);
#endif /* __ANDROID__ */
#endif


  if (r == 0)
    return 0;

  if (r == ETIMEDOUT)
    return -ETIMEDOUT;

  abort();
  return -EINVAL;  /* Satisfy the compiler. */
}