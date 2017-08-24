{
    /* Explicitly give the child no stdin.  */
    cp->PipeChildStd[0] = INVALID_HANDLE_VALUE;
  }