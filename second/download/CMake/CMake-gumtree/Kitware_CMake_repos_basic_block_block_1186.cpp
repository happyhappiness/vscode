{
        /* Error getting the child return code.  */
        strcpy(cp->ProcessResults[prPipe].ExitExceptionString,
               "Error getting child return code.");
        cp->ProcessResults[prPipe].State = kwsysProcess_StateByIndex_Error;
      }