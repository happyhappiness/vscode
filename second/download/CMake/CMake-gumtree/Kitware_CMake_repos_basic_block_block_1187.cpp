(WIFSIGNALED(cp->ProcessResults[prPipe].ExitCode)) {
        /* The child received an unhandled signal.  */
        cp->ProcessResults[prPipe].State = kwsysProcess_State_Exception;
        kwsysProcessSetExitExceptionByIndex(
          cp, (int)WTERMSIG(cp->ProcessResults[prPipe].ExitCode), prPipe);
      }