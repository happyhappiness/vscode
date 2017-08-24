(i = 0; i < cp->NumberOfCommands; ++i) {
    if (cp->ForkPIDs[i]) {
      int result;
      while (((result = waitpid(cp->ForkPIDs[i], &cp->CommandExitCodes[i],
                                WNOHANG)) < 0) &&
             (errno == EINTR))
        ;
      if (result > 0) {
        /* This child has termianted.  */
        cp->ForkPIDs[i] = 0;
        if (--cp->CommandsLeft == 0) {
          /* All children have terminated.  Close the signal pipe
             write end so that no more notifications are sent to this
             object.  */
          kwsysProcessCleanupDescriptor(&cp->SignalPipe);

          /* TODO: Once the children have terminated, switch
             WaitForData to use a non-blocking read to get the
             rest of the data from the pipe.  This is needed when
             grandchildren keep the output pipes open.  */
        }
      } else if (result < 0 && cp->State != kwsysProcess_State_Error) {
        /* Unexpected error.  Report the first time this happens.  */
        strncpy(cp->ErrorMessage, strerror(errno), KWSYSPE_PIPE_BUFFER_SIZE);
        cp->State = kwsysProcess_State_Error;
      }
    }
  }