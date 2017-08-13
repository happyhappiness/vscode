{
    /* This is the parent process for a requested test number.  */
    int states[10] = {
      kwsysProcess_State_Exited,   kwsysProcess_State_Exited,
      kwsysProcess_State_Expired,  kwsysProcess_State_Exception,
      kwsysProcess_State_Exited,   kwsysProcess_State_Expired,
      kwsysProcess_State_Exited,   kwsysProcess_State_Exited,
      kwsysProcess_State_Expired,  /* Ctrl+C handler test */
      kwsysProcess_State_Exception /* Process group test */
    };
    int exceptions[10] = {
      kwsysProcess_Exception_None, kwsysProcess_Exception_None,
      kwsysProcess_Exception_None, kwsysProcess_Exception_Fault,
      kwsysProcess_Exception_None, kwsysProcess_Exception_None,
      kwsysProcess_Exception_None, kwsysProcess_Exception_None,
      kwsysProcess_Exception_None, kwsysProcess_Exception_Interrupt
    };
    int values[10] = { 0, 123, 1, 1, 0, 0, 0, 0, 1, 1 };
    int shares[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
    int outputs[10] = { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 };
    int delays[10] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
    double timeouts[10] = { 10, 10, 10, 30, 30, 10, -1, 10, 6, 4 };
    int polls[10] = { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
    int repeat[10] = { 257, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int createNewGroups[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
    unsigned int interruptDelays[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 3, 2 };
    int r;
    const char* cmd[4];
#ifdef _WIN32
    char* argv0 = 0;
#endif
    char* test1IterationsStr = getenv("KWSYS_TEST_PROCESS_1_COUNT");
    if (test1IterationsStr) {
      long int test1Iterations = strtol(test1IterationsStr, 0, 10);
      if (test1Iterations > 10 && test1Iterations != LONG_MAX) {
        repeat[0] = (int)test1Iterations;
      }
    }
#ifdef _WIN32
    if (n == 0 && (argv0 = strdup(argv[0]))) {
      /* Try converting to forward slashes to see if it works.  */
      char* c;
      for (c = argv0; *c; ++c) {
        if (*c == '\\') {
          *c = '/';
        }
      }
      cmd[0] = argv0;
    } else {
      cmd[0] = argv[0];
    }
#else
    cmd[0] = argv[0];
#endif
    cmd[1] = "run";
    cmd[2] = argv[1];
    cmd[3] = 0;
    fprintf(stdout, "Output on stdout before test %d.\n", n);
    fprintf(stderr, "Output on stderr before test %d.\n", n);
    fflush(stdout);
    fflush(stderr);
    r = runChild(cmd, states[n - 1], exceptions[n - 1], values[n - 1],
                 shares[n - 1], outputs[n - 1], delays[n - 1], timeouts[n - 1],
                 polls[n - 1], repeat[n - 1], 0, createNewGroups[n - 1],
                 interruptDelays[n - 1]);
    fprintf(stdout, "Output on stdout after test %d.\n", n);
    fprintf(stderr, "Output on stderr after test %d.\n", n);
    fflush(stdout);
    fflush(stderr);
#if defined(_WIN32)
    if (argv0) {
      free(argv0);
    }
#endif
    return r;
  }