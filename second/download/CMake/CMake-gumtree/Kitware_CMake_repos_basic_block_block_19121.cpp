{
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGPROF);
    sigmask |= 1 << (SIGPROF - 1);
  }