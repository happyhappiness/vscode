{
#if KWSYSPE_USE_SELECT
      /* If the pipe was reported by the last call to select, we must
         read from it.  This is needed to satisfy the suggestions from
         "man select_tut" and is not needed for the polling
         implementation.  Ignore the data.  */
      if (FD_ISSET(cp->PipeReadEnds[i], &cp->PipeSet)) {
        /* We are handling this pipe now.  Remove it from the set.  */
        FD_CLR(cp->PipeReadEnds[i], &cp->PipeSet);

        /* The pipe is ready to read without blocking.  Keep trying to
           read until the operation is not interrupted.  */
        while ((read(cp->PipeReadEnds[i], cp->PipeBuffer,
                     KWSYSPE_PIPE_BUFFER_SIZE) < 0) &&
               (errno == EINTR))
          ;
      }
#endif

      /* We are done reading from this pipe.  */
      kwsysProcessCleanupDescriptor(&cp->PipeReadEnds[i]);
      --cp->PipesLeft;
    }