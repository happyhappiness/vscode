void kwsysProcessCleanup(kwsysProcess* cp, int error)
{
  int i;
  /* If this is an error case, report the error.  */
  if(error)
    {
    /* Construct an error message if one has not been provided already.  */
    if(cp->ErrorMessage[0] == 0)
      {
      /* Format the error message.  */
      DWORD original = GetLastError();
      wchar_t err_msg[KWSYSPE_PIPE_BUFFER_SIZE];
      DWORD length = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
                                   FORMAT_MESSAGE_IGNORE_INSERTS, 0, original,
                                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                   err_msg, KWSYSPE_PIPE_BUFFER_SIZE, 0);
      WideCharToMultiByte(CP_UTF8, 0, err_msg, -1, cp->ErrorMessage,
                          KWSYSPE_PIPE_BUFFER_SIZE, NULL, NULL);
      if(length < 1)
        {
        /* FormatMessage failed.  Use a default message.  */
        _snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE,
                  "Process execution failed with error 0x%X.  "
                  "FormatMessage failed with error 0x%X",
                  original, GetLastError());
        }
      }

    /* Remove trailing period and newline, if any.  */
    kwsysProcessCleanErrorMessage(cp);

    /* Set the error state.  */
    cp->State = kwsysProcess_State_Error;

    /* Cleanup any processes already started in a suspended state.  */
    if(cp->ProcessInformation)
      {
      for(i=0; i < cp->NumberOfCommands; ++i)
        {
        if(cp->ProcessInformation[i].hProcess)
          {
          TerminateProcess(cp->ProcessInformation[i].hProcess, 255);
          WaitForSingleObject(cp->ProcessInformation[i].hProcess, INFINITE);
          }
        }
      for(i=0; i < cp->NumberOfCommands; ++i)
        {