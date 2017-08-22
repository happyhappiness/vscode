@@ -109,14 +109,15 @@ static DWORD WINAPI kwsysProcessPipeThreadWake(LPVOID ptd);
 static void kwsysProcessPipeThreadWakePipe(kwsysProcess* cp,
                                            kwsysProcessPipeData* td);
 static int kwsysProcessInitialize(kwsysProcess* cp);
-static int kwsysProcessCreate(kwsysProcess* cp, int index,
-                              kwsysProcessCreateInformation* si);
+static DWORD kwsysProcessCreate(kwsysProcess* cp, int index,
+                                kwsysProcessCreateInformation* si);
 static void kwsysProcessDestroy(kwsysProcess* cp, int event);
-static int kwsysProcessSetupOutputPipeFile(PHANDLE handle, const char* name);
+static DWORD kwsysProcessSetupOutputPipeFile(PHANDLE handle,
+                                             const char* name);
 static void kwsysProcessSetupSharedPipe(DWORD nStdHandle, PHANDLE handle);
 static void kwsysProcessSetupPipeNative(HANDLE native, PHANDLE handle);
 static void kwsysProcessCleanupHandle(PHANDLE h);
-static void kwsysProcessCleanup(kwsysProcess* cp, int error);
+static void kwsysProcessCleanup(kwsysProcess* cp, DWORD error);
 static void kwsysProcessCleanErrorMessage(kwsysProcess* cp);
 static int kwsysProcessGetTimeoutTime(kwsysProcess* cp, double* userTimeout,
                                       kwsysProcessTime* timeoutTime);
@@ -133,6 +134,13 @@ static kwsysProcessTime kwsysProcessTimeSubtract(kwsysProcessTime in1, kwsysProc
 static void kwsysProcessSetExitException(kwsysProcess* cp, int code);
 static void kwsysProcessKillTree(int pid);
 static void kwsysProcessDisablePipeThreads(kwsysProcess* cp);
+static int kwsysProcessesInitialize(void);
+static int kwsysTryEnterCreateProcessSection(void);
+static void kwsysLeaveCreateProcessSection(void);
+static int kwsysProcessesAdd(HANDLE hProcess, DWORD dwProcessId,
+                             int newProcessGroup);
+static void kwsysProcessesRemove(HANDLE hProcess);
+static BOOL WINAPI kwsysCtrlHandler(DWORD dwCtrlType);
 
 /*--------------------------------------------------------------------------*/
 /* A structure containing synchronization data for each thread.  */
@@ -222,6 +230,9 @@ struct kwsysProcess_s
   /* Whether to merge stdout/stderr of the child.  */
   int MergeOutput;
 
+  /* Whether to create the process in a new process group.  */
+  int CreateProcessGroup;
+
   /* Mutex to protect the shared index used by threads to report data.  */
   HANDLE SharedIndexMutex;
 
@@ -321,6 +332,16 @@ kwsysProcess* kwsysProcess_New(void)
   /* Windows version number data.  */
   OSVERSIONINFO osv;
 
+  /* Initialize list of processes before we get any farther.  It's especially
+     important that the console Ctrl handler be added BEFORE starting the
+     first process.  This prevents the risk of an orphaned process being
+     started by the main thread while the default Ctrl handler is in
+     progress.  */
+  if(!kwsysProcessesInitialize())
+    {
+    return 0;
+    }
+
   /* Allocate a process control structure.  */
   cp = (kwsysProcess*)malloc(sizeof(kwsysProcess));
   if(!cp)
@@ -836,6 +857,8 @@ int kwsysProcess_GetOption(kwsysProcess* cp, int optionId)
     case kwsysProcess_Option_HideWindow: return cp->HideWindow;
     case kwsysProcess_Option_MergeOutput: return cp->MergeOutput;
     case kwsysProcess_Option_Verbatim: return cp->Verbatim;
+    case kwsysProcess_Option_CreateProcessGroup:
+      return cp->CreateProcessGroup;
     default: return 0;
     }
 }
@@ -854,6 +877,8 @@ void kwsysProcess_SetOption(kwsysProcess* cp, int optionId, int value)
     case kwsysProcess_Option_HideWindow: cp->HideWindow = value; break;
     case kwsysProcess_Option_MergeOutput: cp->MergeOutput = value; break;
     case kwsysProcess_Option_Verbatim: cp->Verbatim = value; break;
