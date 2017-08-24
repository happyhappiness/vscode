{
        /* Child terminated due to exceptional behavior.  */
        cp->ProcessResults[i].State = kwsysProcess_StateByIndex_Exception;
        cp->ProcessResults[i].ExitValue = 1;
        kwsysProcessSetExitExceptionByIndex(cp, cp->ProcessResults[i].ExitCode,
                                            i);
      }