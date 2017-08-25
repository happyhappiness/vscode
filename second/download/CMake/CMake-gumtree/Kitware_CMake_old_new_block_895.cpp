{
      /* Select returned an error.  Leave the error description in the
         pipe buffer.  */
      snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE,
               "%s", strerror(errno));
      
      /* Kill the child now.  */
      kwsysProcess_Kill(cp);
      cp->Killed = 0;
      cp->ChildError = 1;
      cp->PipesLeft = 0;
      }