{
  int prPipe = 0;

  /* Make sure we are executing a process.  */
  if (!cp || cp->State != kwsysProcess_State_Executing) {
    return 1;
  }

  /* Wait for all the pipes to close.  Ignore all data.  */
  while ((prPipe = kwsysProcess_WaitForData(cp, 0, 0, userTimeout)) > 0) {
    if (prPipe == kwsysProcess_Pipe_Timeout) {
      return 0;
    }
  }

  /* Check if there was an error in one of the waitpid calls.  */
  if (cp->State == kwsysProcess_State_Error) {
    /* The error message is already in its buffer.  Tell
       kwsysProcessCleanup to not create it.  */
    kwsysProcessCleanup(cp, 0);
    return 1;
  }

  /* Check whether the child reported an error invoking the process.  */
  if (cp->SelectError) {
    /* The error message is already in its buffer.  Tell
       kwsysProcessCleanup to not create it.  */
    kwsysProcessCleanup(cp, 0);
    cp->State = kwsysProcess_State_Error;
    return 1;
  }
  /* Determine the outcome.  */
  if (cp->Killed) {
    /* We killed the child.  */
    cp->State = kwsysProcess_State_Killed;
  } else if (cp->TimeoutExpired) {
    /* The timeout expired.  */
    cp->State = kwsysProcess_State_Expired;
  } else {
    /* The children exited.  Report the outcome of the child processes.  */
    for (prPipe = 0; prPipe < cp->NumberOfCommands; ++prPipe) {
      cp->ProcessResults[prPipe].ExitCode = cp->CommandExitCodes[prPipe];
      if (WIFEXITED(cp->ProcessResults[prPipe].ExitCode)) {
        /* The child exited normally.  */
        cp->ProcessResults[prPipe].State = kwsysProcess_StateByIndex_Exited;
        cp->ProcessResults[prPipe].ExitException = kwsysProcess_Exception_None;
        cp->ProcessResults[prPipe].ExitValue =
          (int)WEXITSTATUS(cp->ProcessResults[prPipe].ExitCode);
      } else if (WIFSIGNALED(cp->ProcessResults[prPipe].ExitCode)) {
        /* The child received an unhandled signal.  */
        cp->ProcessResults[prPipe].State = kwsysProcess_State_Exception;
        kwsysProcessSetExitExceptionByIndex(
          cp, (int)WTERMSIG(cp->ProcessResults[prPipe].ExitCode), prPipe);
      } else {
        /* Error getting the child return code.  */
        strcpy(cp->ProcessResults[prPipe].ExitExceptionString,
               "Error getting child return code.");
        cp->ProcessResults[prPipe].State = kwsysProcess_StateByIndex_Error;
      }
    }
    /* support legacy state status value */
    cp->State = cp->ProcessResults[cp->NumberOfCommands - 1].State;
  }
  /* Normal cleanup.  */
  kwsysProcessCleanup(cp, 0);
  return 1;
}