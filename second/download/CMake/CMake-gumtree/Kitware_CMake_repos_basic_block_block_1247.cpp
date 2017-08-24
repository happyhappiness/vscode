(pipe(pgidPipe) < 0) {
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[0]);
    kwsysProcessCleanupDescriptor(&si->ErrorPipe[1]);
    return 0;
  }