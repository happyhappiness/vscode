((pipe = kwsysProcess_WaitForData(cp, 0, 0, userTimeout)) > 0) {
    if (pipe == kwsysProcess_Pipe_Timeout) {
      /* The user timeout has expired.  */
      return 0;
    }
  }