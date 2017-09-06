kwsysProcess* kwsysProcess_New()
{
  int i;

  /* Process control structure.  */
  kwsysProcess* cp;

  /* Path to Win9x forwarding executable.  */
  char* win9x = 0;

  /* Windows version number data.  */
  OSVERSIONINFO osv;
  
  /* Allocate a process control structure.  */
  cp = (kwsysProcess*)malloc(sizeof(kwsysProcess));
  ZeroMemory(cp, sizeof(*cp));
  
  /* Set initial status.  */
  cp->State = kwsysProcess_Starting;
  
  /* Choose a method of running the child based on version of
     windows.  */
  ZeroMemory(&osv, sizeof(osv));
  osv.dwOSVersionInfoSize = sizeof(osv);
  GetVersionEx(&osv);
  if(osv.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
    {
    /* This is Win9x.  We need the console forwarding executable to
       work-around a Windows 9x bug.  */
    char fwdName[_MAX_FNAME+1] = "";
    char tempDir[_MAX_PATH+1] = "";
    
    /* We will try putting the executable in the system temp
       directory.  */
    DWORD length = GetEnvironmentVariable("TEMP", tempDir, _MAX_PATH);
    
    /* Construct the executable name from the process id and kwsysProcess
       instance.  This should be unique.  */
    sprintf(fwdName, "cmw9xfwd_%u_%p.exe", GetCurrentProcessId(), cp);
    
    /* If the environment variable "TEMP" gave us a directory, use it.  */
    if(length > 0 && length <= _MAX_PATH)
      {
      /* Make sure there is no trailing slash.  */
      size_t tdlen = strlen(tempDir);
      if(tempDir[tdlen-1] == '/' || tempDir[tdlen-1] == '\\')
        {
        tempDir[tdlen-1] = 0;
        --tdlen;
        }
      
      /* Allocate a buffer to hold the forwarding executable path.  */
      win9x = (char*)malloc(tdlen + strlen(fwdName) + 2);
      if(!win9x)
        {
        kwsysProcess_Delete(cp);
        return 0;
        }
      
      /* Construct the full path to the forwarding executable.  */
      sprintf(win9x, "%s/%s", tempDir, fwdName);
      }
    
    /* If we found a place to put the forwarding executable, try to
       write it. */
    if(win9x)
      {
      if(!kwsysEncodedWriteArrayProcessFwd9x(win9x))
        {
        /* Failed to create forwarding executable.  Give up.  */
        free(win9x);
        kwsysProcess_Delete(cp);
        return 0;
        }
      }
    else
      {
      /* Failed to find a place to put forwarding executable.  */
      kwsysProcess_Delete(cp);
      return 0;
      }
    }
  
  /* We need the extra error pipe on Win9x.  */
  cp->Win9x = win9x;
  cp->PipeCount = cp->Win9x? 3:2;
  
  /* Initially no thread owns the mutex.  Initialize semaphore to 1.  */
  if(!(cp->SharedIndexMutex = CreateSemaphore(0, 1, 1, 0)))
    {
    kwsysProcess_Delete(cp);
    return 0;
    }
  
  /* Initially no data are available.  Initialize semaphore to 0.  */
  if(!(cp->Full = CreateSemaphore(0, 0, 1, 0)))
    {
    kwsysProcess_Delete(cp);
    return 0;
    }

  if(cp->Win9x)
    {
    /* Create an event to tell the forwarding executable to kill the
       child.  */
    SECURITY_ATTRIBUTES sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;
    if(!(cp->Win9xKillEvent = CreateEvent(&sa, TRUE, 0, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }
    }
    
  /* Create the thread to read each pipe.  */
  for(i=0; i < cp->PipeCount; ++i)
    {
    DWORD dummy=0;
    
    /* Assign the thread its index.  */
    cp->Pipe[i].Index = i;
    
    /* Give the thread a pointer back to the kwsysProcess instance.  */
    cp->Pipe[i].Process = cp;
    
    /* The pipe is not yet ready to read.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Ready = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }
    
    /* The pipe is not yet reset.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Reset = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }
    
    /* The thread's buffer is initially empty.  Initialize semaphore to 1.  */
    if(!(cp->Pipe[i].Empty = CreateSemaphore(0, 1, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }
    
    /* Create the thread.  It will block immediately.  The thread will
       not make deeply nested calls, so we need only a small
       stack.  */
    if(!(cp->Pipe[i].Thread = CreateThread(0, 1024, kwsysProcessPipeThread,
                                           &cp->Pipe[i], 0, &dummy)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }
    }
  
  return cp;
}