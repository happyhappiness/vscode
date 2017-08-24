{
    // restore previous actions
    sigaction(SIGABRT, &saABRTOrig, 0);
    sigaction(SIGSEGV, &saSEGVOrig, 0);
    sigaction(SIGTERM, &saTERMOrig, 0);
    sigaction(SIGINT, &saINTOrig, 0);
    sigaction(SIGILL, &saILLOrig, 0);
    sigaction(SIGBUS, &saBUSOrig, 0);
    sigaction(SIGFPE, &saFPEOrig, 0);

    // enable write, disable read
    saOrigValid = 0;
  }