{
        /* Unexpected error.  Report the first time this happens.  */
        strncpy(cp->ErrorMessage, strerror(errno), KWSYSPE_PIPE_BUFFER_SIZE);
        cp->State = kwsysProcess_State_Error;
      }