+    case kwsysProcess_Option_CreateProcessGroup:
+      cp->CreateProcessGroup = value; break;
     default: break;
     }
 }
@@ -945,7 +970,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
     if(!GetCurrentDirectoryW(cp->RealWorkingDirectoryLength,
                             cp->RealWorkingDirectory))
       {
-      kwsysProcessCleanup(cp, 1);
+      kwsysProcessCleanup(cp, GetLastError());
       return;
       }
     SetCurrentDirectoryW(cp->WorkingDirectory);
@@ -957,14 +982,16 @@ void kwsysProcess_Execute(kwsysProcess* cp)
     {
     /* Create a handle to read a file for stdin.  */
     wchar_t* wstdin = kwsysEncoding_DupToWide(cp->PipeFileSTDIN);
+    DWORD error;
     cp->PipeChildStd[0] =
       CreateFileW(wstdin, GENERIC_READ|GENERIC_WRITE,
                   FILE_SHARE_READ|FILE_SHARE_WRITE,
                   0, OPEN_EXISTING, 0, 0);
+    error = GetLastError(); /* Check now in case free changes this.  */
     free(wstdin);
     if(cp->PipeChildStd[0] == INVALID_HANDLE_VALUE)
       {
-      kwsysProcessCleanup(cp, 1);
+      kwsysProcessCleanup(cp, error);
       return;
       }
     }
@@ -990,17 +1017,18 @@ void kwsysProcess_Execute(kwsysProcess* cp)
   if(!CreatePipe(&cp->Pipe[KWSYSPE_PIPE_STDOUT].Read,
                  &cp->Pipe[KWSYSPE_PIPE_STDOUT].Write, 0, 0))
     {
-    kwsysProcessCleanup(cp, 1);
+    kwsysProcessCleanup(cp, GetLastError());
     return;
     }
 
   if(cp->PipeFileSTDOUT)
     {
     /* Use a file for stdout.  */
-    if(!kwsysProcessSetupOutputPipeFile(&cp->PipeChildStd[1],
-                                        cp->PipeFileSTDOUT))
+    DWORD error = kwsysProcessSetupOutputPipeFile(&cp->PipeChildStd[1],
+                                                  cp->PipeFileSTDOUT);
+    if(error)
       {
-      kwsysProcessCleanup(cp, 1);
+      kwsysProcessCleanup(cp, error);
       return;
       }
     }
@@ -1023,7 +1051,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
                         GetCurrentProcess(), &cp->PipeChildStd[1],
                         0, FALSE, DUPLICATE_SAME_ACCESS))
       {
-      kwsysProcessCleanup(cp, 1);
+      kwsysProcessCleanup(cp, GetLastError());
       return;
       }
     }
@@ -1034,17 +1062,18 @@ void kwsysProcess_Execute(kwsysProcess* cp)
   if(!CreatePipe(&cp->Pipe[KWSYSPE_PIPE_STDERR].Read,
                  &cp->Pipe[KWSYSPE_PIPE_STDERR].Write, 0, 0))
     {
-    kwsysProcessCleanup(cp, 1);
+    kwsysProcessCleanup(cp, GetLastError());
     return;
     }
 
   if(cp->PipeFileSTDERR)
     {
     /* Use a file for stderr.  */
-    if(!kwsysProcessSetupOutputPipeFile(&cp->PipeChildStd[2],
-                                        cp->PipeFileSTDERR))
+    DWORD error = kwsysProcessSetupOutputPipeFile(&cp->PipeChildStd[2],
+                                                  cp->PipeFileSTDERR);
+    if(error)
       {
-      kwsysProcessCleanup(cp, 1);
+      kwsysProcessCleanup(cp, error);
       return;
       }
     }
@@ -1067,7 +1096,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
                         GetCurrentProcess(), &cp->PipeChildStd[2],
                         0, FALSE, DUPLICATE_SAME_ACCESS))
       {
-      kwsysProcessCleanup(cp, 1);
+      kwsysProcessCleanup(cp, GetLastError());
       return;
       }
     }
