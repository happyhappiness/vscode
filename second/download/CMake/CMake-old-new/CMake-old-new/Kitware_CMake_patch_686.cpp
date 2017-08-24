@@ -9,8 +9,8 @@ Version:   $Revision$
 Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
 See http://www.cmake.org/HTML/Copyright.html for details.
 
-This software is distributed WITHOUT ANY WARRANTY; without even 
-the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+This software is distributed WITHOUT ANY WARRANTY; without even
+the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
@@ -21,16 +21,16 @@ PURPOSE.  See the above copyright notices for more information.
 /*
 
 Implementation for Windows
-  
+
 On windows, a thread is created to wait for data on each pipe.  The
 threads are synchronized with the main thread to simulate the use of
 a UNIX-style select system call.
-  
+
 On Windows9x platforms, a small WIN32 console application is spawned
 in-between the calling process and the actual child to be executed.
 This is to work-around a problem with connecting pipes from WIN16
 console applications to WIN32 applications.
-  
+
 For more information, please check Microsoft Knowledge Base Articles
 Q190351 and Q150956.
 
@@ -101,125 +101,125 @@ extern kwsysEXPORT int kwsysEncodedWriteArrayProcessFwd9x(const char* fname);
 struct kwsysProcessPipeData_s
 {
   /* ------------- Data managed per instance of kwsysProcess ------------- */
-  
+
   /* Handle for the thread for this pipe.  */
   HANDLE Thread;
-    
+
   /* Semaphore indicating a process and pipe are available.  */
   HANDLE Ready;
-    
+
   /* Semaphore indicating when this thread's buffer is empty.  */
   HANDLE Empty;
-    
+
   /* Semaphore indicating a pipe thread has reset for another process.  */
   HANDLE Reset;
-    
+
   /* Index of this pipe.  */
   int Index;
 
   /* The kwsysProcess instance owning this pipe.  */
   kwsysProcess* Process;
-  
+
   /* ------------- Data managed per call to Execute ------------- */
-  
+
   /* Buffer for data read in this pipe's thread.  */
   char DataBuffer[KWSYSPE_PIPE_BUFFER_SIZE];
-    
+
   /* The length of the data stored in the buffer.  */
   DWORD DataLength;
-    
+
   /* Whether the pipe has been closed.  */
   int Closed;
-    
+
   /* Handle for the read end of this pipe. */
   HANDLE Read;
-  
+
   /* Handle for the write end of this pipe. */
   HANDLE Write;
