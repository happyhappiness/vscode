      }
    }

  /* Create the child process.  */
  {
  BOOL r;
  char* realCommand;
  if(cp->Win9x)
    {
    /* Create an error reporting pipe for the forwarding executable.
       Neither end is directly inherited.  */
    if(!CreatePipe(&si->ErrorPipeRead, &si->ErrorPipeWrite, 0, 0))
      {
      return 0;
      }

    /* Create an inherited duplicate of the write end.  This also closes
       the non-inherited version. */
    if(!DuplicateHandle(GetCurrentProcess(), si->ErrorPipeWrite,
                        GetCurrentProcess(), &si->ErrorPipeWrite,
                        0, TRUE, (DUPLICATE_CLOSE_SOURCE |
                                  DUPLICATE_SAME_ACCESS)))
      {
      return 0;
      }

    /* The forwarding executable is given a handle to the error pipe
       and resume and kill events.  */
    realCommand = (char*)malloc(strlen(cp->Win9x)+strlen(cp->Commands[index])+100);
    if(!realCommand)
      {
      return 0;
      }
    sprintf(realCommand, "%s %p %p %p %d %s", cp->Win9x,
            si->ErrorPipeWrite, cp->Win9xResumeEvent, cp->Win9xKillEvent,
            cp->HideWindow, cp->Commands[index]);
    }
  else
    {
    realCommand = cp->Commands[index];
    }

  /* Create the child in a suspended state so we can wait until all
     children have been created before running any one.  */
  r = CreateProcess(0, realCommand, 0, 0, TRUE,
                    cp->Win9x? 0 : CREATE_SUSPENDED, 0, 0,
                    &si->StartupInfo, &cp->ProcessInformation[index]);
  if(cp->Win9x)
    {
    /* Free memory.  */
    free(realCommand);

    /* Close the error pipe write end so we can detect when the
       forwarding executable closes it.  */
    kwsysProcessCleanupHandle(&si->ErrorPipeWrite);
    if(r)
      {
      /* Wait for the forwarding executable to report an error or
         close the error pipe to report success.  */
      DWORD total = 0;
      DWORD n = 1;
      while(total < KWSYSPE_PIPE_BUFFER_SIZE && n > 0)
        {
        if(ReadFile(si->ErrorPipeRead, cp->ErrorMessage+total,
                    KWSYSPE_PIPE_BUFFER_SIZE-total, &n, 0))
          {
          total += n;
          }
        else
          {
          n = 0;
          }
        }
      if(total > 0 || GetLastError() != ERROR_BROKEN_PIPE)
        {
        /* The forwarding executable could not run the process, or
           there was an error reading from its error pipe.  Preserve
           the last error while cleaning up the forwarding executable
           so the cleanup our caller does reports the proper error.  */
        DWORD error = GetLastError();
        kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hThread);
        kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hProcess);
        SetLastError(error);
        return 0;
        }
      }
    kwsysProcessCleanupHandle(&si->ErrorPipeRead);
    }

  if(!r)
    {
    return 0;
    }
  }

  /* Successfully created this child process.  Close the current
     process's copies of the inherited stdout and stdin handles.  The
