((prPipe = kwsysProcess_WaitForData(cp, 0, 0, userTimeout)) > 0) {
    if (prPipe == kwsysProcess_Pipe_Timeout) {
      return 0;
    }
  }