-};  
+};
 
 /*--------------------------------------------------------------------------*/
 /* Structure containing data used to implement the child's execution.  */
 struct kwsysProcess_s
 {
   /* ------------- Data managed per instance of kwsysProcess ------------- */
-  
+
   /* The status of the process structure.  */
   int State;
-  
+
   /* The command lines to execute.  */
   char** Commands;
   int NumberOfCommands;
 
   /* The exit code of each command.  */
   DWORD* CommandExitCodes;
-  
+
   /* The working directory for the child process.  */
   char* WorkingDirectory;
-  
+
   /* Whether to hide the child process's window.  */
   int HideWindow;
-  
+
   /* On Win9x platforms, the path to the forwarding executable.  */
   char* Win9x;
-  
+
   /* On Win9x platforms, the resume event for the forwarding executable.  */
   HANDLE Win9xResumeEvent;
-  
+
   /* On Win9x platforms, the kill event for the forwarding executable.  */
   HANDLE Win9xKillEvent;
-  
+
   /* Mutex to protect the shared index used by threads to report data.  */
   HANDLE SharedIndexMutex;
-  
+
   /* Semaphore used by threads to signal data ready.  */
   HANDLE Full;
-  
+
   /* Whether we are currently deleting this kwsysProcess instance.  */
   int Deleting;
-  
+
   /* Data specific to each pipe and its thread.  */
-  kwsysProcessPipeData Pipe[KWSYSPE_PIPE_COUNT];  
-  
+  kwsysProcessPipeData Pipe[KWSYSPE_PIPE_COUNT];
+
   /* ------------- Data managed per call to Execute ------------- */
-  
+
   /* The exceptional behavior that terminated the process, if any.  */
   int ExitException;
-  
+
   /* The process exit code.  */
   DWORD ExitCode;
-  
+
   /* The process return code, if any.  */
   int ExitValue;
-  
+
   /* Index of last pipe to report data, if any.  */
   int CurrentIndex;
-  
-  /* Index shared by threads to report data.  */  
+
+  /* Index shared by threads to report data.  */
   int SharedIndex;
-  
+
   /* The timeout length.  */
   double Timeout;
-  
+
   /* Time at which the child started.  */
   kwsysProcessTime StartTime;
-  
+
   /* Time at which the child will timeout.  Negative for no timeout.  */
   kwsysProcessTime TimeoutTime;
-  
+
   /* Flag for whether the process was killed.  */
   int Killed;
-  
+
   /* Flag for whether the timeout expired.  */
   int TimeoutExpired;
-  
+
   /* Flag for whether the process has terminated.  */
   int Terminated;
-  
+
   /* The number of pipes still open during execution and while waiting
      for pipes to close after process termination.  */
   int PipesLeft;
-  
+
   /* Buffer for error messages (possibly from Win9x child).  */
   char ErrorMessage[KWSYSPE_PIPE_BUFFER_SIZE+1];
 
@@ -244,7 +244,7 @@ kwsysProcess* kwsysProcess_New()
 
   /* Windows version number data.  */
   OSVERSIONINFO osv;
-  
+
   /* Allocate a process control structure.  */
   cp = (kwsysProcess*)malloc(sizeof(kwsysProcess));
   if(!cp)
@@ -253,10 +253,10 @@ kwsysProcess* kwsysProcess_New()
     return 0;
     }
   ZeroMemory(cp, sizeof(*cp));
-  
+
   /* Set initial status.  */
   cp->State = kwsysProcess_State_Starting;
-  
+
   /* Choose a method of running the child based on version of
      windows.  */
   ZeroMemory(&osv, sizeof(osv));
@@ -268,16 +268,16 @@ kwsysProcess* kwsysProcess_New()
        work-around a Windows 9x bug.  */
     char fwdName[_MAX_FNAME+1] = "";
     char tempDir[_MAX_PATH+1] = "";
-    
+
     /* We will try putting the executable in the system temp
        directory.  Note that the returned path already has a trailing
        slash.  */
     DWORD length = GetTempPath(_MAX_PATH+1, tempDir);
-    
+
     /* Construct the executable name from the process id and kwsysProcess
        instance.  This should be unique.  */
     sprintf(fwdName, "cmw9xfwd_%u_%p.exe", GetCurrentProcessId(), cp);
-    
+
     /* If we have a temp directory, use it.  */
     if(length > 0 && length <= _MAX_PATH)
       {
@@ -289,11 +289,11 @@ kwsysProcess* kwsysProcess_New()
         kwsysProcess_Delete(cp);
         return 0;
         }
-      
+
       /* Construct the full path to the forwarding executable.  */
       sprintf(win9x, "%s%s", tempDir, fwdName);
       }
-    
+
     /* If we found a place to put the forwarding executable, try to
        write it. */
     if(win9x)
@@ -313,17 +313,17 @@ kwsysProcess* kwsysProcess_New()
       return 0;
       }
     }
-  
+
   /* Save the path to the forwarding executable.  */
   cp->Win9x = win9x;
-  
+
   /* Initially no thread owns the mutex.  Initialize semaphore to 1.  */
   if(!(cp->SharedIndexMutex = CreateSemaphore(0, 1, 1, 0)))
     {
     kwsysProcess_Delete(cp);
     return 0;
     }
-  
+
   /* Initially no data are available.  Initialize semaphore to 0.  */
   if(!(cp->Full = CreateSemaphore(0, 0, 1, 0)))
     {
@@ -354,39 +354,39 @@ kwsysProcess* kwsysProcess_New()
       return 0;
       }
     }
