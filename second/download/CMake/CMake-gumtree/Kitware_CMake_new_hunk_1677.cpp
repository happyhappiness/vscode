{

  int i;



  /* Child startup control data.  */

  kwsysProcessCreateInformation si;

  

  /* Do not execute a second time.  */

  if(cp->State == kwsysProcess_State_Executing)

    {

    return;

    }



  /* Initialize the control structure for a new process.  */

  if(!kwsysProcessInitialize(cp))

    {

    strcpy(cp->ErrorMessage, "Out of memory");

    cp->State = kwsysProcess_State_Error;

    return;

    }

  

  /* Reset the Win9x resume and kill events.  */

  if(cp->Win9x)

    {

    if(!ResetEvent(cp->Win9xResumeEvent))

      {

      kwsysProcessCleanup(cp, 1);

      return;

      }

    if(!ResetEvent(cp->Win9xKillEvent))

      {

      kwsysProcessCleanup(cp, 1);

      return;

      }

    }



  /* Initialize startup info data.  */

  ZeroMemory(&si, sizeof(si));

  si.StartupInfo.cb = sizeof(si.StartupInfo);

  

  /* Decide whether a child window should be shown.  */

  si.StartupInfo.dwFlags |= STARTF_USESHOWWINDOW;

  si.StartupInfo.wShowWindow =

    (unsigned short)(cp->HideWindow?SW_HIDE:SW_SHOWDEFAULT);

  

  /* Connect the child's output pipes to the threads.  */

  si.StartupInfo.dwFlags = STARTF_USESTDHANDLES;



  /* Create stderr pipe to be shared by all processes in the pipeline.

     Neither end is directly inherited.  */

  if(!CreatePipe(&cp->Pipe[KWSYSPE_PIPE_STDERR].Read,

                 &cp->Pipe[KWSYSPE_PIPE_STDERR].Write, 0, 0))

    {

    kwsysProcessCleanup(cp, 1);

    return;

    }

    

  /* Create an inherited duplicate of the write end, but do not

     close the non-inherited version.  We need to keep it open

     to use in waking up the pipe threads.  */

  if(!DuplicateHandle(GetCurrentProcess(), cp->Pipe[KWSYSPE_PIPE_STDERR].Write,

                      GetCurrentProcess(), &si.StartupInfo.hStdError,

                      0, TRUE, DUPLICATE_SAME_ACCESS))

    {

    kwsysProcessCleanup(cp, 1);

    kwsysProcessCleanupHandle(&si.StartupInfo.hStdError);

    return;

    }



  /* Create the pipeline of processes.  */

  {

  HANDLE readEnd = 0;

  for(i=0; i < cp->NumberOfCommands; ++i)

    {

    if(kwsysProcessCreate(cp, i, &si, &readEnd))

      {

      cp->ProcessEvents[i+1] = cp->ProcessInformation[i].hProcess;

      }

    else

      {

      kwsysProcessCleanup(cp, 1);



      /* Release resources that may have been allocated for this

         process before an error occurred.  */

      kwsysProcessCleanupHandle(&readEnd);

      if(i > 0)

        {

        kwsysProcessCleanupHandle(&si.StartupInfo.hStdInput);

        }

      kwsysProcessCleanupHandle(&si.StartupInfo.hStdOutput);

      kwsysProcessCleanupHandle(&si.StartupInfo.hStdError);

      kwsysProcessCleanupHandle(&si.ErrorPipeRead);

      kwsysProcessCleanupHandle(&si.ErrorPipeWrite);

      return;

      }

    }



  /* Save a handle to the output pipe for the last process.  */

  cp->Pipe[KWSYSPE_PIPE_STDOUT].Read = readEnd;

  }



  /* Close the inherited handles to the stderr pipe shared by all

     processes in the pipeline.  */

  kwsysProcessCleanupHandle(&si.StartupInfo.hStdError);



  /* The timeout period starts now.  */

  cp->StartTime = kwsysProcessTimeGetCurrent();

  cp->TimeoutTime = kwsysProcessTimeFromDouble(-1);

  

  /* All processes in the pipeline have been started in suspended

     mode.  Resume them all now.  */

  if(cp->Win9x)

    {

    SetEvent(cp->Win9xResumeEvent);

    }

  else

    {

    for(i=0; i < cp->NumberOfCommands; ++i)

      {

      ResumeThread(cp->ProcessInformation[i].hThread);

      }

    }



  /* ---- It is no longer safe to call kwsysProcessCleanup. ----- */  

  /* Tell the pipe threads that a process has started.  */

  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)

    {

    ReleaseSemaphore(cp->Pipe[i].Ready, 1, 0);

    }



  /* We don't care about the children's main threads.  */

  for(i=0; i < cp->NumberOfCommands; ++i)

    {

    kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);

    }

  

  /* No pipe has reported data.  */

  cp->CurrentIndex = KWSYSPE_PIPE_COUNT;

  cp->PipesLeft = KWSYSPE_PIPE_COUNT;

  

  /* The process has now started.  */

  cp->State = kwsysProcess_State_Executing;