@@ -1106,11 +1135,12 @@ void kwsysProcess_Execute(kwsysProcess* cp)
       HANDLE p[2] = {INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE};
       if (!CreatePipe(&p[0], &p[1], 0, 0))
         {
+        DWORD error = GetLastError();
         if (nextStdInput != cp->PipeChildStd[0])
           {
           kwsysProcessCleanupHandle(&nextStdInput);
           }
-        kwsysProcessCleanup(cp, 1);
+        kwsysProcessCleanup(cp, error);
         return;
         }
       nextStdInput = p[0];
@@ -1119,7 +1149,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
     si.hStdError = cp->MergeOutput? cp->PipeChildStd[1] : cp->PipeChildStd[2];
 
     {
-    int res = kwsysProcessCreate(cp, i, &si);
+    DWORD error = kwsysProcessCreate(cp, i, &si);
 
     /* Close our copies of pipes used between children.  */
     if (si.hStdInput != cp->PipeChildStd[0])
@@ -1134,7 +1164,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
       {
       kwsysProcessCleanupHandle(&si.hStdError);
       }
-    if (res)
+    if (!error)
       {
       cp->ProcessEvents[i+1] = cp->ProcessInformation[i].hProcess;
       }
@@ -1144,7 +1174,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
         {
         kwsysProcessCleanupHandle(&nextStdInput);
         }
-      kwsysProcessCleanup(cp, 1);
+      kwsysProcessCleanup(cp, error);
       return;
       }
     }
@@ -1460,6 +1490,52 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
 }
 
 /*--------------------------------------------------------------------------*/
+void kwsysProcess_Interrupt(kwsysProcess* cp)
+{
+  int i;
+  /* Make sure we are executing a process.  */
+  if(!cp || cp->State != kwsysProcess_State_Executing || cp->TimeoutExpired ||
+     cp->Killed)
+    {
+    KWSYSPE_DEBUG((stderr, "interrupt: child not executing\n"));
+    return;
+    }
+
+  /* Skip actually interrupting the child if it has already terminated.  */
+  if(cp->Terminated)
+    {
+    KWSYSPE_DEBUG((stderr, "interrupt: child already terminated\n"));
+    return;
+    }
+
+  /* Interrupt the children.  */
+  if (cp->CreateProcessGroup)
+    {
+    if(cp->ProcessInformation)
+      {
+      for(i=0; i < cp->NumberOfCommands; ++i)
+        {
+        /* Make sure the process handle isn't closed (e.g. from disowning). */
+        if(cp->ProcessInformation[i].hProcess)
+          {
+          /* The user created a process group for this process.  The group ID
+             is the process ID for the original process in the group.  Note
+             that we have to use Ctrl+Break: Ctrl+C is not allowed for process
+             groups.  */
+          GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT,
+                                   cp->ProcessInformation[i].dwProcessId);
+          }
+        }
+      }
+    }
+  else
+    {
+    /* No process group was created.  Kill our own process group...  */
+    GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, 0);
+    }
+}
+
+/*--------------------------------------------------------------------------*/
 void kwsysProcess_Kill(kwsysProcess* cp)
 {
   int i;
@@ -1487,7 +1563,8 @@ void kwsysProcess_Kill(kwsysProcess* cp)
   for(i=0; i < cp->NumberOfCommands; ++i)
     {
     kwsysProcessKillTree(cp->ProcessInformation[i].dwProcessId);
-    // close the handle if we kill it
+    /* Remove from global list of processes and close handles.  */
+    kwsysProcessesRemove(cp->ProcessInformation[i].hProcess);
     kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
     kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hProcess);
     }
@@ -1686,7 +1763,7 @@ int kwsysProcessInitialize(kwsysProcess* cp)
 }
 
 /*--------------------------------------------------------------------------*/
-static int kwsysProcessCreateChildHandle(PHANDLE out, HANDLE in, int isStdIn)
+static DWORD kwsysProcessCreateChildHandle(PHANDLE out, HANDLE in, int isStdIn)
 {
   DWORD flags;
 
@@ -1697,13 +1774,19 @@ static int kwsysProcessCreateChildHandle(PHANDLE out, HANDLE in, int isStdIn)
     if (flags & HANDLE_FLAG_INHERIT)
       {
       *out = in;
-      return 1;
+      return ERROR_SUCCESS;
       }
 
     /* Create an inherited copy of this handle.  */
-    return DuplicateHandle(GetCurrentProcess(), in,
-                           GetCurrentProcess(), out,
-                           0, TRUE, DUPLICATE_SAME_ACCESS);
+    if (DuplicateHandle(GetCurrentProcess(), in, GetCurrentProcess(), out,
+                        0, TRUE, DUPLICATE_SAME_ACCESS))
+      {
+      return ERROR_SUCCESS;
+      }
+    else
+      {
+      return GetLastError();
+      }
     }
   else
     {
@@ -1719,29 +1802,46 @@ static int kwsysProcessCreateChildHandle(PHANDLE out, HANDLE in, int isStdIn)
                         (GENERIC_WRITE | FILE_READ_ATTRIBUTES)),
                        FILE_SHARE_READ|FILE_SHARE_WRITE,
                        &sa, OPEN_EXISTING, 0, 0);