-    
+
   /* Create the thread to read each pipe.  */
   for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
     {
     DWORD dummy=0;
-    
+
     /* Assign the thread its index.  */
     cp->Pipe[i].Index = i;
-    
+
     /* Give the thread a pointer back to the kwsysProcess instance.  */
     cp->Pipe[i].Process = cp;
-    
+
     /* The pipe is not yet ready to read.  Initialize semaphore to 0.  */
     if(!(cp->Pipe[i].Ready = CreateSemaphore(0, 0, 1, 0)))
       {
       kwsysProcess_Delete(cp);
       return 0;
       }
-    
+
     /* The pipe is not yet reset.  Initialize semaphore to 0.  */
     if(!(cp->Pipe[i].Reset = CreateSemaphore(0, 0, 1, 0)))
       {
       kwsysProcess_Delete(cp);
       return 0;
       }
-    
+
     /* The thread's buffer is initially empty.  Initialize semaphore to 1.  */
     if(!(cp->Pipe[i].Empty = CreateSemaphore(0, 1, 1, 0)))
       {
       kwsysProcess_Delete(cp);
       return 0;
       }
-    
+
     /* Create the thread.  It will block immediately.  The thread will
        not make deeply nested calls, so we need only a small
        stack.  */
@@ -397,7 +397,7 @@ kwsysProcess* kwsysProcess_New()
       return 0;
       }
     }
-  
+
   return cp;
 }
 
@@ -411,10 +411,10 @@ void kwsysProcess_Delete(kwsysProcess* cp)
     {
     kwsysProcess_WaitForExit(cp, 0);
     }
-  
+
   /* We are deleting the kwsysProcess instance.  */
   cp->Deleting = 1;
-  
+
   /* Terminate each of the threads.  */
   for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
     {
@@ -423,30 +423,30 @@ void kwsysProcess_Delete(kwsysProcess* cp)
       /* Signal the thread we are ready for it.  It will terminate
          immediately since Deleting is set.  */
       ReleaseSemaphore(cp->Pipe[i].Ready, 1, 0);
-      
+
       /* Wait for the thread to exit.  */
       WaitForSingleObject(cp->Pipe[i].Thread, INFINITE);
-      
+
       /* Close the handle to the thread. */
       kwsysProcessCleanupHandle(&cp->Pipe[i].Thread);
       }
-    
+
     /* Cleanup the pipe's semaphores.  */
     kwsysProcessCleanupHandle(&cp->Pipe[i].Ready);
     kwsysProcessCleanupHandle(&cp->Pipe[i].Empty);
-    }  
-  
+    }
+
   /* Close the shared semaphores.  */
   kwsysProcessCleanupHandle(&cp->SharedIndexMutex);
   kwsysProcessCleanupHandle(&cp->Full);
-  
+
   /* Close the Win9x resume and kill event handles.  */
   if(cp->Win9x)
     {
     kwsysProcessCleanupHandle(&cp->Win9xResumeEvent);
     kwsysProcessCleanupHandle(&cp->Win9xKillEvent);
     }
-  
+
   /* Free memory.  */
   kwsysProcess_SetCommand(cp, 0);
   kwsysProcess_SetWorkingDirectory(cp, 0);
@@ -542,11 +542,11 @@ int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
         break;
         }
       }
-      
+
     /* Add the length of the argument, plus 1 for the space
          separating the arguments.  */
     length += (int)strlen(*arg) + 1;
-      
+
     if(spaces)
       {
       /* Add 2 for double quotes since spaces are present.  */
@@ -575,12 +575,12 @@ int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
           backslashes = 0;
           }
         }
-      
+
       /* We need to escape all ending backslashes. */
       length += backslashes;
       }
     }
-    
+
   /* Allocate enough space for the command.  We do not need an extra
        byte for the terminating null because we allocated a space for
        the first argument that we will not use.  */
@@ -591,7 +591,7 @@ int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
     free(newCommands);
     return 0;
     }
