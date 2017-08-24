(i = 0; i < KWSYSPE_PIPE_COUNT; ++i) {
    kwsysProcessCleanupDescriptor(&cp->PipeReadEnds[i]);
  }