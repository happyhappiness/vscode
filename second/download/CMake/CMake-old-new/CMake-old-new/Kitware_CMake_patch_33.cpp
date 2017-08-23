@@ -86,7 +86,6 @@ typedef struct kwsysProcessCreateInformation_s
   HANDLE hStdError;
 } kwsysProcessCreateInformation;
 
-/*--------------------------------------------------------------------------*/
 typedef struct kwsysProcessPipeData_s kwsysProcessPipeData;
 static DWORD WINAPI kwsysProcessPipeThreadRead(LPVOID ptd);
 static void kwsysProcessPipeThreadReadPipe(kwsysProcess* cp,
@@ -119,6 +118,8 @@ static kwsysProcessTime kwsysProcessTimeAdd(kwsysProcessTime in1,
 static kwsysProcessTime kwsysProcessTimeSubtract(kwsysProcessTime in1,
                                                  kwsysProcessTime in2);
 static void kwsysProcessSetExitException(kwsysProcess* cp, int code);
+static void kwsysProcessSetExitExceptionByIndex(kwsysProcess* cp, int code,
+                                                int idx);
 static void kwsysProcessKillTree(int pid);
 static void kwsysProcessDisablePipeThreads(kwsysProcess* cp);
 static int kwsysProcessesInitialize(void);
@@ -129,7 +130,6 @@ static int kwsysProcessesAdd(HANDLE hProcess, DWORD dwProcessId,
 static void kwsysProcessesRemove(HANDLE hProcess);
 static BOOL WINAPI kwsysCtrlHandler(DWORD dwCtrlType);
 
-/*--------------------------------------------------------------------------*/
 /* A structure containing synchronization data for each thread.  */
 typedef struct kwsysProcessPipeSync_s kwsysProcessPipeSync;
 struct kwsysProcessPipeSync_s
@@ -147,7 +147,6 @@ struct kwsysProcessPipeSync_s
   HANDLE Reset;
 };
 
-/*--------------------------------------------------------------------------*/
 /* A structure containing data for each pipe's threads.  */
 struct kwsysProcessPipeData_s
 {
@@ -183,7 +182,26 @@ struct kwsysProcessPipeData_s
   HANDLE Write;
 };
 
-/*--------------------------------------------------------------------------*/
+/* A structure containing results data for each process.  */
+typedef struct kwsysProcessResults_s kwsysProcessResults;
+struct kwsysProcessResults_s
+{
+  /* The status of the process.  */
+  int State;
+
+  /* The exceptional behavior that terminated the process, if any.  */
+  int ExitException;
+
+  /* The process exit code.  */
+  DWORD ExitCode;
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
@@ -249,15 +267,6 @@ struct kwsysProcess_s
 
   /* ------------- Data managed per call to Execute ------------- */
 
-  /* The exceptional behavior that terminated the process, if any.  */
-  int ExitException;
-
-  /* The process exit code.  */
-  DWORD ExitCode;
-
-  /* The process return code, if any.  */
-  int ExitValue;
-
   /* Index of last pipe to report data, if any.  */
   int CurrentIndex;
 
@@ -289,8 +298,8 @@ struct kwsysProcess_s
   /* Buffer for error messages.  */
   char ErrorMessage[KWSYSPE_PIPE_BUFFER_SIZE + 1];
 
-  /* Description for the ExitException.  */
-  char ExitExceptionString[KWSYSPE_PIPE_BUFFER_SIZE + 1];
+  /* process results.  */
+  kwsysProcessResults* ProcessResults;
 
   /* Windows process information data.  */
   PROCESS_INFORMATION* ProcessInformation;
@@ -308,7 +317,6 @@ struct kwsysProcess_s
   HANDLE PipeChildStd[3];
 };
 
-/*--------------------------------------------------------------------------*/
 kwsysProcess* kwsysProcess_New(void)
 {
   int i;
@@ -447,7 +455,6 @@ kwsysProcess* kwsysProcess_New(void)
   return cp;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_Delete(kwsysProcess* cp)
 {
   int i;
@@ -519,10 +526,10 @@ void kwsysProcess_Delete(kwsysProcess* cp)
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
@@ -543,7 +550,6 @@ int kwsysProcess_SetCommand(kwsysProcess* cp, char const* const* command)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
 {
   int newNumberOfCommands;
@@ -639,7 +645,6 @@ int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_SetTimeout(kwsysProcess* cp, double timeout)
 {
   if (!cp) {
@@ -653,7 +658,6 @@ void kwsysProcess_SetTimeout(kwsysProcess* cp, double timeout)
   cp->TimeoutTime.QuadPart = -1;
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_SetWorkingDirectory(kwsysProcess* cp, const char* dir)
 {
   if (!cp) {
@@ -685,7 +689,6 @@ int kwsysProcess_SetWorkingDirectory(kwsysProcess* cp, const char* dir)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_SetPipeFile(kwsysProcess* cp, int pipe, const char* file)
 {
   char** pfile;
@@ -727,7 +730,6 @@ int kwsysProcess_SetPipeFile(kwsysProcess* cp, int pipe, const char* file)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_SetPipeShared(kwsysProcess* cp, int pipe, int shared)
 {
   if (!cp) {
@@ -756,7 +758,6 @@ void kwsysProcess_SetPipeShared(kwsysProcess* cp, int pipe, int shared)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_SetPipeNative(kwsysProcess* cp, int pipe, HANDLE p[2])
 {
   HANDLE* pPipeNative = 0;
@@ -796,7 +797,6 @@ void kwsysProcess_SetPipeNative(kwsysProcess* cp, int pipe, HANDLE p[2])
   }
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_GetOption(kwsysProcess* cp, int optionId)
 {
   if (!cp) {
@@ -819,7 +819,6 @@ int kwsysProcess_GetOption(kwsysProcess* cp, int optionId)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_SetOption(kwsysProcess* cp, int optionId, int value)
 {
   if (!cp) {
@@ -847,31 +846,32 @@ void kwsysProcess_SetOption(kwsysProcess* cp, int optionId, int value)
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
 int kwsysProcess_GetExitValue(kwsysProcess* cp)
 {
-  return cp ? cp->ExitValue : -1;
+  return (cp && cp->ProcessResults && (cp->NumberOfCommands > 0))
+    ? cp->ProcessResults[cp->NumberOfCommands - 1].ExitValue
+    : -1;
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
 const char* kwsysProcess_GetErrorString(kwsysProcess* cp)
 {
   if (!cp) {
@@ -882,18 +882,59 @@ const char* kwsysProcess_GetErrorString(kwsysProcess* cp)
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
   }
   return "No exception";
 }
 
-/*--------------------------------------------------------------------------*/
+/* the index should be in array bound. */
+#define KWSYSPE_IDX_CHK(RET)                                                  \
+  if (!cp || idx >= cp->NumberOfCommands || idx < 0) {                        \
+    KWSYSPE_DEBUG((stderr, "array index out of bound\n"));                    \
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
+  }
+  return "No exception";
+}
+
+#undef KWSYSPE_IDX_CHK
+
 void kwsysProcess_Execute(kwsysProcess* cp)
 {
   int i;
@@ -1135,7 +1176,6 @@ void kwsysProcess_Execute(kwsysProcess* cp)
   cp->Detached = cp->OptionDetach;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_Disown(kwsysProcess* cp)
 {
   int i;
@@ -1162,8 +1202,6 @@ void kwsysProcess_Disown(kwsysProcess* cp)
   cp->State = kwsysProcess_State_Disowned;
 }
 
-/*--------------------------------------------------------------------------*/
-
 int kwsysProcess_WaitForData(kwsysProcess* cp, char** data, int* length,
                              double* userTimeout)
 {
@@ -1289,7 +1327,6 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, char** data, int* length,
   }
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
 {
   int i;
@@ -1338,25 +1375,29 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
     /* The timeout expired.  */
     cp->State = kwsysProcess_State_Expired;
   } else {
-    /* The children exited.  Report the outcome of the last process.  */
-    cp->ExitCode = cp->CommandExitCodes[cp->NumberOfCommands - 1];
-    if ((cp->ExitCode & 0xF0000000) == 0xC0000000) {
-      /* Child terminated due to exceptional behavior.  */
-      cp->State = kwsysProcess_State_Exception;
-      cp->ExitValue = 1;
-      kwsysProcessSetExitException(cp, cp->ExitCode);
-    } else {
-      /* Child exited without exception.  */
-      cp->State = kwsysProcess_State_Exited;
-      cp->ExitException = kwsysProcess_Exception_None;
-      cp->ExitValue = cp->ExitCode;
+    /* The children exited.  Report the outcome of the child processes.  */
+    for (i = 0; i < cp->NumberOfCommands; ++i) {
+      cp->ProcessResults[i].ExitCode = cp->CommandExitCodes[i];
+      if ((cp->ProcessResults[i].ExitCode & 0xF0000000) == 0xC0000000) {
+        /* Child terminated due to exceptional behavior.  */
+        cp->ProcessResults[i].State = kwsysProcess_StateByIndex_Exception;
+        cp->ProcessResults[i].ExitValue = 1;
+        kwsysProcessSetExitExceptionByIndex(cp, cp->ProcessResults[i].ExitCode,
+                                            i);
+      } else {
+        /* Child exited without exception.  */
+        cp->ProcessResults[i].State = kwsysProcess_StateByIndex_Exited;
+        cp->ProcessResults[i].ExitException = kwsysProcess_Exception_None;
+        cp->ProcessResults[i].ExitValue = cp->ProcessResults[i].ExitCode;
+      }
     }
+    /* support legacy state status value */
+    cp->State = cp->ProcessResults[cp->NumberOfCommands - 1].State;
   }
 
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_Interrupt(kwsysProcess* cp)
 {
   int i;
@@ -1394,7 +1435,6 @@ void kwsysProcess_Interrupt(kwsysProcess* cp)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_Kill(kwsysProcess* cp)
 {
   int i;
@@ -1429,8 +1469,6 @@ void kwsysProcess_Kill(kwsysProcess* cp)
      for them to exit.  */
 }
 
-/*--------------------------------------------------------------------------*/
-
 /*
   Function executed for each pipe's thread.  Argument is a pointer to
   the kwsysProcessPipeData instance for this thread.
@@ -1451,8 +1489,6 @@ DWORD WINAPI kwsysProcessPipeThreadRead(LPVOID ptd)
   return 0;
 }
 
-/*--------------------------------------------------------------------------*/
-
 /*
   Function called in each pipe's thread to handle data for one
   execution of a subprocess.
@@ -1494,8 +1530,6 @@ void kwsysProcessPipeThreadReadPipe(kwsysProcess* cp, kwsysProcessPipeData* td)
   ReleaseSemaphore(td->Reader.Go, 1, 0);
 }
 
-/*--------------------------------------------------------------------------*/
-
 /*
   Function executed for each pipe's thread.  Argument is a pointer to
   the kwsysProcessPipeData instance for this thread.
@@ -1516,8 +1550,6 @@ DWORD WINAPI kwsysProcessPipeThreadWake(LPVOID ptd)
   return 0;
 }
 
-/*--------------------------------------------------------------------------*/
-
 /*
   Function called in each pipe's thread to handle reading thread
   wakeup for one execution of a subprocess.
@@ -1540,23 +1572,34 @@ void kwsysProcessPipeThreadWakePipe(kwsysProcess* cp, kwsysProcessPipeData* td)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 /* Initialize a process control structure for kwsysProcess_Execute.  */
 int kwsysProcessInitialize(kwsysProcess* cp)
 {
+  int i;
   /* Reset internal status flags.  */
   cp->TimeoutExpired = 0;
   cp->Terminated = 0;
   cp->Killed = 0;
-  cp->ExitException = kwsysProcess_Exception_None;
-  cp->ExitCode = 1;
-  cp->ExitValue = 1;
 
-  /* Reset error data.  */
-  cp->ErrorMessage[0] = 0;
-  strcpy(cp->ExitExceptionString, "No exception");
+  free(cp->ProcessResults);
+  /* Allocate process result information for each process.  */
+  cp->ProcessResults = (kwsysProcessResults*)malloc(
+    sizeof(kwsysProcessResults) * (cp->NumberOfCommands));
+  if (!cp->ProcessResults) {
+    return 0;
+  }
+  ZeroMemory(cp->ProcessResults,
+             sizeof(kwsysProcessResults) * cp->NumberOfCommands);
+  for (i = 0; i < cp->NumberOfCommands; i++) {
+    cp->ProcessResults[i].ExitException = kwsysProcess_Exception_None;
+    cp->ProcessResults[i].State = kwsysProcess_StateByIndex_Starting;
+    cp->ProcessResults[i].ExitCode = 1;
+    cp->ProcessResults[i].ExitValue = 1;
+    strcpy(cp->ProcessResults[i].ExitExceptionString, "No exception");
+  }
 
   /* Allocate process information for each process.  */
+  free(cp->ProcessInformation);
   cp->ProcessInformation = (PROCESS_INFORMATION*)malloc(
     sizeof(PROCESS_INFORMATION) * cp->NumberOfCommands);
   if (!cp->ProcessInformation) {
@@ -1596,7 +1639,6 @@ int kwsysProcessInitialize(kwsysProcess* cp)
     }
   }
   {
-    int i;
     for (i = 0; i < 3; ++i) {
       cp->PipeChildStd[i] = INVALID_HANDLE_VALUE;
     }
@@ -1605,7 +1647,6 @@ int kwsysProcessInitialize(kwsysProcess* cp)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 static DWORD kwsysProcessCreateChildHandle(PHANDLE out, HANDLE in, int isStdIn)
 {
   DWORD flags;
@@ -1641,7 +1682,6 @@ static DWORD kwsysProcessCreateChildHandle(PHANDLE out, HANDLE in, int isStdIn)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 DWORD kwsysProcessCreate(kwsysProcess* cp, int index,
                          kwsysProcessCreateInformation* si)
 {
@@ -1706,7 +1746,6 @@ DWORD kwsysProcessCreate(kwsysProcess* cp, int index,
   return error;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcessDestroy(kwsysProcess* cp, int event)
 {
   int i;
@@ -1756,7 +1795,6 @@ void kwsysProcessDestroy(kwsysProcess* cp, int event)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 DWORD kwsysProcessSetupOutputPipeFile(PHANDLE phandle, const char* name)
 {
   HANDLE fout;
@@ -1784,7 +1822,6 @@ DWORD kwsysProcessSetupOutputPipeFile(PHANDLE phandle, const char* name)
   return ERROR_SUCCESS;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcessSetupSharedPipe(DWORD nStdHandle, PHANDLE handle)
 {
   /* Close the existing handle.  */
@@ -1793,7 +1830,6 @@ void kwsysProcessSetupSharedPipe(DWORD nStdHandle, PHANDLE handle)
   *handle = GetStdHandle(nStdHandle);
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcessSetupPipeNative(HANDLE native, PHANDLE handle)
 {
   /* Close the existing handle.  */
@@ -1802,8 +1838,6 @@ void kwsysProcessSetupPipeNative(HANDLE native, PHANDLE handle)
   *handle = native;
 }
 
-/*--------------------------------------------------------------------------*/
-
 /* Close the given handle if it is open.  Reset its value to 0.  */
 void kwsysProcessCleanupHandle(PHANDLE h)
 {
@@ -1816,8 +1850,6 @@ void kwsysProcessCleanupHandle(PHANDLE h)
   }
 }
 
-/*--------------------------------------------------------------------------*/
-
 /* Close all handles created by kwsysProcess_Execute.  */
 void kwsysProcessCleanup(kwsysProcess* cp, DWORD error)
 {
@@ -1902,7 +1934,6 @@ void kwsysProcessCleanup(kwsysProcess* cp, DWORD error)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcessCleanErrorMessage(kwsysProcess* cp)
 {
   /* Remove trailing period and newline, if any.  */
@@ -1920,7 +1951,6 @@ void kwsysProcessCleanErrorMessage(kwsysProcess* cp)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 /* Get the time at which either the process or user timeout will
    expire.  Returns 1 if the user timeout is first, and 0 otherwise.  */
 int kwsysProcessGetTimeoutTime(kwsysProcess* cp, double* userTimeout,
@@ -1952,7 +1982,6 @@ int kwsysProcessGetTimeoutTime(kwsysProcess* cp, double* userTimeout,
   return 0;
 }
 
-/*--------------------------------------------------------------------------*/
 /* Get the length of time before the given timeout time arrives.
    Returns 1 if the time has already arrived, and 0 otherwise.  */
 int kwsysProcessGetTimeoutLeft(kwsysProcessTime* timeoutTime,
@@ -1982,7 +2011,6 @@ int kwsysProcessGetTimeoutLeft(kwsysProcessTime* timeoutTime,
   }
 }
 
-/*--------------------------------------------------------------------------*/
 kwsysProcessTime kwsysProcessTimeGetCurrent()
 {
   kwsysProcessTime current;
@@ -1993,33 +2021,28 @@ kwsysProcessTime kwsysProcessTimeGetCurrent()
   return current;
 }
 
-/*--------------------------------------------------------------------------*/
 DWORD kwsysProcessTimeToDWORD(kwsysProcessTime t)
 {
   return (DWORD)(t.QuadPart * 0.0001);
 }
 
-/*--------------------------------------------------------------------------*/
 double kwsysProcessTimeToDouble(kwsysProcessTime t)
 {
   return t.QuadPart * 0.0000001;
 }
 
-/*--------------------------------------------------------------------------*/
 kwsysProcessTime kwsysProcessTimeFromDouble(double d)
 {
   kwsysProcessTime t;
   t.QuadPart = (LONGLONG)(d * 10000000);
   return t;
 }
 
-/*--------------------------------------------------------------------------*/
 int kwsysProcessTimeLess(kwsysProcessTime in1, kwsysProcessTime in2)
 {
   return in1.QuadPart < in2.QuadPart;
 }
 
-/*--------------------------------------------------------------------------*/
 kwsysProcessTime kwsysProcessTimeAdd(kwsysProcessTime in1,
                                      kwsysProcessTime in2)
 {
@@ -2028,7 +2051,6 @@ kwsysProcessTime kwsysProcessTimeAdd(kwsysProcessTime in1,
   return out;
 }
 
-/*--------------------------------------------------------------------------*/
 kwsysProcessTime kwsysProcessTimeSubtract(kwsysProcessTime in1,
                                           kwsysProcessTime in2)
 {
@@ -2037,11 +2059,11 @@ kwsysProcessTime kwsysProcessTimeSubtract(kwsysProcessTime in1,
   return out;
 }
 
-/*--------------------------------------------------------------------------*/
 #define KWSYSPE_CASE(type, str)                                               \
-  cp->ExitException = kwsysProcess_Exception_##type;                          \
-  strcpy(cp->ExitExceptionString, str)
-static void kwsysProcessSetExitException(kwsysProcess* cp, int code)
+  cp->ProcessResults[idx].ExitException = kwsysProcess_Exception_##type;      \
+  strcpy(cp->ProcessResults[idx].ExitExceptionString, str)
+static void kwsysProcessSetExitExceptionByIndex(kwsysProcess* cp, int code,
+                                                int idx)
 {
   switch (code) {
     case STATUS_CONTROL_C_EXIT:
@@ -2120,9 +2142,9 @@ static void kwsysProcessSetExitException(kwsysProcess* cp, int code)
 
     case STATUS_NO_MEMORY:
     default:
-      cp->ExitException = kwsysProcess_Exception_Other;
-      _snprintf(cp->ExitExceptionString, KWSYSPE_PIPE_BUFFER_SIZE,
-                "Exit code 0x%x\n", code);
+      cp->ProcessResults[idx].ExitException = kwsysProcess_Exception_Other;
+      _snprintf(cp->ProcessResults[idx].ExitExceptionString,
+                KWSYSPE_PIPE_BUFFER_SIZE, "Exit code 0x%x\n", code);
       break;
   }
 }
@@ -2136,7 +2158,6 @@ static int kwsysProcess_List_NextProcess(kwsysProcess_List* self);
 static int kwsysProcess_List_GetCurrentProcessId(kwsysProcess_List* self);
 static int kwsysProcess_List_GetCurrentParentId(kwsysProcess_List* self);
 
-/*--------------------------------------------------------------------------*/
 /* Windows NT 4 API definitions.  */
 #define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
 typedef LONG NTSTATUS;
@@ -2168,7 +2189,6 @@ struct _SYSTEM_PROCESS_INFORMATION
   ULONG InheritedFromProcessId;
 };
 
-/*--------------------------------------------------------------------------*/
 /* Toolhelp32 API definitions.  */
 #define TH32CS_SNAPPROCESS 0x00000002
 #if defined(_WIN64)
@@ -2192,15 +2212,13 @@ struct tagPROCESSENTRY32
   char szExeFile[MAX_PATH];
 };
 
-/*--------------------------------------------------------------------------*/
 /* Windows API function types.  */
 typedef HANDLE(WINAPI* CreateToolhelp32SnapshotType)(DWORD, DWORD);
 typedef BOOL(WINAPI* Process32FirstType)(HANDLE, LPPROCESSENTRY32);
 typedef BOOL(WINAPI* Process32NextType)(HANDLE, LPPROCESSENTRY32);
 typedef NTSTATUS(WINAPI* ZwQuerySystemInformationType)(ULONG, PVOID, ULONG,
                                                        PULONG);
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List__New_NT4(kwsysProcess_List* self);
 static int kwsysProcess_List__New_Snapshot(kwsysProcess_List* self);
 static void kwsysProcess_List__Delete_NT4(kwsysProcess_List* self);
@@ -2233,7 +2251,6 @@ struct kwsysProcess_List_s
   PROCESSENTRY32 CurrentEntry;
 };
 
-/*--------------------------------------------------------------------------*/
 static kwsysProcess_List* kwsysProcess_List_New(void)
 {
   OSVERSIONINFO osv;
@@ -2279,7 +2296,6 @@ static kwsysProcess_List* kwsysProcess_List_New(void)
   return self;
 }
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcess_List_Delete(kwsysProcess_List* self)
 {
   if (self) {
@@ -2292,39 +2308,34 @@ static void kwsysProcess_List_Delete(kwsysProcess_List* self)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List_Update(kwsysProcess_List* self)
 {
   return self ? (self->NT4 ? kwsysProcess_List__Update_NT4(self)
                            : kwsysProcess_List__Update_Snapshot(self))
               : 0;
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List_GetCurrentProcessId(kwsysProcess_List* self)
 {
   return self ? (self->NT4 ? kwsysProcess_List__GetProcessId_NT4(self)
                            : kwsysProcess_List__GetProcessId_Snapshot(self))
               : -1;
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List_GetCurrentParentId(kwsysProcess_List* self)
 {
   return self ? (self->NT4 ? kwsysProcess_List__GetParentId_NT4(self)
                            : kwsysProcess_List__GetParentId_Snapshot(self))
               : -1;
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List_NextProcess(kwsysProcess_List* self)
 {
   return (self ? (self->NT4 ? kwsysProcess_List__Next_NT4(self)
                             : kwsysProcess_List__Next_Snapshot(self))
                : 0);
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List__New_NT4(kwsysProcess_List* self)
 {
   /* Get a handle to the NT runtime module that should already be
@@ -2348,7 +2359,6 @@ static int kwsysProcess_List__New_NT4(kwsysProcess_List* self)
   return self->Buffer ? 1 : 0;
 }
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcess_List__Delete_NT4(kwsysProcess_List* self)
 {
   /* Free the process information buffer.  */
@@ -2357,7 +2367,6 @@ static void kwsysProcess_List__Delete_NT4(kwsysProcess_List* self)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List__Update_NT4(kwsysProcess_List* self)
 {
   self->CurrentInfo = 0;
@@ -2387,7 +2396,6 @@ static int kwsysProcess_List__Update_NT4(kwsysProcess_List* self)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List__Next_NT4(kwsysProcess_List* self)
 {
   if (self->CurrentInfo) {
@@ -2401,19 +2409,16 @@ static int kwsysProcess_List__Next_NT4(kwsysProcess_List* self)
   return 0;
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List__GetProcessId_NT4(kwsysProcess_List* self)
 {
   return self->CurrentInfo ? self->CurrentInfo->ProcessId : -1;
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List__GetParentId_NT4(kwsysProcess_List* self)
 {
   return self->CurrentInfo ? self->CurrentInfo->InheritedFromProcessId : -1;
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List__New_Snapshot(kwsysProcess_List* self)
 {
   /* Get a handle to the Windows runtime module that should already be
@@ -2436,15 +2441,13 @@ static int kwsysProcess_List__New_Snapshot(kwsysProcess_List* self)
     : 0;
 }
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcess_List__Delete_Snapshot(kwsysProcess_List* self)
 {
   if (self->Snapshot) {
     CloseHandle(self->Snapshot);
   }
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List__Update_Snapshot(kwsysProcess_List* self)
 {
   if (self->Snapshot) {
@@ -2464,7 +2467,6 @@ static int kwsysProcess_List__Update_Snapshot(kwsysProcess_List* self)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List__Next_Snapshot(kwsysProcess_List* self)
 {
   if (self->Snapshot) {
@@ -2477,19 +2479,16 @@ static int kwsysProcess_List__Next_Snapshot(kwsysProcess_List* self)
   return 0;
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List__GetProcessId_Snapshot(kwsysProcess_List* self)
 {
   return self->Snapshot ? self->CurrentEntry.th32ProcessID : -1;
 }
 
-/*--------------------------------------------------------------------------*/
 static int kwsysProcess_List__GetParentId_Snapshot(kwsysProcess_List* self)
 {
   return self->Snapshot ? self->CurrentEntry.th32ParentProcessID : -1;
 }
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcessKill(DWORD pid)
 {
   HANDLE h = OpenProcess(PROCESS_TERMINATE, 0, pid);
@@ -2500,7 +2499,6 @@ static void kwsysProcessKill(DWORD pid)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcessKillTree(int pid)
 {
   kwsysProcess_List* plist = kwsysProcess_List_New();
@@ -2516,7 +2514,6 @@ static void kwsysProcessKillTree(int pid)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 static void kwsysProcessDisablePipeThreads(kwsysProcess* cp)
 {
   int i;
@@ -2568,7 +2565,6 @@ static void kwsysProcessDisablePipeThreads(kwsysProcess* cp)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 /* Global set of executing processes for use by the Ctrl handler.
    This global instance will be zero-initialized by the compiler.
 
@@ -2598,7 +2594,6 @@ typedef struct kwsysProcessInstances_s
 } kwsysProcessInstances;
 static kwsysProcessInstances kwsysProcesses;
 
-/*--------------------------------------------------------------------------*/
 /* Initialize critial section and set up console Ctrl handler.  You MUST call
    this before using any other kwsysProcesses* functions below.  */
 static int kwsysProcessesInitialize(void)
@@ -2617,7 +2612,6 @@ static int kwsysProcessesInitialize(void)
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 /* The Ctrl handler waits on the global list of processes.  To prevent an
    orphaned process, do not create a new process if the Ctrl handler is
    already running.  Do so by using this function to check if it is ok to
@@ -2636,15 +2630,13 @@ static int kwsysTryEnterCreateProcessSection(void)
   }
 }
 
-/*--------------------------------------------------------------------------*/
 /* Matching function on successful kwsysTryEnterCreateProcessSection return.
    Make sure you called kwsysProcessesAdd if applicable before calling this.*/
 static void kwsysLeaveCreateProcessSection(void)
 {
   LeaveCriticalSection(&kwsysProcesses.Lock);
 }
 
-/*--------------------------------------------------------------------------*/
 /* Add new process to global process list.  The Ctrl handler will wait for
    the process to exit before it returns.  Do not close the process handle
    until after calling kwsysProcessesRemove.  The newProcessGroup parameter
@@ -2702,7 +2694,6 @@ static int kwsysProcessesAdd(HANDLE hProcess, DWORD dwProcessid,
   return 1;
 }
 
-/*--------------------------------------------------------------------------*/
 /* Removes process to global process list.  */
 static void kwsysProcessesRemove(HANDLE hProcess)
 {
@@ -2738,7 +2729,6 @@ static void kwsysProcessesRemove(HANDLE hProcess)
   LeaveCriticalSection(&kwsysProcesses.Lock);
 }
 
-/*--------------------------------------------------------------------------*/
 static BOOL WINAPI kwsysCtrlHandler(DWORD dwCtrlType)
 {
   size_t i;
@@ -2774,7 +2764,6 @@ static BOOL WINAPI kwsysCtrlHandler(DWORD dwCtrlType)
   return FALSE;
 }
 
-/*--------------------------------------------------------------------------*/
 void kwsysProcess_ResetStartTime(kwsysProcess* cp)
 {
   if (!cp) {