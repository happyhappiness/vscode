(cp->CurrentIndex < KWSYSPE_PIPE_COUNT) {
      KWSYSPE_DEBUG((stderr, "releasing reader %d\n", cp->CurrentIndex));
      ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Reader.Go, 1, 0);
      cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
    }