-    
+
   /* Construct the command line in the allocated buffer.  */
   cmd = newCommands[cp->NumberOfCommands];
   for(arg = command; *arg; ++arg)
@@ -611,19 +611,19 @@ int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
         spaces = 1;
         break;
         }
-      }      
-      
+      }
+
     /* Add the separating space if this is not the first argument.  */
     if(arg != command)
       {
       *cmd++ = ' ';
       }
-      
+
     if(spaces)
       {
       /* Add the opening double-quote for this argument.  */
       *cmd++ = '"';
-        
+
         /* Add the characters of the argument, possibly escaping them.  */
       for(c=*arg; *c; ++c)
         {
@@ -642,10 +642,10 @@ int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
             --backslashes;
             *cmd++ = '\\';
             }
-            
+
           /* Add the backslash to escape the double-quote.  */
           *cmd++ = '\\';
-            
+
           /* Add the double-quote itself.  */
           *cmd++ = '"';
           }
@@ -658,7 +658,7 @@ int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
           *cmd++ = *c;
           }
         }
-        
+
       /* Add enough backslashes to escape any trailing ones.  */
       while(backslashes > 0)
         {
@@ -781,7 +781,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
 
   /* Child startup control data.  */
   kwsysProcessCreateInformation si;
-  
+
   /* Do not execute a second time.  */
   if(cp->State == kwsysProcess_State_Executing)
     {
@@ -795,7 +795,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
     cp->State = kwsysProcess_State_Error;
     return;
     }
-  
+
   /* Reset the Win9x resume and kill events.  */
   if(cp->Win9x)
     {
@@ -814,12 +814,12 @@ void kwsysProcess_Execute(kwsysProcess* cp)
   /* Initialize startup info data.  */
   ZeroMemory(&si, sizeof(si));
   si.StartupInfo.cb = sizeof(si.StartupInfo);
-  
+
   /* Decide whether a child window should be shown.  */
   si.StartupInfo.dwFlags |= STARTF_USESHOWWINDOW;
   si.StartupInfo.wShowWindow =
     (unsigned short)(cp->HideWindow?SW_HIDE:SW_SHOWDEFAULT);
-  
+
   /* Connect the child's output pipes to the threads.  */
   si.StartupInfo.dwFlags |= STARTF_USESTDHANDLES;
 
@@ -831,7 +831,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
     kwsysProcessCleanup(cp, 1);
     return;
     }
-    
+
   /* Create an inherited duplicate of the write end, but do not
      close the non-inherited version.  We need to keep it open
      to use in waking up the pipe threads.  */
@@ -883,7 +883,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
   /* The timeout period starts now.  */
   cp->StartTime = kwsysProcessTimeGetCurrent();
   cp->TimeoutTime = kwsysProcessTimeFromDouble(-1);
-  
+
   /* All processes in the pipeline have been started in suspended
      mode.  Resume them all now.  */
   if(cp->Win9x)
@@ -898,7 +898,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
       }
     }
 
-  /* ---- It is no longer safe to call kwsysProcessCleanup. ----- */  
+  /* ---- It is no longer safe to call kwsysProcessCleanup. ----- */
   /* Tell the pipe threads that a process has started.  */
   for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
     {
@@ -910,11 +910,11 @@ void kwsysProcess_Execute(kwsysProcess* cp)
     {
     kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
     }
-  
+
   /* No pipe has reported data.  */
   cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
   cp->PipesLeft = KWSYSPE_PIPE_COUNT;
-  
+
   /* The process has now started.  */
   cp->State = kwsysProcess_State_Executing;
 }
@@ -940,14 +940,14 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
     {
     return 0;
     }
-  
+
   /* Record the time at which user timeout period starts.  */
   userStartTime = kwsysProcessTimeGetCurrent();
-  
+
   /* Calculate the time at which a timeout will expire, and whether it
      is the user or process timeout.  */
   user = kwsysProcessGetTimeoutTime(cp, userTimeout, &timeoutTime);
