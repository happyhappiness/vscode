{
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