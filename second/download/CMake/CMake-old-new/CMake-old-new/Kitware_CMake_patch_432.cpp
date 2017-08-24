@@ -28,14 +28,6 @@ On windows, a thread is created to wait for data on each pipe.  The
 threads are synchronized with the main thread to simulate the use of
 a UNIX-style select system call.
 
-On Windows9x platforms, a small WIN32 console application is spawned
-in-between the calling process and the actual child to be executed.
-This is to work-around a problem with connecting pipes from WIN16
-console applications to WIN32 applications.
-
-For more information, please check Microsoft Knowledge Base Articles
-Q190351 and Q150956.
-
 */
 
 #ifdef _MSC_VER
@@ -91,18 +83,12 @@ Q190351 and Q150956.
 # define KWSYSPE_DEBUG(x) (void)1
 #endif
 
-#define kwsysEncodedWriteArrayProcessFwd9x kwsys_ns(EncodedWriteArrayProcessFwd9x)
-
 typedef LARGE_INTEGER kwsysProcessTime;
 
 typedef struct kwsysProcessCreateInformation_s
 {
   /* Windows child startup control data.  */
   STARTUPINFO StartupInfo;
-
-  /* Special error reporting pipe for Win9x forwarding executable.  */
-  HANDLE ErrorPipeRead;
-  HANDLE ErrorPipeWrite;
 } kwsysProcessCreateInformation;
 
 /*--------------------------------------------------------------------------*/
