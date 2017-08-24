{
    /* This is the special debugging test to run a given command
       line.  */
    const char** cmd = argv + 2;
    int state = kwsysProcess_State_Exited;
    int exception = kwsysProcess_Exception_None;
    int value = 0;
    double timeout = 0;
    int r =
      runChild(cmd, state, exception, value, 0, 1, 0, timeout, 0, 1, 0, 0, 0);
    return r;
  }