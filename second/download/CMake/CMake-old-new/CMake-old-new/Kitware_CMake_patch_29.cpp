@@ -140,7 +140,6 @@ typedef struct kwsysProcessCreateInformation_s
   int ErrorPipe[2];
 } kwsysProcessCreateInformation;
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcessVolatileFree(volatile void* p);
 static int kwsysProcessInitialize(kwsysProcess* cp);
 static void kwsysProcessCleanup(kwsysProcess* cp, int error);
@@ -166,7 +165,8 @@ static kwsysProcessTime kwsysProcessTimeAdd(kwsysProcessTime in1,
                                             kwsysProcessTime in2);
 static kwsysProcessTime kwsysProcessTimeSubtract(kwsysProcessTime in1,
                                                  kwsysProcessTime in2);
-static void kwsysProcessSetExitException(kwsysProcess* cp, int sig);
+static void kwsysProcessSetExitExceptionByIndex(kwsysProcess* cp, int sig,
+                                                int idx);
 static void kwsysProcessChildErrorExit(int errorPipe);
 static void kwsysProcessRestoreDefaultSignalHandlers(void);
 static pid_t kwsysProcessFork(kwsysProcess* cp,
@@ -184,7 +184,26 @@ static void kwsysProcessesSignalHandler(int signum, siginfo_t* info,
 static void kwsysProcessesSignalHandler(int signum);
 #endif
 
-/*--------------------------------------------------------------------------*/
+/* A structure containing results data for each process.  */
+typedef struct kwsysProcessResults_s kwsysProcessResults;
+struct kwsysProcessResults_s
+{
+  /* The status of the child process. */
+  int State;
+
+  /* The exceptional behavior that terminated the process, if any.  */
+  int ExitException;
+
+  /* The process exit code.  */
+  int ExitCode;
+
+  /* The process return code, if any.  */
+  int ExitValue;
+
+  /* Description for the ExitException.  */
+  char ExitExceptionString[KWSYSPE_PIPE_BUFFER_SIZE + 1];
+};
+
 /* Structure containing data used to implement the child's execution.  */
 struct kwsysProcess_s
 {
@@ -255,28 +274,18 @@ struct kwsysProcess_s
   /* The number of children still executing.  */
   int CommandsLeft;
 
-  /* The current status of the child process.  Must be atomic because
+  /* The status of the process structure.  Must be atomic because
      the signal handler checks this to avoid a race.  */
   volatile sig_atomic_t State;
 
-  /* The exceptional behavior that terminated the child process, if
-   * any.  */
-  int ExitException;
-
-  /* The exit code of the child process.  */
-  int ExitCode;
-
-  /* The exit value of the child process, if any.  */
-  int ExitValue;
-
   /* Whether the process was killed.  */
   volatile sig_atomic_t Killed;
 
   /* Buffer for error message in case of failure.  */
   char ErrorMessage[KWSYSPE_PIPE_BUFFER_SIZE + 1];
 
-  /* Description for the ExitException.  */
-  char ExitExceptionString[KWSYSPE_PIPE_BUFFER_SIZE + 1];
+  /* process results.  */
+  kwsysProcessResults* ProcessResults;
 
   /* The exit codes of each child process in the pipeline.  */
   int* CommandExitCodes;
@@ -301,7 +310,6 @@ struct kwsysProcess_s
   char* RealWorkingDirectory;
 };
 
-/*--------------------------------------------------------------------------*/
 kwsysProcess* kwsysProcess_New(void)
 {
   /* Allocate a process control structure.  */
@@ -328,7 +336,6 @@ kwsysProcess* kwsysProcess_New(void)
   return cp;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_Delete(kwsysProcess* cp)
 {
   /* Make sure we have an instance.  */
@@ -354,10 +361,10 @@ void kwsysProcess_Delete(kwsysProcess* cp)
   if (cp->CommandExitCodes) {
     free(cp->CommandExitCodes);
   }
+  free(cp->ProcessResults);
   free(cp);
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_SetCommand(kwsysProcess* cp, char const* const* command)
 {
   int i;
@@ -382,7 +389,6 @@ int kwsysProcess_SetCommand(kwsysProcess* cp, char const* const* command)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
 {
   int newNumberOfCommands;
@@ -462,7 +468,6 @@ int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_SetTimeout(kwsysProcess* cp, double timeout)
 {
   if (!cp) {
@@ -476,7 +481,6 @@ void kwsysProcess_SetTimeout(kwsysProcess* cp, double timeout)
   cp->TimeoutTime.tv_sec = -1;
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_SetWorkingDirectory(kwsysProcess* cp, const char* dir)
 {
   if (!cp) {
@@ -502,7 +506,6 @@ int kwsysProcess_SetWorkingDirectory(kwsysProcess* cp, const char* dir)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_SetPipeFile(kwsysProcess* cp, int prPipe, const char* file)
 {
   char** pfile;
@@ -543,7 +546,6 @@ int kwsysProcess_SetPipeFile(kwsysProcess* cp, int prPipe, const char* file)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_SetPipeShared(kwsysProcess* cp, int prPipe, int shared)
 {
   if (!cp) {
@@ -572,7 +574,6 @@ void kwsysProcess_SetPipeShared(kwsysProcess* cp, int prPipe, int shared)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_SetPipeNative(kwsysProcess* cp, int prPipe, int p[2])
 {
   int* pPipeNative = 0;
@@ -612,7 +613,6 @@ void kwsysProcess_SetPipeNative(kwsysProcess* cp, int prPipe, int p[2])
   }
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_GetOption(kwsysProcess* cp, int optionId)
 {
   if (!cp) {
@@ -633,7 +633,6 @@ int kwsysProcess_GetOption(kwsysProcess* cp, int optionId)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_SetOption(kwsysProcess* cp, int optionId, int value)
 {
   if (!cp) {
@@ -658,31 +657,32 @@ void kwsysProcess_SetOption(kwsysProcess* cp, int optionId, int value)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_GetState(kwsysProcess* cp)
 {
   return cp ? cp->State : kwsysProcess_State_Error;
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_GetExitException(kwsysProcess* cp)
 {
-  return cp ? cp->ExitException : kwsysProcess_Exception_Other;
+  return (cp && cp->ProcessResults && (cp->NumberOfCommands > 0))
+    ? cp->ProcessResults[cp->NumberOfCommands - 1].ExitException
+    : kwsysProcess_Exception_Other;
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_GetExitCode(kwsysProcess* cp)
 {
-  return cp ? cp->ExitCode : 0;
+  return (cp && cp->ProcessResults && (cp->NumberOfCommands > 0))
+    ? cp->ProcessResults[cp->NumberOfCommands - 1].ExitCode
+    : 0;
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_GetExitValue(kwsysProcess* cp)
 {
-  return cp ? cp->ExitValue : -1;
+  return (cp && cp->ProcessResults && (cp->NumberOfCommands > 0))
+    ? cp->ProcessResults[cp->NumberOfCommands - 1].ExitValue
+    : -1;
 }
 
-/*--------------------------------------------------------------------------*/
 const char* kwsysProcess_GetErrorString(kwsysProcess* cp)
 {
   if (!cp) {
@@ -693,18 +693,58 @@ const char* kwsysProcess_GetErrorString(kwsysProcess* cp)
   return "Success";
 }
 
-/*--------------------------------------------------------------------------*/
 const char* kwsysProcess_GetExceptionString(kwsysProcess* cp)
 {
-  if (!cp) {
+  if (!(cp && cp->ProcessResults && (cp->NumberOfCommands > 0))) {
     return "GetExceptionString called with NULL process management structure";
   } else if (cp->State == kwsysProcess_State_Exception) {
-    return cp->ExitExceptionString;
+    return cp->ProcessResults[cp->NumberOfCommands - 1].ExitExceptionString;
+  }
+  return "No exception";
+}
+
+/* the index should be in array bound. */
+#define KWSYSPE_IDX_CHK(RET)                                                  \
+  if (!cp || idx >= cp->NumberOfCommands || idx < 0) {                        \
+    return RET;                                                               \
+  }
+
+int kwsysProcess_GetStateByIndex(kwsysProcess* cp, int idx)
+{
+  KWSYSPE_IDX_CHK(kwsysProcess_State_Error)
+  return cp->ProcessResults[idx].State;
+}
+
+int kwsysProcess_GetExitExceptionByIndex(kwsysProcess* cp, int idx)
+{
+  KWSYSPE_IDX_CHK(kwsysProcess_Exception_Other)
+  return cp->ProcessResults[idx].ExitException;
+}
+
+int kwsysProcess_GetExitValueByIndex(kwsysProcess* cp, int idx)
+{
+  KWSYSPE_IDX_CHK(-1)
+  return cp->ProcessResults[idx].ExitValue;
+}
+
+int kwsysProcess_GetExitCodeByIndex(kwsysProcess* cp, int idx)
+{
+  KWSYSPE_IDX_CHK(-1)
+  return cp->CommandExitCodes[idx];
+}
+
+const char* kwsysProcess_GetExceptionStringByIndex(kwsysProcess* cp, int idx)
+{
+  KWSYSPE_IDX_CHK("GetExceptionString called with NULL process management "
+                  "structure or index out of bound")
+  if (cp->ProcessResults[idx].State == kwsysProcess_StateByIndex_Exception) {
+    return cp->ProcessResults[idx].ExitExceptionString;
   }
   return "No exception";
 }
 
-/*--------------------------------------------------------------------------*/
+#undef KWSYSPE_IDX_CHK
+
 void kwsysProcess_Execute(kwsysProcess* cp)
 {
   int i;
@@ -990,7 +1030,6 @@ void kwsysProcess_Execute(kwsysProcess* cp)
   cp->Detached = cp->OptionDetach;
 }
 
-/*--------------------------------------------------------------------------*/
 kwsysEXPORT void kwsysProcess_Disown(kwsysProcess* cp)
 {
   /* Make sure a detached child process is running.  */
@@ -1009,7 +1048,6 @@ kwsysEXPORT void kwsysProcess_Disown(kwsysProcess* cp)
   cp->State = kwsysProcess_State_Disowned;
 }
 
-/*--------------------------------------------------------------------------*/
 typedef struct kwsysProcessWaitData_s
 {
   int Expired;
@@ -1021,7 +1059,6 @@ typedef struct kwsysProcessWaitData_s
 static int kwsysProcessWaitForPipe(kwsysProcess* cp, char** data, int* length,
                                    kwsysProcessWaitData* wd);
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_WaitForData(kwsysProcess* cp, char** data, int* length,
                              double* userTimeout)
 {
@@ -1083,7 +1120,6 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, char** data, int* length,
   }
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcessWaitForPipe(kwsysProcess* cp, char** data, int* length,
                                    kwsysProcessWaitData* wd)
 {
@@ -1285,10 +1321,8 @@ static int kwsysProcessWaitForPipe(kwsysProcess* cp, char** data, int* length,
 #endif
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
 {
-  int status = 0;
   int prPipe = 0;
 
   /* Make sure we are executing a process.  */
@@ -1319,40 +1353,43 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
     cp->State = kwsysProcess_State_Error;
     return 1;
   }
-
-  /* Use the status of the last process in the pipeline.  */
-  status = cp->CommandExitCodes[cp->NumberOfCommands - 1];
-
   /* Determine the outcome.  */
   if (cp->Killed) {
     /* We killed the child.  */
     cp->State = kwsysProcess_State_Killed;
   } else if (cp->TimeoutExpired) {
     /* The timeout expired.  */
     cp->State = kwsysProcess_State_Expired;
-  } else if (WIFEXITED(status)) {
-    /* The child exited normally.  */
-    cp->State = kwsysProcess_State_Exited;
-    cp->ExitException = kwsysProcess_Exception_None;
-    cp->ExitCode = status;
-    cp->ExitValue = (int)WEXITSTATUS(status);
-  } else if (WIFSIGNALED(status)) {
-    /* The child received an unhandled signal.  */
-    cp->State = kwsysProcess_State_Exception;
-    cp->ExitCode = status;
-    kwsysProcessSetExitException(cp, (int)WTERMSIG(status));
   } else {
-    /* Error getting the child return code.  */
-    strcpy(cp->ErrorMessage, "Error getting child return code.");
-    cp->State = kwsysProcess_State_Error;
+    /* The children exited.  Report the outcome of the child processes.  */
+    for (prPipe = 0; prPipe < cp->NumberOfCommands; ++prPipe) {
+      cp->ProcessResults[prPipe].ExitCode = cp->CommandExitCodes[prPipe];
+      if (WIFEXITED(cp->ProcessResults[prPipe].ExitCode)) {
+        /* The child exited normally.  */
+        cp->ProcessResults[prPipe].State = kwsysProcess_StateByIndex_Exited;
+        cp->ProcessResults[prPipe].ExitException = kwsysProcess_Exception_None;
+        cp->ProcessResults[prPipe].ExitValue =
+          (int)WEXITSTATUS(cp->ProcessResults[prPipe].ExitCode);
+      } else if (WIFSIGNALED(cp->ProcessResults[prPipe].ExitCode)) {
+        /* The child received an unhandled signal.  */
+        cp->ProcessResults[prPipe].State = kwsysProcess_State_Exception;
+        kwsysProcessSetExitExceptionByIndex(
+          cp, (int)WTERMSIG(cp->ProcessResults[prPipe].ExitCode), prPipe);
+      } else {
+        /* Error getting the child return code.  */
+        strcpy(cp->ProcessResults[prPipe].ExitExceptionString,
+               "Error getting child return code.");
+        cp->ProcessResults[prPipe].State = kwsysProcess_StateByIndex_Error;
+      }
+    }
+    /* support legacy state status value */
+    cp->State = cp->ProcessResults[cp->NumberOfCommands - 1].State;
   }
-
   /* Normal cleanup.  */
   kwsysProcessCleanup(cp, 0);
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_Interrupt(kwsysProcess* cp)
 {
   int i;
@@ -1384,7 +1421,6 @@ void kwsysProcess_Interrupt(kwsysProcess* cp)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_Kill(kwsysProcess* cp)
 {
   int i;
@@ -1431,7 +1467,6 @@ void kwsysProcess_Kill(kwsysProcess* cp)
   cp->CommandsLeft = 0;
 }
 
-/*--------------------------------------------------------------------------*/
 /* Call the free() function with a pointer to volatile without causing
    compiler warnings.  */
 static void kwsysProcessVolatileFree(volatile void* p)
@@ -1448,7 +1483,6 @@ static void kwsysProcessVolatileFree(volatile void* p)
 #endif
 }
 
-/*--------------------------------------------------------------------------*/
 /* Initialize a process control structure for kwsysProcess_Execute.  */
 static int kwsysProcessInitialize(kwsysProcess* cp)
 {
@@ -1474,11 +1508,7 @@ static int kwsysProcessInitialize(kwsysProcess* cp)
 #endif
   cp->State = kwsysProcess_State_Starting;
   cp->Killed = 0;
-  cp->ExitException = kwsysProcess_Exception_None;
-  cp->ExitCode = 1;
-  cp->ExitValue = 1;
   cp->ErrorMessage[0] = 0;
-  strcpy(cp->ExitExceptionString, "No exception");
 
   oldForkPIDs = cp->ForkPIDs;
   cp->ForkPIDs = (volatile pid_t*)malloc(sizeof(volatile pid_t) *
@@ -1504,6 +1534,23 @@ static int kwsysProcessInitialize(kwsysProcess* cp)
   memset(cp->CommandExitCodes, 0,
          sizeof(int) * (size_t)(cp->NumberOfCommands));
 
+  /* Allocate process result information for each process.  */
+  free(cp->ProcessResults);
+  cp->ProcessResults = (kwsysProcessResults*)malloc(
+    sizeof(kwsysProcessResults) * (size_t)(cp->NumberOfCommands));
+  if (!cp->ProcessResults) {
+    return 0;
+  }
+  memset(cp->ProcessResults, 0,
+         sizeof(kwsysProcessResults) * (size_t)(cp->NumberOfCommands));
+  for (i = 0; i < cp->NumberOfCommands; i++) {
+    cp->ProcessResults[i].ExitException = kwsysProcess_Exception_None;
+    cp->ProcessResults[i].State = kwsysProcess_StateByIndex_Starting;
+    cp->ProcessResults[i].ExitCode = 1;
+    cp->ProcessResults[i].ExitValue = 1;
+    strcpy(cp->ProcessResults[i].ExitExceptionString, "No exception");
+  }
+
   /* Allocate memory to save the real working directory.  */
   if (cp->WorkingDirectory) {
 #if defined(MAXPATHLEN)
@@ -1523,7 +1570,6 @@ static int kwsysProcessInitialize(kwsysProcess* cp)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 /* Free all resources used by the given kwsysProcess instance that were
    allocated by kwsysProcess_Execute.  */
 static void kwsysProcessCleanup(kwsysProcess* cp, int error)
@@ -1590,7 +1636,6 @@ static void kwsysProcessCleanup(kwsysProcess* cp, int error)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 /* Close the given file descriptor if it is open.  Reset its value to -1.  */
 static void kwsysProcessCleanupDescriptor(int* pfd)
 {
@@ -1603,7 +1648,6 @@ static void kwsysProcessCleanupDescriptor(int* pfd)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcessClosePipes(kwsysProcess* cp)
 {
   int i;
@@ -1636,7 +1680,6 @@ static void kwsysProcessClosePipes(kwsysProcess* cp)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcessSetNonBlocking(int fd)
 {
   int flags = fcntl(fd, F_GETFL);
@@ -1646,12 +1689,10 @@ static int kwsysProcessSetNonBlocking(int fd)
   return flags >= 0;
 }
 
-/*--------------------------------------------------------------------------*/
 #if defined(__VMS)
 int decc$set_child_standard_streams(int fd1, int fd2, int fd3);
 #endif
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcessCreate(kwsysProcess* cp, int prIndex,
                               kwsysProcessCreateInformation* si)
 {
@@ -1831,7 +1872,6 @@ static int kwsysProcessCreate(kwsysProcess* cp, int prIndex,
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcessDestroy(kwsysProcess* cp)
 {
   /* A child process has terminated.  Reap it if it is one handled by
@@ -1880,7 +1920,6 @@ static void kwsysProcessDestroy(kwsysProcess* cp)
   sigprocmask(SIG_SETMASK, &old_mask, 0);
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcessSetupOutputPipeFile(int* p, const char* name)
 {
   int fout;
@@ -1906,7 +1945,6 @@ static int kwsysProcessSetupOutputPipeFile(int* p, const char* name)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcessSetupOutputPipeNative(int* p, int des[2])
 {
   /* Close the existing descriptor.  */
@@ -1925,7 +1963,6 @@ static int kwsysProcessSetupOutputPipeNative(int* p, int des[2])
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 /* Get the time at which either the process or user timeout will
    expire.  Returns 1 if the user timeout is first, and 0 otherwise.  */
 static int kwsysProcessGetTimeoutTime(kwsysProcess* cp, double* userTimeout,
@@ -1957,7 +1994,6 @@ static int kwsysProcessGetTimeoutTime(kwsysProcess* cp, double* userTimeout,
   return 0;
 }
 
-/*--------------------------------------------------------------------------*/
 /* Get the length of time before the given timeout time arrives.
    Returns 1 if the time has already arrived, and 0 otherwise.  */
 static int kwsysProcessGetTimeoutLeft(kwsysProcessTime* timeoutTime,
@@ -1992,7 +2028,6 @@ static int kwsysProcessGetTimeoutLeft(kwsysProcessTime* timeoutTime,
   }
 }
 
-/*--------------------------------------------------------------------------*/
 static kwsysProcessTime kwsysProcessTimeGetCurrent(void)
 {
   kwsysProcessTime current;
@@ -2003,13 +2038,11 @@ static kwsysProcessTime kwsysProcessTimeGetCurrent(void)
   return current;
 }
 
-/*--------------------------------------------------------------------------*/
 static double kwsysProcessTimeToDouble(kwsysProcessTime t)
 {
   return (double)t.tv_sec + (double)(t.tv_usec) * 0.000001;
 }
 
-/*--------------------------------------------------------------------------*/
 static kwsysProcessTime kwsysProcessTimeFromDouble(double d)
 {
   kwsysProcessTime t;
@@ -2018,14 +2051,12 @@ static kwsysProcessTime kwsysProcessTimeFromDouble(double d)
   return t;
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcessTimeLess(kwsysProcessTime in1, kwsysProcessTime in2)
 {
   return ((in1.tv_sec < in2.tv_sec) ||
           ((in1.tv_sec == in2.tv_sec) && (in1.tv_usec < in2.tv_usec)));
 }
 
-/*--------------------------------------------------------------------------*/
 static kwsysProcessTime kwsysProcessTimeAdd(kwsysProcessTime in1,
                                             kwsysProcessTime in2)
 {
@@ -2039,7 +2070,6 @@ static kwsysProcessTime kwsysProcessTimeAdd(kwsysProcessTime in1,
   return out;
 }
 
-/*--------------------------------------------------------------------------*/
 static kwsysProcessTime kwsysProcessTimeSubtract(kwsysProcessTime in1,
                                                  kwsysProcessTime in2)
 {
@@ -2053,11 +2083,11 @@ static kwsysProcessTime kwsysProcessTimeSubtract(kwsysProcessTime in1,
   return out;
 }
 
-/*--------------------------------------------------------------------------*/
 #define KWSYSPE_CASE(type, str)                                               \
-  cp->ExitException = kwsysProcess_Exception_##type;                          \
-  strcpy(cp->ExitExceptionString, str)
-static void kwsysProcessSetExitException(kwsysProcess* cp, int sig)
+  cp->ProcessResults[idx].ExitException = kwsysProcess_Exception_##type;      \
+  strcpy(cp->ProcessResults[idx].ExitExceptionString, str)
+static void kwsysProcessSetExitExceptionByIndex(kwsysProcess* cp, int sig,
+                                                int idx)
 {
   switch (sig) {
 #ifdef SIGSEGV
@@ -2243,14 +2273,13 @@ static void kwsysProcessSetExitException(kwsysProcess* cp, int sig)
 #endif
 #endif
     default:
-      cp->ExitException = kwsysProcess_Exception_Other;
-      sprintf(cp->ExitExceptionString, "Signal %d", sig);
+      cp->ProcessResults[idx].ExitException = kwsysProcess_Exception_Other;
+      sprintf(cp->ProcessResults[idx].ExitExceptionString, "Signal %d", sig);
       break;
   }
 }
 #undef KWSYSPE_CASE
 
-/*--------------------------------------------------------------------------*/
 /* When the child process encounters an error before its program is
    invoked, this is called to report the error to the parent and
    exit.  */
@@ -2269,7 +2298,6 @@ static void kwsysProcessChildErrorExit(int errorPipe)
   _exit(1);
 }
 
-/*--------------------------------------------------------------------------*/
 /* Restores all signal handlers to their default values.  */
 static void kwsysProcessRestoreDefaultSignalHandlers(void)
 {
@@ -2377,13 +2405,11 @@ static void kwsysProcessRestoreDefaultSignalHandlers(void)
 #endif
 }
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcessExit(void)
 {
   _exit(0);
 }
 
-/*--------------------------------------------------------------------------*/
 #if !defined(__VMS)
 static pid_t kwsysProcessFork(kwsysProcess* cp,
                               kwsysProcessCreateInformation* si)
@@ -2433,7 +2459,6 @@ static pid_t kwsysProcessFork(kwsysProcess* cp,
 }
 #endif
 
-/*--------------------------------------------------------------------------*/
 /* We try to obtain process information by invoking the ps command.
    Here we define the command to call on each platform and the
    corresponding parsing format string.  The parsing format should
@@ -2457,7 +2482,6 @@ static pid_t kwsysProcessFork(kwsysProcess* cp,
 #define KWSYSPE_PS_FORMAT "%d %d %*[^\n]\n"
 #endif
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcessKill(pid_t process_id)
 {
 #if defined(__linux__) || defined(__CYGWIN__)
@@ -2561,7 +2585,6 @@ static void kwsysProcessKill(pid_t process_id)
 #endif
 }
 
-/*--------------------------------------------------------------------------*/
 #if defined(__VMS)
 int decc$feature_get_index(const char* name);
 int decc$feature_set_value(int index, int mode, int value);
@@ -2574,7 +2597,6 @@ static int kwsysProcessSetVMSFeature(const char* name, int value)
 }
 #endif
 
-/*--------------------------------------------------------------------------*/
 /* Global set of executing processes for use by the signal handler.
    This global instance will be zero-initialized by the compiler.  */
 typedef struct kwsysProcessInstances_s
@@ -2590,7 +2612,6 @@ static struct sigaction kwsysProcessesOldSigChldAction;
 static struct sigaction kwsysProcessesOldSigIntAction;
 static struct sigaction kwsysProcessesOldSigTermAction;
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcessesUpdate(kwsysProcessInstances* newProcesses)
 {
   /* Block signals while we update the set of pipes to check.
@@ -2611,7 +2632,6 @@ static void kwsysProcessesUpdate(kwsysProcessInstances* newProcesses)
   sigprocmask(SIG_SETMASK, &oldset, 0);
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcessesAdd(kwsysProcess* cp)
 {
   /* Create a pipe through which the signal handler can notify the
@@ -2721,7 +2741,6 @@ static int kwsysProcessesAdd(kwsysProcess* cp)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcessesRemove(kwsysProcess* cp)
 {
   /* Attempt to remove the given signal pipe from the signal handler set.  */
@@ -2772,7 +2791,6 @@ static void kwsysProcessesRemove(kwsysProcess* cp)
   kwsysProcessCleanupDescriptor(&cp->SignalPipe);
 }
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcessesSignalHandler(int signum
 #if KWSYSPE_USE_SIGINFO
                                         ,
@@ -2884,7 +2902,6 @@ static void kwsysProcessesSignalHandler(int signum
   errno = old_errno;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_ResetStartTime(kwsysProcess* cp)
 {
   if (!cp) {