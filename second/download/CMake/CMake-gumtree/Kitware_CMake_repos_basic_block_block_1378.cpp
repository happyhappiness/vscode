{
    /* Share this process's stdin with the child.  */
    kwsysProcessSetupSharedPipe(STD_INPUT_HANDLE, &cp->PipeChildStd[0]);
  }