(!CreatePipe(&cp->Pipe[KWSYSPE_PIPE_STDERR].Read,
                  &cp->Pipe[KWSYSPE_PIPE_STDERR].Write, 0, 0)) {
    kwsysProcessCleanup(cp, GetLastError());
    return;
  }