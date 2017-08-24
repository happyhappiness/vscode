(i = 0; i < KWSYSPE_PIPE_COUNT; ++i) {
      /* TODO: If the child created its own child (our grandchild)
         which inherited a copy of the pipe write-end then the pipe
         may not close and we will still need the waker write pipe.
         However we still want to be able to detect end-of-data in the
         normal case.  The reader thread will have to switch to using
         PeekNamedPipe to read the last bit of data from the pipe
         without blocking.  This is equivalent to using a non-blocking
         read on posix.  */
      KWSYSPE_DEBUG((stderr, "closing wakeup write %d\n", i));
      kwsysProcessCleanupHandle(&cp->Pipe[i].Write);
    }