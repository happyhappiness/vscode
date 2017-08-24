(!ReadFile(td->Read, td->DataBuffer, KWSYSPE_PIPE_BUFFER_SIZE,
                  &td->DataLength, 0)) {
      if (GetLastError() != ERROR_BROKEN_PIPE) {
        /* UNEXPECTED failure to read the pipe.  */
      }

      /* The pipe closed.  There are no more data to read.  */
      td->Closed = 1;
      KWSYSPE_DEBUG((stderr, "read closed %d\n", td->Index));
    }