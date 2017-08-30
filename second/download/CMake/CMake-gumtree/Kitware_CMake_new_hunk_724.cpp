    if(cp->ErrorMessage[0] == 0)
      {
      /* Format the error message.  */
      wchar_t err_msg[KWSYSPE_PIPE_BUFFER_SIZE];
      DWORD length = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
                                   FORMAT_MESSAGE_IGNORE_INSERTS, 0, error,
                                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                   err_msg, KWSYSPE_PIPE_BUFFER_SIZE, 0);
      if(length < 1)
        {
        /* FormatMessage failed.  Use a default message.  */
        _snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE,
                  "Process execution failed with error 0x%X.  "
                  "FormatMessage failed with error 0x%X",
                  error, GetLastError());
        }
      if(!WideCharToMultiByte(CP_UTF8, 0, err_msg, -1, cp->ErrorMessage,
                              KWSYSPE_PIPE_BUFFER_SIZE, NULL, NULL))
        {
        /* WideCharToMultiByte failed.  Use a default message.  */
        _snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE,
                  "Process execution failed with error 0x%X.  "
                  "WideCharToMultiByte failed with error 0x%X",
                  error, GetLastError());
        }
      }

