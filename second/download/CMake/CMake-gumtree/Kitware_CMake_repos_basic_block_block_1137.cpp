(cp->PipeSharedSTDERR) {
    /* Use the parent stderr.  */
    kwsysProcessCleanupDescriptor(&cp->PipeChildStd[2]);
    cp->PipeChildStd[2] = 2;
  }