void kwsysProcess_Execute(kwsysProcess* cp)
{
  int i;

  /* Windows child startup control data.  */
  STARTUPINFO si;
  DWORD dwCreationFlags=0;
  
  /* Do not execute a second time.  */
  if(cp->State == kwsysProcess_State_Executing)
    {
    return;
    }
  
  /* Initialize startup info data.  */
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  
  /* Reset internal status flags.  */
  cp->TimeoutExpired = 0;
  cp->Terminated = 0;
  cp->Killed = 0;
  cp->ExitException = kwsysProcess_Exception_None;
  cp->ExitCode = 1;
  cp->ExitValue = 1;
  
  /* Reset error data.  */
  cp->ErrorMessage[0] = 0;
  cp->ErrorMessageLength = 0;
  
  /* Reset the Win9x kill event.  */
  if(cp->Win9x)
    {
    if(!ResetEvent(cp->Win9xKillEvent))
      {
      kwsysProcessCleanup(cp, 1);
      return;
      }
    }
  
  /* Create a pipe for each child output.  */
  for(i=0; i < cp->PipeCount; ++i)
    {
    HANDLE writeEnd;
    
    /* The pipe is not closed.  */
    cp->Pipe[i].Closed = 0;
    
    /* Create the pipe.  Neither end is directly inherited.  */
    if(!CreatePipe(&cp->Pipe[i].Read, &writeEnd, 0, 0))
      {
      kwsysProcessCleanup(cp, 1);
      return;
      }
    
    /* Create an inherited duplicate of the write end.  This also closes
       the non-inherited version. */
    if(!DuplicateHandle(GetCurrentProcess(), writeEnd,
                        GetCurrentProcess(), &cp->Pipe[i].Write,
                        0, TRUE, (DUPLICATE_CLOSE_SOURCE |
                                  DUPLICATE_SAME_ACCESS)))
      {
      kwsysProcessCleanup(cp, 1);
      return;
      }
    }
  
  /* Construct the real command line.  */
  if(cp->Win9x)
    {
    /* Windows 9x */
    
    /* The forwarding executable is given a handle to the error pipe
       and a handle to the kill event.  */
    cp->RealCommand = malloc(strlen(cp->Win9x)+strlen(cp->Command)+100);
    sprintf(cp->RealCommand, "%s %p %p %d %s", cp->Win9x,
            cp->Pipe[CMPE_PIPE_ERROR].Write, cp->Win9xKillEvent,
            cp->HideWindow, cp->Command);
    }
  else
    {
    /* Not Windows 9x */    
    cp->RealCommand = strdup(cp->Command);
    }
  
  /* Connect the child's output pipes to the threads.  */
  si.dwFlags = STARTF_USESTDHANDLES;
  si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
  si.hStdOutput = cp->Pipe[CMPE_PIPE_STDOUT].Write;
  si.hStdError = cp->Pipe[CMPE_PIPE_STDERR].Write;
  
  /* Decide whether a child window should be shown.  */
  si.dwFlags |= STARTF_USESHOWWINDOW;
  si.wShowWindow = (unsigned short)(cp->HideWindow?SW_HIDE:SW_SHOWDEFAULT);
  
  /* The timeout period starts now.  */
  cp->StartTime = kwsysProcessTimeGetCurrent();
  cp->TimeoutTime = kwsysProcessTimeFromDouble(-1);
  
  /* CREATE THE CHILD PROCESS */
  if(!CreateProcess(0, cp->RealCommand, 0, 0, TRUE, dwCreationFlags, 0,
                    cp->WorkingDirectory, &si, &cp->ProcessInformation))
    {
    kwsysProcessCleanup(cp, 1);
    return;
    }
  
  /* ---- It is no longer safe to call kwsysProcessCleanup. ----- */
  /* Tell the pipe threads that a process has started.  */
  for(i=0; i < cp->PipeCount; ++i)
    {
    ReleaseSemaphore(cp->Pipe[i].Ready, 1, 0);
    }
  
  /* We don't care about the child's main thread.  */
  kwsysProcessCleanupHandle(&cp->ProcessInformation.hThread);
  
  /* No pipe has reported data.  */
  cp->CurrentIndex = CMPE_PIPE_COUNT;
  cp->PipesLeft = cp->PipeCount;
  
  /* The process has now started.  */
  cp->State = kwsysProcess_State_Executing;
}