-    return *out != INVALID_HANDLE_VALUE;
+    return (*out != INVALID_HANDLE_VALUE) ? ERROR_SUCCESS : GetLastError();
     }
-
 }
 
 /*--------------------------------------------------------------------------*/
-int kwsysProcessCreate(kwsysProcess* cp, int index,
-                       kwsysProcessCreateInformation* si)
+DWORD kwsysProcessCreate(kwsysProcess* cp, int index,
+                         kwsysProcessCreateInformation* si)
 {
-  int res =
+  DWORD creationFlags;
+  DWORD error = ERROR_SUCCESS;
+
+  /* Check if we are currently exiting.  */
+  if (!kwsysTryEnterCreateProcessSection())
+    {
+    /* The Ctrl handler is currently working on exiting our process.  Rather
+    than return an error code, which could cause incorrect conclusions to be
+    reached by the caller, we simply hang.  (For example, a CMake try_run
+    configure step might cause the project to configure wrong.)  */
+    Sleep(INFINITE);
+    }
 
-    /* Create inherited copies the handles.  */
-    kwsysProcessCreateChildHandle(&si->StartupInfo.hStdInput,
-                                  si->hStdInput, 1) &&
-    kwsysProcessCreateChildHandle(&si->StartupInfo.hStdOutput,
-                                  si->hStdOutput, 0) &&
-    kwsysProcessCreateChildHandle(&si->StartupInfo.hStdError,
-                                  si->hStdError, 0) &&
+  /* Create the child in a suspended state so we can wait until all
+     children have been created before running any one.  */
+  creationFlags = CREATE_SUSPENDED;
+  if (cp->CreateProcessGroup)
+    {
+    creationFlags |= CREATE_NEW_PROCESS_GROUP;
+    }
 
-    /* Create the child in a suspended state so we can wait until all
-       children have been created before running any one.  */
-    CreateProcessW(0, cp->Commands[index], 0, 0, TRUE, CREATE_SUSPENDED, 0,
-                   0, &si->StartupInfo, &cp->ProcessInformation[index]);
+  /* Create inherited copies of the handles.  */
+  (error = kwsysProcessCreateChildHandle(&si->StartupInfo.hStdInput,
+                                          si->hStdInput, 1)) ||
+  (error = kwsysProcessCreateChildHandle(&si->StartupInfo.hStdOutput,
+                                          si->hStdOutput, 0)) ||
+  (error = kwsysProcessCreateChildHandle(&si->StartupInfo.hStdError,
+                                          si->hStdError, 0)) ||
+  /* Create the process.  */
+  (!CreateProcessW(0, cp->Commands[index], 0, 0, TRUE, creationFlags, 0,
+                  0, &si->StartupInfo, &cp->ProcessInformation[index]) &&
+    (error = GetLastError()));
 
   /* Close the inherited copies of the handles. */
   if (si->StartupInfo.hStdInput != si->hStdInput)
@@ -1757,7 +1857,23 @@ int kwsysProcessCreate(kwsysProcess* cp, int index,
     kwsysProcessCleanupHandle(&si->StartupInfo.hStdError);
     }
 
-  return res;
+  /* Add the process to the global list of processes. */
+  if (!error &&
+      !kwsysProcessesAdd(cp->ProcessInformation[index].hProcess,
+      cp->ProcessInformation[index].dwProcessId, cp->CreateProcessGroup))
+    {
+    /* This failed for some reason.  Kill the suspended process. */
+    TerminateProcess(cp->ProcessInformation[index].hProcess, 1);
+    /* And clean up... */
+    kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hProcess);
+    kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hThread);
+    strcpy(cp->ErrorMessage, "kwsysProcessesAdd function failed");
+    error = ERROR_NOT_ENOUGH_MEMORY; /* Most likely reason.  */
+    }
+
+  /* If the console Ctrl handler is waiting for us, this will release it... */
+  kwsysLeaveCreateProcessSection();
+  return error;
 }
 
 /*--------------------------------------------------------------------------*/
