(cp->PipeSharedSTDERR) {
    /* Use the parent stderr.  */
    kwsysProcessSetupSharedPipe(STD_ERROR_HANDLE, &cp->PipeChildStd[2]);
  }