{
  /* Construct the error message.  */
  char buffer[KWSYSPE_PIPE_BUFFER_SIZE];
  strncpy(buffer, strerror(errno), KWSYSPE_PIPE_BUFFER_SIZE);
  
  /* Report the error to the parent through the special pipe.  */
  write(cp->PipeWriteEnds[KWSYSPE_PIPE_ERROR], buffer, strlen(buffer));