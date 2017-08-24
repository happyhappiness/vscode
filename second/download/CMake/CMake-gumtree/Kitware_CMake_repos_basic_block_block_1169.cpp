{
    /* Select returned an error.  Leave the error description in the
       pipe buffer.  */
    strncpy(cp->ErrorMessage, strerror(errno), KWSYSPE_PIPE_BUFFER_SIZE);

    /* Kill the children now.  */
    kwsysProcess_Kill(cp);
    cp->Killed = 0;
    cp->SelectError = 1;
  }