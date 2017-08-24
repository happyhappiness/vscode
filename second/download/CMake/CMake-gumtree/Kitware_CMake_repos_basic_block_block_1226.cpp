{
      strncpy(cp->ErrorMessage, strerror(errno), KWSYSPE_PIPE_BUFFER_SIZE);
    }