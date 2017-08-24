{
    /* Wait for a possible wakeup.  */
    kwsysProcessPipeThreadWakePipe(cp, td);

    /* Signal the main thread we have reset for a new process.  */
    ReleaseSemaphore(td->Waker.Reset, 1, 0);
  }