@@ -146,7 +132,6 @@ static kwsysProcessTime kwsysProcessTimeSubtract(kwsysProcessTime in1, kwsysProc
 static void kwsysProcessSetExitException(kwsysProcess* cp, int code);
 static void kwsysProcessKillTree(int pid);
 static void kwsysProcessDisablePipeThreads(kwsysProcess* cp);
-extern kwsysEXPORT int kwsysEncodedWriteArrayProcessFwd9x(const char* fname);
 
 /*--------------------------------------------------------------------------*/
 /* A structure containing synchronization data for each thread.  */
@@ -233,15 +218,6 @@ struct kwsysProcess_s
   /* Whether to treat command lines as verbatim.  */
   int Verbatim;
 
-  /* On Win9x platforms, the path to the forwarding executable.  */
-  char* Win9x;
-
-  /* On Win9x platforms, the resume event for the forwarding executable.  */
-  HANDLE Win9xResumeEvent;
-
-  /* On Win9x platforms, the kill event for the forwarding executable.  */
-  HANDLE Win9xKillEvent;
-
   /* Mutex to protect the shared index used by threads to report data.  */
   HANDLE SharedIndexMutex;
 
@@ -269,9 +245,6 @@ struct kwsysProcess_s
   HANDLE PipeNativeSTDOUT[2];
   HANDLE PipeNativeSTDERR[2];
 
-  /* Handle to automatically delete the Win9x forwarding executable.  */
-  HANDLE Win9xHandle;
-
   /* ------------- Data managed per call to Execute ------------- */
 
   /* The exceptional behavior that terminated the process, if any.  */
@@ -311,7 +284,7 @@ struct kwsysProcess_s
      for pipes to close after process termination.  */
   int PipesLeft;
 
-  /* Buffer for error messages (possibly from Win9x child).  */
+  /* Buffer for error messages.  */
   char ErrorMessage[KWSYSPE_PIPE_BUFFER_SIZE+1];
 
   /* Description for the ExitException.  */
@@ -337,9 +310,6 @@ kwsysProcess* kwsysProcess_New(void)
   /* Process control structure.  */
   kwsysProcess* cp;
 
-  /* Path to Win9x forwarding executable.  */
-  char* win9x = 0;
-
   /* Windows version number data.  */
   OSVERSIONINFO osv;
 
@@ -365,73 +335,11 @@ kwsysProcess* kwsysProcess_New(void)
   GetVersionEx(&osv);
   if(osv.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
     {
-    /* This is Win9x.  We need the console forwarding executable to
-       work-around a Windows 9x bug.  */
-    char fwdName[_MAX_FNAME+1] = "";
-    char tempDir[_MAX_PATH+1] = "";
-
-    /* We will try putting the executable in the system temp
-       directory.  Note that the returned path already has a trailing
-       slash.  */
-    DWORD length = GetTempPath(_MAX_PATH+1, tempDir);
-
-    /* Construct the executable name from the process id and kwsysProcess
-       instance.  This should be unique.  */
-    sprintf(fwdName, KWSYS_NAMESPACE_STRING "pew9xfwd_%ld_%p.exe",
-            GetCurrentProcessId(), cp);
-
-    /* If we have a temp directory, use it.  */
-    if(length > 0 && length <= _MAX_PATH)
-      {
-      /* Allocate a buffer to hold the forwarding executable path.  */
-      size_t tdlen = strlen(tempDir);
-      win9x = (char*)malloc(tdlen + strlen(fwdName) + 2);
-      if(!win9x)
-        {
-        kwsysProcess_Delete(cp);
-        return 0;
-        }
-
-      /* Construct the full path to the forwarding executable.  */
-      sprintf(win9x, "%s%s", tempDir, fwdName);
-      }
-
-    /* If we found a place to put the forwarding executable, try to
-       write it. */
-    if(win9x)
-      {
-      if(!kwsysEncodedWriteArrayProcessFwd9x(win9x))
-        {
-        /* Failed to create forwarding executable.  Give up.  */
-        free(win9x);
-        kwsysProcess_Delete(cp);
-        return 0;
-        }
-
-      /* Get a handle to the file that will delete it when closed.  */
-      cp->Win9xHandle = CreateFile(win9x, GENERIC_READ, FILE_SHARE_READ, 0,
-                                   OPEN_EXISTING, FILE_FLAG_DELETE_ON_CLOSE, 0);
-      if(cp->Win9xHandle == INVALID_HANDLE_VALUE)
-        {
-        /* We were not able to get a read handle for the forwarding
-           executable.  It will not be deleted properly.  Give up.  */
-        _unlink(win9x);
-        free(win9x);
-        kwsysProcess_Delete(cp);
-        return 0;
-        }
-      }
-    else
-      {
-      /* Failed to find a place to put forwarding executable.  */
-      kwsysProcess_Delete(cp);
-      return 0;
-      }
+    /* Win9x no longer supported.  */
+    kwsysProcess_Delete(cp);
+    return 0;
     }
 
-  /* Save the path to the forwarding executable.  */
-  cp->Win9x = win9x;
-
   /* Initially no thread owns the mutex.  Initialize semaphore to 1.  */
   if(!(cp->SharedIndexMutex = CreateSemaphore(0, 1, 1, 0)))
     {
@@ -446,30 +354,6 @@ kwsysProcess* kwsysProcess_New(void)
     return 0;
     }
 
-  if(cp->Win9x)
-    {
-    SECURITY_ATTRIBUTES sa;
-    ZeroMemory(&sa, sizeof(sa));
-    sa.nLength = sizeof(sa);
-    sa.bInheritHandle = TRUE;
-
-    /* Create an event to tell the forwarding executable to resume the
-       child.  */
-    if(!(cp->Win9xResumeEvent = CreateEvent(&sa, TRUE, 0, 0)))
-      {
-      kwsysProcess_Delete(cp);
-      return 0;
-      }
-
-    /* Create an event to tell the forwarding executable to kill the
-       child.  */
-    if(!(cp->Win9xKillEvent = CreateEvent(&sa, TRUE, 0, 0)))
-      {
-      kwsysProcess_Delete(cp);
-      return 0;
-      }
-    }
-
   /* Create the thread to read each pipe.  */
   for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
     {
@@ -620,13 +504,6 @@ void kwsysProcess_Delete(kwsysProcess* cp)
   kwsysProcessCleanupHandle(&cp->SharedIndexMutex);
   kwsysProcessCleanupHandle(&cp->Full);
 
-  /* Close the Win9x resume and kill event handles.  */
-  if(cp->Win9x)
-    {
-    kwsysProcessCleanupHandle(&cp->Win9xResumeEvent);
-    kwsysProcessCleanupHandle(&cp->Win9xKillEvent);
-    }
-
   /* Free memory.  */
   kwsysProcess_SetCommand(cp, 0);
   kwsysProcess_SetWorkingDirectory(cp, 0);
@@ -637,12 +514,6 @@ void kwsysProcess_Delete(kwsysProcess* cp)
     {
     free(cp->CommandExitCodes);
     }
-  if(cp->Win9x)
-    {
-    /* Close our handle to the forwarding executable file.  This will
-       cause it to be deleted.  */
-    kwsysProcessCleanupHandle(&cp->Win9xHandle);
-    }
   free(cp);
 }
 
@@ -1017,21 +888,6 @@ void kwsysProcess_Execute(kwsysProcess* cp)
     SetCurrentDirectory(cp->WorkingDirectory);
     }
 
-  /* Reset the Win9x resume and kill events.  */
-  if(cp->Win9x)
-    {
-    if(!ResetEvent(cp->Win9xResumeEvent))
-      {
-      kwsysProcessCleanup(cp, 1);
-      return;
-      }
-    if(!ResetEvent(cp->Win9xKillEvent))
-      {
-      kwsysProcessCleanup(cp, 1);
-      return;
-      }
-    }
-
   /* Initialize startup info data.  */
   ZeroMemory(&si, sizeof(si));
   si.StartupInfo.cb = sizeof(si.StartupInfo);
@@ -1130,8 +986,6 @@ void kwsysProcess_Execute(kwsysProcess* cp)
                                     STD_OUTPUT_HANDLE);
       kwsysProcessCleanupHandleSafe(&si.StartupInfo.hStdError,
                                     STD_ERROR_HANDLE);
