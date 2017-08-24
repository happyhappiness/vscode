{
    /* The waking threads will cause all reading threads to report.
       Wait for the next one and save its index.  */
    KWSYSPE_DEBUG((stderr, "waiting for reader\n"));
    WaitForSingleObject(cp->Full, INFINITE);
    cp->CurrentIndex = cp->SharedIndex;
    ReleaseSemaphore(cp->SharedIndexMutex, 1, 0);
    KWSYSPE_DEBUG((stderr, "got reader %d\n", cp->CurrentIndex));

    /* We are done reading this pipe.  Close its read handle.  */
    cp->Pipe[cp->CurrentIndex].Closed = 1;
    kwsysProcessCleanupHandle(&cp->Pipe[cp->CurrentIndex].Read);
    --cp->PipesLeft;

    /* Tell the reading thread we are done with the data.  It will
       reset immediately because the pipe is closed.  */
    ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Reader.Go, 1, 0);
  }