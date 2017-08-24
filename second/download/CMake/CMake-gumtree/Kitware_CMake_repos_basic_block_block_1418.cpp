{
    /* Read output from the process for this thread's pipe.  */
    kwsysProcessPipeThreadReadPipe(cp, td);

    /* Signal the main thread we have reset for a new process.  */
    ReleaseSemaphore(td->Reader.Reset, 1, 0);
  }