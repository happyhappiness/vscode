(sigprocmask(SIG_SETMASK, &old_mask, 0) < 0) {
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[0]);
    return 0;
  }