kwsysProcess* kwsysProcess_New(void)
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
  if(!cp)
    {
    /* Could not allocate memory for the control structure.  */
    return 0;
    }
  ZeroMemory(cp, sizeof(*cp));

  /* Share stdin with the parent process by default.  */
  cp->PipeSharedSTDIN = 1;

  /* Set initial status.  */
  cp->State = kwsysProcess_State_Starting;

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
       directory.  Note that the returned path already has a trailing
       slash.  */
    DWORD length = GetTempPath(_MAX_PATH+1, tempDir);

    /* Construct the executable name from the process id and kwsysProcess
       instance.  This should be unique.  */
    sprintf(fwdName, KWSYS_NAMESPACE_STRING "pew9xfwd_%ld_%p.exe",
            GetCurrentProcessId(), cp);

    /* If we have a temp directory, use it.  */
    if(length > 0 && length <= _MAX_PATH)
      {
      /* Allocate a buffer to hold the forwarding executable path.  */
      size_t tdlen = strlen(tempDir);
      win9x = (char*)malloc(tdlen + strlen(fwdName) + 2);
      if(!win9x)
        {
        kwsysProcess_Delete(cp);
        return 0;
        }

      /* Construct the full path to the forwarding executable.  */
      sprintf(win9x, "%s%s", tempDir, fwdName);
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

      /* Get a handle to the file that will delete it when closed.  */
      cp->Win9xHandle = CreateFile(win9x, GENERIC_READ, FILE_SHARE_READ, 0,
                                   OPEN_EXISTING, FILE_FLAG_DELETE_ON_CLOSE, 0);
      if(cp->Win9xHandle == INVALID_HANDLE_VALUE)
        {
        /* We were not able to get a read handle for the forwarding
           executable.  It will not be deleted properly.  Give up.  */
        _unlink(win9x);
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

  /* Save the path to the forwarding executable.  */
  cp->Win9x = win9x;

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
    SECURITY_ATTRIBUTES sa;
    ZeroMemory(&sa, sizeof(sa));
    sa.nLength = sizeof(sa);
    sa.bInheritHandle = TRUE;

    /* Create an event to tell the forwarding executable to resume the
       child.  */
    if(!(cp->Win9xResumeEvent = CreateEvent(&sa, TRUE, 0, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* Create an event to tell the forwarding executable to kill the
       child.  */
    if(!(cp->Win9xKillEvent = CreateEvent(&sa, TRUE, 0, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }
    }

  /* Create the thread to read each pipe.  */
  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
    {
    DWORD dummy=0;

    /* Assign the thread its index.  */
    cp->Pipe[i].Index = i;

    /* Give the thread a pointer back to the kwsysProcess instance.  */
    cp->Pipe[i].Process = cp;

    /* No process is yet running.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Reader.Ready = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* The pipe is not yet reset.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Reader.Reset = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* The thread's buffer is initially empty.  Initialize semaphore to 1.  */
    if(!(cp->Pipe[i].Reader.Go = CreateSemaphore(0, 1, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* Create the reading thread.  It will block immediately.  The
       thread will not make deeply nested calls, so we need only a
       small stack.  */
    if(!(cp->Pipe[i].Reader.Thread = CreateThread(0, 1024,
                                                  kwsysProcessPipeThreadRead,
                                                  &cp->Pipe[i], 0, &dummy)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* No process is yet running.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Waker.Ready = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* The pipe is not yet reset.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Waker.Reset = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* The waker should not wake immediately.  Initialize semaphore to 0.  */
    if(!(cp->Pipe[i].Waker.Go = CreateSemaphore(0, 0, 1, 0)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }

    /* Create the waking thread.  It will block immediately.  The
       thread will not make deeply nested calls, so we need only a
       small stack.  */
    if(!(cp->Pipe[i].Waker.Thread = CreateThread(0, 1024,
                                                 kwsysProcessPipeThreadWake,
                                                 &cp->Pipe[i], 0, &dummy)))
      {
      kwsysProcess_Delete(cp);
      return 0;
      }
    }

  return cp;
}