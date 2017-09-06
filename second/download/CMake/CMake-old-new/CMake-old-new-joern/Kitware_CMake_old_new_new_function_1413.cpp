int kwsysProcessCreate(kwsysProcess* cp, int index,
                       kwsysProcessCreateInformation* si,
                       PHANDLE readEnd)
{
  /* Setup the process's stdin.  */
  if(*readEnd)
    {
    /* Create an inherited duplicate of the read end from the output
       pipe of the previous process.  This also closes the
       non-inherited version. */
    if(!DuplicateHandle(GetCurrentProcess(), *readEnd,
                        GetCurrentProcess(), readEnd,
                        0, TRUE, (DUPLICATE_CLOSE_SOURCE |
                                  DUPLICATE_SAME_ACCESS)))
      {
      return 0;
      }
    si->StartupInfo.hStdInput = *readEnd;

    /* This function is done with this handle.  */
    *readEnd = 0;
    }
  else
    {
    si->StartupInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    }

  /* Setup the process's stdout.  */
  {
  DWORD maybeClose = DUPLICATE_CLOSE_SOURCE;
  HANDLE writeEnd;

  /* Create the output pipe for this process.  Neither end is directly
     inherited.  */
  if(!CreatePipe(readEnd, &writeEnd, 0, 0))
    {
    return 0;
    }

  /* Create an inherited duplicate of the write end.  Close the
     non-inherited version unless this is the last process.  Save the
     non-inherited write end of the last process.  */
  if(index == cp->NumberOfCommands-1)
    {
    cp->Pipe[KWSYSPE_PIPE_STDOUT].Write = writeEnd;
    maybeClose = 0;
    }
  if(!DuplicateHandle(GetCurrentProcess(), writeEnd,
                      GetCurrentProcess(), &si->StartupInfo.hStdOutput,
                      0, TRUE, (maybeClose | DUPLICATE_SAME_ACCESS)))
    {
    return 0;
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
    realCommand = malloc(strlen(cp->Win9x)+strlen(cp->Commands[index])+100);
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
                    cp->Win9x? 0 : CREATE_SUSPENDED, 0,
                    cp->WorkingDirectory, &si->StartupInfo,
                    &cp->ProcessInformation[index]);

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

  /* Successfully created this child process.  */
  if(index > 0)
    {
    /* Close our handle to the input pipe for the current process.  */
    kwsysProcessCleanupHandle(&si->StartupInfo.hStdInput);
    }

  /* The parent process does not need the inhertied pipe write end.  */
  kwsysProcessCleanupHandle(&si->StartupInfo.hStdOutput);

  return 1;
}