-      kwsysProcessCleanupHandle(&si.ErrorPipeRead);
-      kwsysProcessCleanupHandle(&si.ErrorPipeWrite);
       return;
       }
     }
@@ -1160,16 +1014,9 @@ void kwsysProcess_Execute(kwsysProcess* cp)
 
   /* All processes in the pipeline have been started in suspended
      mode.  Resume them all now.  */
-  if(cp->Win9x)
-    {
-    SetEvent(cp->Win9xResumeEvent);
-    }
-  else
+  for(i=0; i < cp->NumberOfCommands; ++i)
     {
-    for(i=0; i < cp->NumberOfCommands; ++i)
-      {
-      ResumeThread(cp->ProcessInformation[i].hThread);
-      }
+    ResumeThread(cp->ProcessInformation[i].hThread);
     }
 
   /* ---- It is no longer safe to call kwsysProcessCleanup. ----- */
@@ -1480,21 +1327,12 @@ void kwsysProcess_Kill(kwsysProcess* cp)
 
   /* Kill the children.  */
   cp->Killed = 1;
-  if(cp->Win9x)
-    {
-    /* Windows 9x.  Tell the forwarding executable to kill the child.  */
-    SetEvent(cp->Win9xKillEvent);
-    }
-  else
+  for(i=0; i < cp->NumberOfCommands; ++i)
     {
-    /* Not Windows 9x.  Just terminate the children.  */
-    for(i=0; i < cp->NumberOfCommands; ++i)
-      {
-      kwsysProcessKillTree(cp->ProcessInformation[i].dwProcessId); 
-      // close the handle if we kill it
-      kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
-      kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hProcess);
-      }
+    kwsysProcessKillTree(cp->ProcessInformation[i].dwProcessId);
+    // close the handle if we kill it
+    kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
+    kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hProcess);
     }
 
   /* We are killing the children and ignoring all data.  Do not wait
@@ -1815,97 +1653,13 @@ int kwsysProcessCreate(kwsysProcess* cp, int index,
       }
     }
 
-  /* Create the child process.  */
-  {
-  BOOL r;
-  char* realCommand;
-  if(cp->Win9x)
-    {
-    /* Create an error reporting pipe for the forwarding executable.
-       Neither end is directly inherited.  */
-    if(!CreatePipe(&si->ErrorPipeRead, &si->ErrorPipeWrite, 0, 0))
-      {
-      return 0;
-      }
-
-    /* Create an inherited duplicate of the write end.  This also closes
-       the non-inherited version. */
-    if(!DuplicateHandle(GetCurrentProcess(), si->ErrorPipeWrite,
-                        GetCurrentProcess(), &si->ErrorPipeWrite,
-                        0, TRUE, (DUPLICATE_CLOSE_SOURCE |
-                                  DUPLICATE_SAME_ACCESS)))
-      {
-      return 0;
-      }
-
-    /* The forwarding executable is given a handle to the error pipe
-       and resume and kill events.  */
-    realCommand = (char*)malloc(strlen(cp->Win9x)+strlen(cp->Commands[index])+100);
-    if(!realCommand)
-      {
-      return 0;
-      }
-    sprintf(realCommand, "%s %p %p %p %d %s", cp->Win9x,
-            si->ErrorPipeWrite, cp->Win9xResumeEvent, cp->Win9xKillEvent,
-            cp->HideWindow, cp->Commands[index]);
-    }
-  else
-    {
-    realCommand = cp->Commands[index];
-    }
-
   /* Create the child in a suspended state so we can wait until all
      children have been created before running any one.  */
-  r = CreateProcess(0, realCommand, 0, 0, TRUE,
-                    cp->Win9x? 0 : CREATE_SUSPENDED, 0, 0,
-                    &si->StartupInfo, &cp->ProcessInformation[index]);
-  if(cp->Win9x)
-    {
-    /* Free memory.  */
-    free(realCommand);
-
-    /* Close the error pipe write end so we can detect when the
-       forwarding executable closes it.  */
-    kwsysProcessCleanupHandle(&si->ErrorPipeWrite);
-    if(r)
-      {
-      /* Wait for the forwarding executable to report an error or
-         close the error pipe to report success.  */
-      DWORD total = 0;
-      DWORD n = 1;
-      while(total < KWSYSPE_PIPE_BUFFER_SIZE && n > 0)
-        {
-        if(ReadFile(si->ErrorPipeRead, cp->ErrorMessage+total,
-                    KWSYSPE_PIPE_BUFFER_SIZE-total, &n, 0))
-          {
-          total += n;
-          }
-        else
-          {
-          n = 0;
-          }
-        }
-      if(total > 0 || GetLastError() != ERROR_BROKEN_PIPE)
-        {
-        /* The forwarding executable could not run the process, or
-           there was an error reading from its error pipe.  Preserve
-           the last error while cleaning up the forwarding executable
-           so the cleanup our caller does reports the proper error.  */
-        DWORD error = GetLastError();
-        kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hThread);
-        kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hProcess);
-        SetLastError(error);
-        return 0;
-        }
-      }
-    kwsysProcessCleanupHandle(&si->ErrorPipeRead);
-    }
-
-  if(!r)
+  if(!CreateProcess(0, cp->Commands[index], 0, 0, TRUE, CREATE_SUSPENDED, 0,
+                    0, &si->StartupInfo, &cp->ProcessInformation[index]))
     {
     return 0;
     }
-  }
 
   /* Successfully created this child process.  Close the current
      process's copies of the inherited stdout and stdin handles.  The
@@ -2152,19 +1906,12 @@ void kwsysProcessCleanup(kwsysProcess* cp, int error)
     /* Cleanup any processes already started in a suspended state.  */
     if(cp->ProcessInformation)
       {
-      if(cp->Win9x)
-        {
-        SetEvent(cp->Win9xKillEvent);
-        }
-      else
+      for(i=0; i < cp->NumberOfCommands; ++i)
         {
-        for(i=0; i < cp->NumberOfCommands; ++i)
+        if(cp->ProcessInformation[i].hProcess)
           {
-          if(cp->ProcessInformation[i].hProcess)
-            {
-            TerminateProcess(cp->ProcessInformation[i].hProcess, 255);
-            WaitForSingleObject(cp->ProcessInformation[i].hProcess, INFINITE);
-            }
+          TerminateProcess(cp->ProcessInformation[i].hProcess, 255);
+          WaitForSingleObject(cp->ProcessInformation[i].hProcess, INFINITE);
           }
         }
       for(i=0; i < cp->NumberOfCommands; ++i)