@@ -1779,6 +1895,9 @@ void kwsysProcessDestroy(kwsysProcess* cp, int event)
   GetExitCodeProcess(cp->ProcessInformation[index].hProcess,
                      &cp->CommandExitCodes[index]);
 
+  /* Remove from global list of processes.  */
+  kwsysProcessesRemove(cp->ProcessInformation[index].hProcess);
+
   /* Close the process handle for the terminated process.  */
   kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hProcess);
 
@@ -1813,13 +1932,14 @@ void kwsysProcessDestroy(kwsysProcess* cp, int event)
 }
 
 /*--------------------------------------------------------------------------*/
-int kwsysProcessSetupOutputPipeFile(PHANDLE phandle, const char* name)
+DWORD kwsysProcessSetupOutputPipeFile(PHANDLE phandle, const char* name)
 {
   HANDLE fout;
   wchar_t* wname;
+  DWORD error;
   if(!name)
     {
-    return 1;
+    return ERROR_INVALID_PARAMETER;
     }
 
   /* Close the existing handle.  */
@@ -1829,15 +1949,16 @@ int kwsysProcessSetupOutputPipeFile(PHANDLE phandle, const char* name)
   wname = kwsysEncoding_DupToWide(name);
   fout = CreateFileW(wname, GENERIC_WRITE, FILE_SHARE_READ, 0,
                     CREATE_ALWAYS, 0, 0);
+  error = GetLastError();
   free(wname);
   if(fout == INVALID_HANDLE_VALUE)
     {
-    return 0;
+    return error;
     }
 
   /* Assign the replacement handle.  */
   *phandle = fout;
-  return 1;
+  return ERROR_SUCCESS;
 }
 
 /*--------------------------------------------------------------------------*/
@@ -1876,7 +1997,7 @@ void kwsysProcessCleanupHandle(PHANDLE h)
 /*--------------------------------------------------------------------------*/
 
 /* Close all handles created by kwsysProcess_Execute.  */
-void kwsysProcessCleanup(kwsysProcess* cp, int error)
+void kwsysProcessCleanup(kwsysProcess* cp, DWORD error)
 {
   int i;
   /* If this is an error case, report the error.  */
@@ -1886,21 +2007,27 @@ void kwsysProcessCleanup(kwsysProcess* cp, int error)
     if(cp->ErrorMessage[0] == 0)
       {
       /* Format the error message.  */
-      DWORD original = GetLastError();
       wchar_t err_msg[KWSYSPE_PIPE_BUFFER_SIZE];
       DWORD length = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
-                                   FORMAT_MESSAGE_IGNORE_INSERTS, 0, original,
+                                   FORMAT_MESSAGE_IGNORE_INSERTS, 0, error,
                                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                    err_msg, KWSYSPE_PIPE_BUFFER_SIZE, 0);
-      WideCharToMultiByte(CP_UTF8, 0, err_msg, -1, cp->ErrorMessage,
-                          KWSYSPE_PIPE_BUFFER_SIZE, NULL, NULL);
       if(length < 1)
         {
         /* FormatMessage failed.  Use a default message.  */
         _snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE,
                   "Process execution failed with error 0x%X.  "
                   "FormatMessage failed with error 0x%X",
-                  original, GetLastError());
+                  error, GetLastError());
+        }
+      if(!WideCharToMultiByte(CP_UTF8, 0, err_msg, -1, cp->ErrorMessage,
+                              KWSYSPE_PIPE_BUFFER_SIZE, NULL, NULL))
+        {
+        /* WideCharToMultiByte failed.  Use a default message.  */
+        _snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE,
+                  "Process execution failed with error 0x%X.  "
+                  "WideCharToMultiByte failed with error 0x%X",
+                  error, GetLastError());
         }
       }
 
