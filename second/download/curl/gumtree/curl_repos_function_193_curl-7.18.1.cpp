int select_test (int num_fds, fd_set *rd, fd_set *wr, fd_set *exc,
                 struct timeval *tv)
{
#ifdef USE_WINSOCK
  /* Winsock doesn't like no socket set in 'rd', 'wr' or 'exc'. This is
   * case when 'num_fds <= 0. So sleep.
   */
  if (num_fds <= 0) {
    Sleep(1000*tv->tv_sec + tv->tv_usec/1000);
    return 0;
  }
#endif
  return select(num_fds, rd, wr, exc, tv);
}