                                 FORMAT_MESSAGE_IGNORE_INSERTS, 0, original,

                                 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),

                                 cp->ErrorMessage, CMPE_PIPE_BUFFER_SIZE, 0);

    

    if(length > 0)

      {

      /* Remove trailing period and newline, if any.  */

      if(cp->ErrorMessage[length-1] == '\n')

        {

        cp->ErrorMessage[length-1] = 0;

        --length;

        if(length > 0 && cp->ErrorMessage[length-1] == '\r')

          {

          cp->ErrorMessage[length-1] = 0;

          --length;

          }

        }

      if(cp->ErrorMessage[length-1] == '.')

        {

        cp->ErrorMessage[length-1] = 0;

        --length;

        }

      }

    else

      {

      /* FormatMessage failed.  Use a default message.  */

      _snprintf(cp->ErrorMessage, CMPE_PIPE_BUFFER_SIZE,

                "Process execution failed with error 0x%X.  "

                "FormatMessage failed with error 0x%X.",

                original, GetLastError());

      }

    

    /* Set the error state.  */

    cp->State = kwsysProcess_State_Error;

    }

  

  /* Free memory.  */

