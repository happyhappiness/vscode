(data && length) {
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