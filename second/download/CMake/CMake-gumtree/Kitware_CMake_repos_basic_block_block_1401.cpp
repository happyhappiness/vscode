{
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