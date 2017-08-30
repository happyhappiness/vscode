static void kwsysProcessCleanup(kwsysProcess* cp, int error)
{
  int i;
  
  /* If cleaning up due to an error, report the error message.  */
  if(error)
    {
    snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE, "%s", strerror(errno));
    cp->State = kwsysProcess_State_Error;
    }
  
  /* Restore the SIGCHLD handler.  */
  while((sigaction(SIGCHLD, &cp->OldSigChldAction, 0) < 0) &&
        (errno == EINTR));
  
  /* Close pipe handles.  */
  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
    {
    kwsysProcessCleanupDescriptor(&cp->PipeReadEnds[i]);
    kwsysProcessCleanupDescriptor(&cp->PipeWriteEnds[i]);
    }
}