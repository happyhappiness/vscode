{
    // save the current actions
    sigaction(SIGABRT, 0, &saABRTOrig);
    sigaction(SIGSEGV, 0, &saSEGVOrig);
    sigaction(SIGTERM, 0, &saTERMOrig);
    sigaction(SIGINT, 0, &saINTOrig);
    sigaction(SIGILL, 0, &saILLOrig);
    sigaction(SIGBUS, 0, &saBUSOrig);
    sigaction(SIGFPE, 0, &saFPEOrig);

    // enable read, disable write
    saOrigValid = 1;

    // install ours
    struct sigaction sa;
    sa.sa_sigaction = (SigAction)StacktraceSignalHandler;
    sa.sa_flags = SA_SIGINFO | SA_RESETHAND;
#ifdef SA_RESTART
    sa.sa_flags |= SA_RESTART;
#endif
    sigemptyset(&sa.sa_mask);

    sigaction(SIGABRT, &sa, 0);
    sigaction(SIGSEGV, &sa, 0);
    sigaction(SIGTERM, &sa, 0);
    sigaction(SIGINT, &sa, 0);
    sigaction(SIGILL, &sa, 0);
    sigaction(SIGBUS, &sa, 0);
    sigaction(SIGFPE, &sa, 0);
  }