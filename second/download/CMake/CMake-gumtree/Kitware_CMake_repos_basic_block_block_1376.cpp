{
    /* Use a file for stdout.  */
    DWORD error = kwsysProcessSetupOutputPipeFile(&cp->PipeChildStd[1],
                                                  cp->PipeFileSTDOUT);
    if (error) {
      kwsysProcessCleanup(cp, error);
      return;
    }
  }