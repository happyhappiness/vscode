{
    InitializeCriticalSection(&kwsysProcesses.Lock);

    /* Set up console ctrl handler.  */
    if (!SetConsoleCtrlHandler(kwsysCtrlHandler, TRUE)) {
      return 0;
    }

    kwsysProcesses.Initialized = 1;
  }