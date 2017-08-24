{
    sigprocmask(SIG_SETMASK, &old_mask, 0);
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[0]);
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[1]);
    kwsysProcessCleanupDescriptor(&pgidPipe[0]);
    kwsysProcessCleanupDescriptor(&pgidPipe[1]);
    return 0;
  }