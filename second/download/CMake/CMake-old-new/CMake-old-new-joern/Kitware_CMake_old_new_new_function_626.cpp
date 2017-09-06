void kwsysProcessCleanup(kwsysProcess* cp, DWORD error)
{
  int i;
  /* If this is an error case, report the error.  */
  if(error)
    {
    /* Construct an error message if one has not been provided already.  */
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
        /* Remove from global list of processes and close handles.  */
        kwsysProcessesRemove(cp->ProcessInformation[i].hProcess);
        kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
        kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hProcess);
        }
      }

    /* Restore the working directory.  */
    if(cp->RealWorkingDirectory)
      {
      SetCurrentDirectoryW(cp->RealWorkingDirectory);
      }
    }

  /* Free memory.  */
  if(cp->ProcessInformation)
    {
    free(cp->ProcessInformation);
    cp->ProcessInformation = 0;
    }
  if(cp->ProcessEvents)
    {
    free(cp->ProcessEvents);
    cp->ProcessEvents = 0;
    }
  if(cp->RealWorkingDirectory)
    {
    free(cp->RealWorkingDirectory);
    cp->RealWorkingDirectory = 0;
    }

  /* Close each pipe.  */
  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
    {
    kwsysProcessCleanupHandle(&cp->Pipe[i].Write);
    kwsysProcessCleanupHandle(&cp->Pipe[i].Read);
    cp->Pipe[i].Closed = 0;
    }
  for(i=0; i < 3; ++i)
    {
    kwsysProcessCleanupHandle(&cp->PipeChildStd[i]);
    }
}