-  
+
   /* Loop until we have a reason to return.  */
   while(!done && cp->PipesLeft > 0)
     {
@@ -958,7 +958,7 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
       ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Empty, 1, 0);
       cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
       }
-    
+
     /* Setup a timeout if required.  */
     if(kwsysProcessGetTimeoutLeft(&timeoutTime, &timeoutLength))
       {
@@ -974,7 +974,7 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
       {
       timeout = kwsysProcessTimeToDWORD(timeoutLength);
       }
-    
+
     /* Wait for a pipe's thread to signal or a process to terminate.  */
     w = WaitForMultipleObjects(cp->ProcessEventsLength, cp->ProcessEvents,
                                0, timeout);
@@ -990,7 +990,7 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
          The thread will block until we signal its Empty mutex.  */
       cp->CurrentIndex = cp->SharedIndex;
       ReleaseSemaphore(cp->SharedIndexMutex, 1, 0);
-      
+
       /* Data are available or a pipe closed.  */
       if(cp->Pipe[cp->CurrentIndex].Closed)
         {
@@ -1016,7 +1016,7 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
       kwsysProcessDestroy(cp, w-WAIT_OBJECT_0);
       }
     }
-  
+
   /* Update the user timeout.  */
   if(userTimeout)
     {
@@ -1030,7 +1030,7 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
       *userTimeout = 0;
       }
     }
