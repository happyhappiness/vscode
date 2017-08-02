{
        /* WideCharToMultiByte failed.  Use a default message.  */
        _snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE,
                  "Process execution failed with error 0x%X.  "
                  "WideCharToMultiByte failed with error 0x%X",
                  error, GetLastError());
      }