(i = 0; i < KWSYSPE_PIPE_COUNT; ++i) {
    kwsysProcessCleanupHandle(&cp->Pipe[i].Write);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Read);
    cp->Pipe[i].Closed = 0;
  }