{
      /* Save the index of the reporting thread and release the mutex.
         The thread will block until we signal its Empty mutex.  */
      cp->CurrentIndex = cp->SharedIndex;
      ReleaseSemaphore(cp->SharedIndexMutex, 1, 0);

      /* Data are available or a pipe closed.  */
      if (cp->Pipe[cp->CurrentIndex].Closed) {
        /* The pipe closed at the write end.  Close the read end and
           inform the wakeup thread it is done with this process.  */
        kwsysProcessCleanupHandle(&cp->Pipe[cp->CurrentIndex].Read);
        ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Waker.Go, 1, 0);
        KWSYSPE_DEBUG((stderr, "wakeup %d\n", cp->CurrentIndex));
        --cp->PipesLeft;
      } else if (data && length) {
        /* Report this data.  */
        *data = cp->Pipe[cp->CurrentIndex].DataBuffer;
        *length = cp->Pipe[cp->CurrentIndex].DataLength;
        switch (cp->CurrentIndex) {
          case KWSYSPE_PIPE_STDOUT:
            pipeId = kwsysProcess_Pipe_STDOUT;
            break;
          case KWSYSPE_PIPE_STDERR:
            pipeId = kwsysProcess_Pipe_STDERR;
            break;
        }
        done = 1;
      }
    }