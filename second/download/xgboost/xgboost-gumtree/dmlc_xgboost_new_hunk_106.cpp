
 private:
  inline static int Select_(int maxfd, fd_set *rfds,
                            fd_set *wfds, fd_set *efds, long timeout) { // NOLINT(*)
#if !defined(_WIN32)
    utils::Assert(maxfd < FD_SETSIZE, "maxdf must be smaller than FDSETSIZE");
#endif
