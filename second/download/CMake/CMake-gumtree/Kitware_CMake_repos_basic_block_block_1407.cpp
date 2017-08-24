{
  int i;
  int pipe;

  /* Make sure we are executing a process.  */
  if (!cp || cp->State != kwsysProcess_State_Executing) {
    return 1;
  }

  /* Wait for the process to terminate.  Ignore all data.  */
  while ((pipe = kwsysProcess_WaitForData(cp, 0, 0, userTimeout)) > 0) {
    if (pipe == kwsysProcess_Pipe_Timeout) {
      /* The user timeout has expired.  */
      return 0;
    }
  }

  KWSYSPE_DEBUG((stderr, "no more data\n"));

  /* When the last pipe closes in WaitForData, the loop terminates
     without releasing the pipe's thread.  Release it now.  */
  if (cp->CurrentIndex < KWSYSPE_PIPE_COUNT) {
    KWSYSPE_DEBUG((stderr, "releasing reader %d\n", cp->CurrentIndex));
    ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Reader.Go, 1, 0);
    cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
  }

  /* Wait for all pipe threads to reset.  */
  for (i = 0; i < KWSYSPE_PIPE_COUNT; ++i) {
    KWSYSPE_DEBUG((stderr, "waiting reader reset %d\n", i));
    WaitForSingleObject(cp->Pipe[i].Reader.Reset, INFINITE);
    KWSYSPE_DEBUG((stderr, "waiting waker reset %d\n", i));
    WaitForSingleObject(cp->Pipe[i].Waker.Reset, INFINITE);
  }

  /* ---- It is now safe again to call kwsysProcessCleanup. ----- */
  /* Close all the pipes.  */
  kwsysProcessCleanup(cp, 0);

  /* Determine the outcome.  */
  if (cp->Killed) {
    /* We killed the child.  */
    cp->State = kwsysProcess_State_Killed;
  } else if (cp->TimeoutExpired) {
    /* The timeout expired.  */
    cp->State = kwsysProcess_State_Expired;
  } else {
    /* The children exited.  Report the outcome of the child processes.  */
    for (i = 0; i < cp->NumberOfCommands; ++i) {
      cp->ProcessResults[i].ExitCode = cp->CommandExitCodes[i];
      if ((cp->ProcessResults[i].ExitCode & 0xF0000000) == 0xC0000000) {
        /* Child terminated due to exceptional behavior.  */
        cp->ProcessResults[i].State = kwsysProcess_StateByIndex_Exception;
        cp->ProcessResults[i].ExitValue = 1;
        kwsysProcessSetExitExceptionByIndex(cp, cp->ProcessResults[i].ExitCode,
                                            i);
      } else {
        /* Child exited without exception.  */
        cp->ProcessResults[i].State = kwsysProcess_StateByIndex_Exited;
        cp->ProcessResults[i].ExitException = kwsysProcess_Exception_None;
        cp->ProcessResults[i].ExitValue = cp->ProcessResults[i].ExitCode;
      }
    }
    /* support legacy state status value */
    cp->State = cp->ProcessResults[cp->NumberOfCommands - 1].State;
  }

  return 1;
}