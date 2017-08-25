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
  else if(cp->PipeFileSTDIN)
    {
    /* Create a handle to read a file for stdin.  */
    HANDLE fin = CreateFile(cp->PipeFileSTDIN, GENERIC_READ|GENERIC_WRITE,
                            FILE_SHARE_READ|FILE_SHARE_WRITE,
                            0, OPEN_EXISTING, 0, 0);
    if(fin == INVALID_HANDLE_VALUE)
      {
      return 0;
      }
    /* Create an inherited duplicate of the handle.  This also closes
       the non-inherited version.  */
    if(!DuplicateHandle(GetCurrentProcess(), fin,
                        GetCurrentProcess(), &fin,
                        0, TRUE, (DUPLICATE_CLOSE_SOURCE |
                                  DUPLICATE_SAME_ACCESS)))
      {
      return 0;
      }
    si->StartupInfo.hStdInput = fin;
    }
  else if(cp->PipeSharedSTDIN)
    {
    /* Share this process's stdin with the child.  */
    if(!kwsysProcessSetupSharedPipe(STD_INPUT_HANDLE,
                                    &si->StartupInfo.hStdInput))
      {
      return 0;
      }
    }
  else if(cp->PipeNativeSTDIN[0])
    {
    /* Use the provided native pipe.  */
    if(!kwsysProcessSetupPipeNative(&si->StartupInfo.hStdInput,
                                    cp->PipeNativeSTDIN, 0))
      {
      return 0;
      }
    }
  else
    {
    /* Explicitly give the child no stdin.  */
    si->StartupInfo.hStdInput = INVALID_HANDLE_VALUE;
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
                      GetCurrentProcess(), &writeEnd,
                      0, TRUE, (maybeClose | DUPLICATE_SAME_ACCESS)))
    {
    return 0;
    }
  si->StartupInfo.hStdOutput = writeEnd;
  }

  /* Replace the stdout pipe with a file if requested.  In this case
     the pipe thread will still run but never report data.  */
  if(index == cp->NumberOfCommands-1 && cp->PipeFileSTDOUT)
    {
    if(!kwsysProcessSetupOutputPipeFile(&si->StartupInfo.hStdOutput,
                                        cp->PipeFileSTDOUT))
      {
      return 0;
      }
    }

  /* Replace the stdout pipe of the last child with the parent
     process's if requested.  In this case the pipe thread will still
     run but never report data.  */
  if(index == cp->NumberOfCommands-1 && cp->PipeSharedSTDOUT)
    {
    if(!kwsysProcessSetupSharedPipe(STD_OUTPUT_HANDLE,
                                    &si->StartupInfo.hStdOutput))
      {
      return 0;
      }
    }

  /* Replace the stdout pipe with the native pipe provided if any.  In
     this case the pipe thread will still run but never report
     data.  */
  if(index == cp->NumberOfCommands-1 && cp->PipeNativeSTDOUT[1])
    {
    if(!kwsysProcessSetupPipeNative(&si->StartupInfo.hStdOutput,
                                    cp->PipeNativeSTDOUT, 1))
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
     stderr handle is shared among all children and is closed by
     kwsysProcess_Execute after all children have been created.  */
  kwsysProcessCleanupHandleSafe(&si->StartupInfo.hStdInput,
                                STD_INPUT_HANDLE);
  kwsysProcessCleanupHandleSafe(&si->StartupInfo.hStdOutput,
                                STD_OUTPUT_HANDLE);

  return 1;
}