-  
+
   /* Check what happened.  */
   if(pipeId)
     {
@@ -1066,13 +1066,13 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
 {
   int i;
   int pipe;
-  
+
   /* Make sure we are executing a process.  */
   if(cp->State != kwsysProcess_State_Executing)
     {
     return 1;
     }
-  
+
   /* Wait for the process to terminate.  Ignore all data.  */
   while((pipe = kwsysProcess_WaitForData(cp, 0, 0, 0, userTimeout)) > 0)
     {
@@ -1096,11 +1096,11 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
     {
     WaitForSingleObject(cp->Pipe[i].Reset, INFINITE);
     }
-  
+
   /* ---- It is now safe again to call kwsysProcessCleanup. ----- */
   /* Close all the pipes.  */
   kwsysProcessCleanup(cp, 0);
-  
+
   /* Determine the outcome.  */
   if(cp->Killed)
     {
@@ -1122,7 +1122,7 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
       cp->State = kwsysProcess_State_Exception;
       switch (cp->ExitCode)
         {
-        case CONTROL_C_EXIT:          
+        case CONTROL_C_EXIT:
           cp->ExitException = kwsysProcess_Exception_Interrupt; break;
 
         case EXCEPTION_FLT_DENORMAL_OPERAND:
@@ -1170,29 +1170,29 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
 void kwsysProcess_Kill(kwsysProcess* cp)
 {
   int i;
-  
+
   /* Make sure we are executing a process.  */
   if(cp->State != kwsysProcess_State_Executing || cp->TimeoutExpired ||
      cp->Killed || cp->Terminated)
     {
     return;
     }
-  
+
   /* If we are killing a process that just reported data, release
      the pipe's thread.  */
   if(cp->CurrentIndex < KWSYSPE_PIPE_COUNT)
     {
     ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Empty, 1, 0);
     cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
     }
-  
+
   /* Wake up all the pipe threads with dummy data.  */
   for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
     {
     DWORD dummy;
     WriteFile(cp->Pipe[i].Write, "", 1, &dummy, 0);
     }
-  
+
   /* Tell pipe threads to reset until we run another process.  */
   while(cp->PipesLeft > 0)
     {
@@ -1203,7 +1203,7 @@ void kwsysProcess_Kill(kwsysProcess* cp)
     ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Empty, 1, 0);
     --cp->PipesLeft;
     }
-  
+
   /* Kill the children.  */
   cp->Killed = 1;
   if(cp->Win9x)
@@ -1237,17 +1237,17 @@ DWORD WINAPI kwsysProcessPipeThread(LPVOID ptd)
 {
   kwsysProcessPipeData* td = (kwsysProcessPipeData*)ptd;
   kwsysProcess* cp = td->Process;
-  
+
   /* Wait for a process to be ready.  */
   while((WaitForSingleObject(td->Ready, INFINITE), !cp->Deleting))
     {
     /* Read output from the process for this thread's pipe.  */
     kwsysProcessPipeThreadReadPipe(cp, td);
-    
+
     /* We were signalled to exit with our buffer empty.  Reset the
        mutex for a new process.  */
     ReleaseSemaphore(td->Empty, 1, 0);
-    
+
     /* Signal the main thread we have reset for a new process.  */
     ReleaseSemaphore(td->Reset, 1, 0);
     }
@@ -1273,14 +1273,14 @@ void kwsysProcessPipeThreadReadPipe(kwsysProcess* cp, kwsysProcessPipeData* td)
         {
         /* UNEXPECTED failure to read the pipe.  */
         }
-      
+
       /* The pipe closed.  There are no more data to read.  */
       td->Closed = 1;
       }
-    
+
     /* Wait for our turn to be handled by the main thread.  */
     WaitForSingleObject(cp->SharedIndexMutex, INFINITE);
-    
+
     /* Tell the main thread we have something to report.  */
     cp->SharedIndex = td->Index;
     ReleaseSemaphore(cp->Full, 1, 0);
@@ -1298,10 +1298,10 @@ int kwsysProcessInitialize(kwsysProcess* cp)
   cp->ExitException = kwsysProcess_Exception_None;
   cp->ExitCode = 1;
   cp->ExitValue = 1;
-  
+
   /* Reset error data.  */
   cp->ErrorMessage[0] = 0;
-  
+
   /* Allocate process information for each process.  */
   cp->ProcessInformation =
     (PROCESS_INFORMATION*)malloc(sizeof(PROCESS_INFORMATION) *
@@ -1405,7 +1405,7 @@ int kwsysProcessCreate(kwsysProcess* cp, int index,
       {
       return 0;
       }
-    
+
     /* Create an inherited duplicate of the write end.  This also closes
        the non-inherited version. */
     if(!DuplicateHandle(GetCurrentProcess(), si->ErrorPipeWrite,
@@ -1561,7 +1561,7 @@ void kwsysProcessCleanupHandle(PHANDLE h)
 void kwsysProcessCleanup(kwsysProcess* cp, int error)
 {
   int i;
-  
+
   /* If this is an error case, report the error.  */
   if(error)
     {
@@ -1585,7 +1585,7 @@ void kwsysProcessCleanup(kwsysProcess* cp, int error)
       }
 
     /* Remove trailing period and newline, if any.  */
-    kwsysProcessCleanErrorMessage(cp);    
+    kwsysProcessCleanErrorMessage(cp);
 
     /* Set the error state.  */
     cp->State = kwsysProcess_State_Error;
@@ -1607,7 +1607,7 @@ void kwsysProcessCleanup(kwsysProcess* cp, int error)
             WaitForSingleObject(cp->ProcessInformation[i].hProcess, INFINITE);
             }
           }
-        }      
+        }
       for(i=0; i < cp->NumberOfCommands; ++i)
         {
         kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
@@ -1633,7 +1633,7 @@ void kwsysProcessCleanup(kwsysProcess* cp, int error)
     {
     kwsysProcessCleanupHandle(&cp->Pipe[i].Write);
     kwsysProcessCleanupHandle(&cp->Pipe[i].Read);
-    }  
+    }
 }
 
 /*--------------------------------------------------------------------------*/
@@ -1669,11 +1669,11 @@ int kwsysProcessGetTimeoutTime(kwsysProcess* cp, double* userTimeout,
     {
     kwsysProcessTime length = kwsysProcessTimeFromDouble(cp->Timeout);
     cp->TimeoutTime = kwsysProcessTimeAdd(cp->StartTime, length);
-    }  
-  
+    }
+
   /* Start with process timeout.  */
   *timeoutTime = cp->TimeoutTime;
-  
+
   /* Check if the user timeout is earlier.  */
   if(userTimeout)
     {