(i = 0; i < KWSYSPE_PIPE_COUNT; ++i) {
    if (cp->PipeReadEnds[i] >= 0 &&
        FD_ISSET(cp->PipeReadEnds[i], &cp->PipeSet)) {
      kwsysProcess_ssize_t n;

      /* We are handling this pipe now.  Remove it from the set.  */
      FD_CLR(cp->PipeReadEnds[i], &cp->PipeSet);

      /* The pipe is ready to read without blocking.  Keep trying to
         read until the operation is not interrupted.  */
      while (((n = read(cp->PipeReadEnds[i], cp->PipeBuffer,
                        KWSYSPE_PIPE_BUFFER_SIZE)) < 0) &&
             (errno == EINTR))
        ;
      if (n > 0) {
        /* We have data on this pipe.  */
        if (i == KWSYSPE_PIPE_SIGNAL) {
          /* A child process has terminated.  */
          kwsysProcessDestroy(cp);
        } else if (data && length) {
          /* Report this data.  */
          *data = cp->PipeBuffer;
          *length = (int)(n);
          switch (i) {
            case KWSYSPE_PIPE_STDOUT:
              wd->PipeId = kwsysProcess_Pipe_STDOUT;
              break;
            case KWSYSPE_PIPE_STDERR:
              wd->PipeId = kwsysProcess_Pipe_STDERR;
              break;
          };
          return 1;
        }
      } else if (n < 0 && errno == EAGAIN) {
        /* No data are really ready.  The select call lied.  See the
           "man select" page on Linux for cases when this occurs.  */
      } else {
        /* We are done reading from this pipe.  */
        kwsysProcessCleanupDescriptor(&cp->PipeReadEnds[i]);
        --cp->PipesLeft;
      }
    }
  }