  /* If cleaning up due to an error, report the error message.  */

  if(error)

    {

    strncpy(cp->ErrorMessage, strerror(errno), KWSYSPE_PIPE_BUFFER_SIZE);

    cp->State = kwsysProcess_State_Error;

    }

  