@@ -1923,6 +2050,8 @@ void kwsysProcessCleanup(kwsysProcess* cp, int error)
         }
       for(i=0; i < cp->NumberOfCommands; ++i)
         {
+        /* Remove from global list of processes and close handles.  */
+        kwsysProcessesRemove(cp->ProcessInformation[i].hProcess);
         kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
         kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hProcess);
         }
@@ -2659,3 +2788,230 @@ static void kwsysProcessDisablePipeThreads(kwsysProcess* cp)
     ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Reader.Go, 1, 0);
     }
 }
+
+/*--------------------------------------------------------------------------*/
+/* Global set of executing processes for use by the Ctrl handler.
+   This global instance will be zero-initialized by the compiler.
+
+   Note that the console Ctrl handler runs on a background thread and so
+   everything it does must be thread safe.  Here, we track the hProcess
+   HANDLEs directly instead of kwsysProcess instances, so that we don't have
+   to make kwsysProcess thread safe.  */
+typedef struct kwsysProcessInstance_s
+{
+  HANDLE hProcess;
+  DWORD dwProcessId;
+  int NewProcessGroup; /* Whether the process was created in a new group.  */
+} kwsysProcessInstance;
+
+typedef struct kwsysProcessInstances_s
+{
+  /* Whether we have initialized key fields below, like critical sections.  */
+  int Initialized;
+
+  /* Ctrl handler runs on a different thread, so we must sync access.  */
+  CRITICAL_SECTION Lock;
+
+  int Exiting;
+  size_t Count;
+  size_t Size;
+  kwsysProcessInstance* Processes;
+} kwsysProcessInstances;
+static kwsysProcessInstances kwsysProcesses;
+
+/*--------------------------------------------------------------------------*/
+/* Initialize critial section and set up console Ctrl handler.  You MUST call
+   this before using any other kwsysProcesses* functions below.  */
+static int kwsysProcessesInitialize(void)
+{
+  /* Initialize everything if not done already.  */
+  if(!kwsysProcesses.Initialized)
+    {
+    InitializeCriticalSection(&kwsysProcesses.Lock);
+
+    /* Set up console ctrl handler.  */
+    if(!SetConsoleCtrlHandler(kwsysCtrlHandler, TRUE))
+      {
+      return 0;
+      }
+
+    kwsysProcesses.Initialized = 1;
+    }
+  return 1;
+}
+
+/*--------------------------------------------------------------------------*/
+/* The Ctrl handler waits on the global list of processes.  To prevent an
+   orphaned process, do not create a new process if the Ctrl handler is
+   already running.  Do so by using this function to check if it is ok to
+   create a process.  */
+static int kwsysTryEnterCreateProcessSection(void)
+{
+  /* Enter main critical section; this means creating a process and the Ctrl
+     handler are mutually exclusive.  */
+  EnterCriticalSection(&kwsysProcesses.Lock);
+  /* Indicate to the caller if they can create a process.  */
+  if(kwsysProcesses.Exiting)
+    {
+    LeaveCriticalSection(&kwsysProcesses.Lock);
+    return 0;
+    }
+  else
+    {
+    return 1;
+    }
+}
+
+/*--------------------------------------------------------------------------*/
+/* Matching function on successful kwsysTryEnterCreateProcessSection return.
+   Make sure you called kwsysProcessesAdd if applicable before calling this.*/
+static void kwsysLeaveCreateProcessSection(void)
+{
+  LeaveCriticalSection(&kwsysProcesses.Lock);
+}
+
+/*--------------------------------------------------------------------------*/
+/* Add new process to global process list.  The Ctrl handler will wait for
+   the process to exit before it returns.  Do not close the process handle
+   until after calling kwsysProcessesRemove.  The newProcessGroup parameter
+   must be set if the process was created with CREATE_NEW_PROCESS_GROUP.  */
+static int kwsysProcessesAdd(HANDLE hProcess, DWORD dwProcessid,
+                             int newProcessGroup)
+{
+  if(!kwsysProcessesInitialize() || !hProcess ||
+      hProcess == INVALID_HANDLE_VALUE)
+    {
+    return 0;
+    }
+
+  /* Enter the critical section. */
+  EnterCriticalSection(&kwsysProcesses.Lock);
+
+  /* Make sure there is enough space for the new process handle.  */
+  if(kwsysProcesses.Count == kwsysProcesses.Size)
+    {
+    size_t newSize;
+    kwsysProcessInstance *newArray;
+    /* Start with enough space for a small number of process handles
+       and double the size each time more is needed.  */
+    newSize = kwsysProcesses.Size? kwsysProcesses.Size*2 : 4;
+
+    /* Try allocating the new block of memory.  */
+    if(newArray = (kwsysProcessInstance*)malloc(
+       newSize*sizeof(kwsysProcessInstance)))
+      {
+      /* Copy the old process handles to the new memory.  */
+      if(kwsysProcesses.Count > 0)
+        {
+        memcpy(newArray, kwsysProcesses.Processes,
+               kwsysProcesses.Count * sizeof(kwsysProcessInstance));
+        }
+      }
+    else
+      {
+      /* Failed to allocate memory for the new process handle set.  */
+      LeaveCriticalSection(&kwsysProcesses.Lock);
+      return 0;
+      }
+
+    /* Free original array. */
+    free(kwsysProcesses.Processes);
+
+    /* Update original structure with new allocation. */
+    kwsysProcesses.Size = newSize;
+    kwsysProcesses.Processes = newArray;
+    }
+
+  /* Append the new process information to the set.  */
+  kwsysProcesses.Processes[kwsysProcesses.Count].hProcess = hProcess;
+  kwsysProcesses.Processes[kwsysProcesses.Count].dwProcessId = dwProcessid;
+  kwsysProcesses.Processes[kwsysProcesses.Count++].NewProcessGroup =
+    newProcessGroup;
+
+  /* Leave critical section and return success. */
+  LeaveCriticalSection(&kwsysProcesses.Lock);
+
+  return 1;
+}
+
+/*--------------------------------------------------------------------------*/
+/* Removes process to global process list.  */
+static void kwsysProcessesRemove(HANDLE hProcess)
+{
+  size_t i;
+
+  if (!hProcess || hProcess == INVALID_HANDLE_VALUE)
+    {
+    return;
+    }
+
+  EnterCriticalSection(&kwsysProcesses.Lock);
+
+  /* Find the given process in the set.  */
+  for(i=0; i < kwsysProcesses.Count; ++i)
+    {
+    if(kwsysProcesses.Processes[i].hProcess == hProcess)
+      {
+      break;
+      }
+    }
+  if(i < kwsysProcesses.Count)
+    {
+    /* Found it!  Remove the process from the set.  */
+    --kwsysProcesses.Count;
+    for(; i < kwsysProcesses.Count; ++i)
+      {
+      kwsysProcesses.Processes[i] = kwsysProcesses.Processes[i+1];
+      }
+
+    /* If this was the last process, free the array.  */
+    if(kwsysProcesses.Count == 0)
+      {
+      kwsysProcesses.Size = 0;
+      free(kwsysProcesses.Processes);
+      kwsysProcesses.Processes = 0;
+      }
+    }
+
+  LeaveCriticalSection(&kwsysProcesses.Lock);
+}
+
+/*--------------------------------------------------------------------------*/
+static BOOL WINAPI kwsysCtrlHandler(DWORD dwCtrlType)
+{
+  size_t i;
+  (void)dwCtrlType;
+  /* Enter critical section.  */
+  EnterCriticalSection(&kwsysProcesses.Lock);
+
+  /* Set flag indicating that we are exiting.  */
+  kwsysProcesses.Exiting = 1;
+
+  /* If some of our processes were created in a new process group, we must
+     manually interrupt them.  They won't otherwise receive a Ctrl+C/Break. */
+  for(i=0; i < kwsysProcesses.Count; ++i)
+    {
+    if(kwsysProcesses.Processes[i].NewProcessGroup)
+      {
+      DWORD groupId = kwsysProcesses.Processes[i].dwProcessId;
+      if(groupId)
+        {
+        GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, groupId);
+        }
+      }
+    }
+
+  /* Wait for each child process to exit.  This is the key step that prevents
+     us from leaving several orphaned children processes running in the
+     background when the user presses Ctrl+C.  */
+  for(i=0; i < kwsysProcesses.Count; ++i)
+    {
+    WaitForSingleObject(kwsysProcesses.Processes[i].hProcess, INFINITE);
+    }
+
+  /* Leave critical section.  */
+  LeaveCriticalSection(&kwsysProcesses.Lock);
+
+  /* Continue on to default Ctrl handler (which calls ExitProcess).  */
+  return FALSE;
+}