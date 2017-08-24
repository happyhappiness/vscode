@@ -49,25 +49,37 @@ Q190351 and Q150956.
 #pragma warning (disable: 4706)
 #endif
 
-/* The number of pipes for the child's output.  The standard stdout
-   and stderr pipes are the first two.  One more pipe is used on Win9x
-   for the forwarding executable to use in reporting problems.  */
-#define CMPE_PIPE_COUNT 3
-#define CMPE_PIPE_STDOUT 0
-#define CMPE_PIPE_STDERR 1
-#define CMPE_PIPE_ERROR 2
+/* There are pipes for the process pipeline's stdout and stderr.  */
+#define KWSYSPE_PIPE_COUNT 2
+#define KWSYSPE_PIPE_STDOUT 0
+#define KWSYSPE_PIPE_STDERR 1
 
 /* The maximum amount to read from a pipe at a time.  */
-#define CMPE_PIPE_BUFFER_SIZE 1024
+#define KWSYSPE_PIPE_BUFFER_SIZE 1024
 
 #define kwsysEncodedWriteArrayProcessFwd9x kwsys(EncodedWriteArrayProcessFwd9x)
 
 typedef LARGE_INTEGER kwsysProcessTime;
 
+typedef struct kwsysProcessCreateInformation_s
+{
+  /* Windows child startup control data.  */
+  STARTUPINFO StartupInfo;
+
+  /* Special error reporting pipe for Win9x forwarding executable.  */
+  HANDLE ErrorPipeRead;
+  HANDLE ErrorPipeWrite;
+} kwsysProcessCreateInformation;
+
 /*--------------------------------------------------------------------------*/
 typedef struct kwsysProcessPipeData_s kwsysProcessPipeData;
 static DWORD WINAPI kwsysProcessPipeThread(LPVOID ptd);
 static void kwsysProcessPipeThreadReadPipe(kwsysProcess* cp, kwsysProcessPipeData* td);
+static int kwsysProcessInitialize(kwsysProcess* cp);
+static int kwsysProcessCreate(kwsysProcess* cp, int index,
+                              kwsysProcessCreateInformation* si,
+                              PHANDLE readEnd);
+static void kwsysProcessDestroy(kwsysProcess* cp, int event);
 static void kwsysProcessCleanupHandle(PHANDLE h);
 static void kwsysProcessCleanup(kwsysProcess* cp, int error);
 static void kwsysProcessCleanErrorMessage(kwsysProcess* cp);
@@ -111,7 +123,7 @@ struct kwsysProcessPipeData_s
   /* ------------- Data managed per call to Execute ------------- */
   
   /* Buffer for data read in this pipe's thread.  */
-  char DataBuffer[CMPE_PIPE_BUFFER_SIZE];
+  char DataBuffer[KWSYSPE_PIPE_BUFFER_SIZE];
     
   /* The length of the data stored in the buffer.  */
   DWORD DataLength;
@@ -132,11 +144,15 @@ struct kwsysProcess_s
 {
   /* ------------- Data managed per instance of kwsysProcess ------------- */
   
-  /* The status of the process.  */
+  /* The status of the process structure.  */
   int State;
   
-  /* The command line to execute.  */
-  char* Command;
+  /* The command lines to execute.  */
+  char** Commands;
+  int NumberOfCommands;
+
+  /* The exit code of each command.  */
+  DWORD* CommandExitCodes;
   
   /* The working directory for the child process.  */
   char* WorkingDirectory;
@@ -147,6 +163,9 @@ struct kwsysProcess_s
   /* On Win9x platforms, the path to the forwarding executable.  */
   char* Win9x;
   
+  /* On Win9x platforms, the resume event for the forwarding executable.  */
+  HANDLE Win9xResumeEvent;
+  
   /* On Win9x platforms, the kill event for the forwarding executable.  */
   HANDLE Win9xKillEvent;
   
@@ -156,15 +175,11 @@ struct kwsysProcess_s
   /* Semaphore used by threads to signal data ready.  */
   HANDLE Full;
   
-  /* The number of pipes needed to implement the child's execution.
-     This is 3 on Win9x and 2 otherwise.  */
-  int PipeCount;
-  
   /* Whether we are currently deleting this kwsysProcess instance.  */
   int Deleting;
   
   /* Data specific to each pipe and its thread.  */
-  kwsysProcessPipeData Pipe[CMPE_PIPE_COUNT];  
+  kwsysProcessPipeData Pipe[KWSYSPE_PIPE_COUNT];  
   
   /* ------------- Data managed per call to Execute ------------- */
   
@@ -206,14 +221,14 @@ struct kwsysProcess_s
   int PipesLeft;
   
   /* Buffer for error messages (possibly from Win9x child).  */
-  char ErrorMessage[CMPE_PIPE_BUFFER_SIZE+1];
-  int ErrorMessageLength;
-  
-  /* The actual command line that will be used to create the process.  */
-  char* RealCommand;
+  char ErrorMessage[KWSYSPE_PIPE_BUFFER_SIZE+1];
 
   /* Windows process information data.  */
-  PROCESS_INFORMATION ProcessInformation;
+  PROCESS_INFORMATION* ProcessInformation;
+
+  /* Data and process termination events for which to wait.  */
+  PHANDLE ProcessEvents;
+  int ProcessEventsLength;
 };
 
 /*--------------------------------------------------------------------------*/
@@ -299,9 +314,8 @@ kwsysProcess* kwsysProcess_New()
       }
     }
   
-  /* We need the extra error pipe on Win9x.  */
+  /* Save the path to the forwarding executable.  */
   cp->Win9x = win9x;
-  cp->PipeCount = cp->Win9x? 3:2;
   
   /* Initially no thread owns the mutex.  Initialize semaphore to 1.  */
   if(!(cp->SharedIndexMutex = CreateSemaphore(0, 1, 1, 0)))
@@ -319,12 +333,21 @@ kwsysProcess* kwsysProcess_New()
 
   if(cp->Win9x)
     {
-    /* Create an event to tell the forwarding executable to kill the
-       child.  */
     SECURITY_ATTRIBUTES sa;
     ZeroMemory(&sa, sizeof(sa));
     sa.nLength = sizeof(sa);
     sa.bInheritHandle = TRUE;
+
+    /* Create an event to tell the forwarding executable to resume the
+       child.  */
+    if(!(cp->Win9xResumeEvent = CreateEvent(&sa, TRUE, 0, 0)))
+      {
+      kwsysProcess_Delete(cp);
+      return 0;
+      }
+
+    /* Create an event to tell the forwarding executable to kill the
+       child.  */
     if(!(cp->Win9xKillEvent = CreateEvent(&sa, TRUE, 0, 0)))
       {
       kwsysProcess_Delete(cp);
@@ -333,7 +356,7 @@ kwsysProcess* kwsysProcess_New()
     }
     
   /* Create the thread to read each pipe.  */
-  for(i=0; i < cp->PipeCount; ++i)
+  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
     {
     DWORD dummy=0;
     
@@ -393,7 +416,7 @@ void kwsysProcess_Delete(kwsysProcess* cp)
   cp->Deleting = 1;
   
   /* Terminate each of the threads.  */
-  for(i=0; i < cp->PipeCount; ++i)
+  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
     {
     if(cp->Pipe[i].Thread)
       {
@@ -417,15 +440,20 @@ void kwsysProcess_Delete(kwsysProcess* cp)
   kwsysProcessCleanupHandle(&cp->SharedIndexMutex);
   kwsysProcessCleanupHandle(&cp->Full);
   
-  /* Close the Win9x kill event handle.  */
+  /* Close the Win9x resume and kill event handles.  */
   if(cp->Win9x)
     {
+    kwsysProcessCleanupHandle(&cp->Win9xResumeEvent);
     kwsysProcessCleanupHandle(&cp->Win9xKillEvent);
     }
   
   /* Free memory.  */
   kwsysProcess_SetCommand(cp, 0);
   kwsysProcess_SetWorkingDirectory(cp, 0);
+  if(cp->CommandExitCodes)
+    {
+    free(cp->CommandExitCodes);
+    }
   if(cp->Win9x)
     {
     _unlink(cp->Win9x);
@@ -435,178 +463,231 @@ void kwsysProcess_Delete(kwsysProcess* cp)
 }
 
 /*--------------------------------------------------------------------------*/
-void kwsysProcess_SetCommand(kwsysProcess* cp, char const* const* command)
+int kwsysProcess_SetCommand(kwsysProcess* cp, char const* const* command)
 {
-  if(cp->Command)
+  int i;
+  for(i=0; i < cp->NumberOfCommands; ++i)
+    {
+    free(cp->Commands[i]);
+    }
+  cp->NumberOfCommands = 0;
+  if(cp->Commands)
     {
-    free(cp->Command);
-    cp->Command = 0;
+    free(cp->Commands);
+    cp->Commands = 0;
     }
   if(command)
     {
-    /* We need to construct a single string representing the command
+    return kwsysProcess_AddCommand(cp, command);
+    }
+  return 1;
+}
+
+/*--------------------------------------------------------------------------*/
+int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
+{
+  int newNumberOfCommands;
+  char** newCommands;
+
+  /* Make sure we have a command to add.  */
+  if(!command)
+    {
+    return 0;
+    }
+
+  /* Allocate a new array for command pointers.  */
+  newNumberOfCommands = cp->NumberOfCommands + 1;
+  if(!(newCommands = (char**)malloc(sizeof(char*) * newNumberOfCommands)))
+    {
+    /* Out of memory.  */
+    return 0;
+    }
+
+  /* Copy any existing commands into the new array.  */
+  {
+  int i;
+  for(i=0; i < cp->NumberOfCommands; ++i)
+    {
+    newCommands[i] = cp->Commands[i];
+    }
+  }
+
+  /* We need to construct a single string representing the command
        and its arguments.  We will surround each argument containing
        spaces with double-quotes.  Inside a double-quoted argument, we
        need to escape double-quotes and all backslashes before them.
        We also need to escape backslashes at the end of an argument
        because they come before the closing double-quote for the
        argument.  */
-    char* cmd;
-    char const* const* arg;
-    int length = 0;
-    /* First determine the length of the final string.  */
-    for(arg = command; *arg; ++arg)
-      {
-      /* Keep track of how many backslashes have been encountered in a
-         row in this argument.  */
-      int backslashes = 0;
-      int spaces = 0;
-      const char* c;
+  {
+  char* cmd;
+  char const* const* arg;
+  int length = 0;
+  /* First determine the length of the final string.  */
+  for(arg = command; *arg; ++arg)
+    {
+    /* Keep track of how many backslashes have been encountered in a
+       row in this argument.  */
+    int backslashes = 0;
+    int spaces = 0;
+    const char* c;
 
-      /* Scan the string for spaces.  If there are no spaces, we can
+    /* Scan the string for spaces.  If there are no spaces, we can
          pass the argument verbatim.  */
-      for(c=*arg; *c; ++c)
+    for(c=*arg; *c; ++c)
+      {
+      if(*c == ' ' || *c == '\t')
         {
-        if(*c == ' ' || *c == '\t')
-          {
-          spaces = 1;
-          break;
-          }
+        spaces = 1;
+        break;
         }
+      }
       
-      /* Add the length of the argument, plus 1 for the space
+    /* Add the length of the argument, plus 1 for the space
          separating the arguments.  */
-      length += (int)strlen(*arg) + 1;
+    length += (int)strlen(*arg) + 1;
       
-      if(spaces)
-        {
-        /* Add 2 for double quotes since spaces are present.  */
-        length += 2;
+    if(spaces)
+      {
+      /* Add 2 for double quotes since spaces are present.  */
+      length += 2;
 
         /* Scan the string to find characters that need escaping.  */
-        for(c=*arg; *c; ++c)
+      for(c=*arg; *c; ++c)
+        {
+        if(*c == '\\')
           {
-          if(*c == '\\')
-            {
-            /* Found a backslash.  It may need to be escaped later.  */
-            ++backslashes;
-            }
-          else if(*c == '"')
-            {
-            /* Found a double-quote.  We need to escape it and all
-               immediately preceding backslashes.  */
-            length += backslashes + 1;
-            backslashes = 0;
-            }
-          else
-            {
-            /* Found another character.  This eliminates the possibility
-               that any immediately preceding backslashes will be
-               escaped.  */
-            backslashes = 0;
-            }
+          /* Found a backslash.  It may need to be escaped later.  */
+          ++backslashes;
+          }
+        else if(*c == '"')
+          {
+          /* Found a double-quote.  We need to escape it and all
+             immediately preceding backslashes.  */
+          length += backslashes + 1;
+          backslashes = 0;
+          }
+        else
+          {
+          /* Found another character.  This eliminates the possibility
+             that any immediately preceding backslashes will be
+             escaped.  */
+          backslashes = 0;
           }
-      
-        /* We need to escape all ending backslashes. */
-        length += backslashes;
         }
+      
+      /* We need to escape all ending backslashes. */
+      length += backslashes;
       }
+    }
     
-    /* Allocate enough space for the command.  We do not need an extra
+  /* Allocate enough space for the command.  We do not need an extra
        byte for the terminating null because we allocated a space for
        the first argument that we will not use.  */
-    cp->Command = (char*)malloc(length);
+  newCommands[cp->NumberOfCommands] = (char*)malloc(length);
+  if(!newCommands[cp->NumberOfCommands])
+    {
+    /* Out of memory.  */
+    free(newCommands);
+    return 0;
+    }
     
-    /* Construct the command line in the allocated buffer.  */
-    cmd = cp->Command;
-    for(arg = command; *arg; ++arg)
-      {
-      /* Keep track of how many backslashes have been encountered in a
-         row in an argument.  */
-      int backslashes = 0;
-      int spaces = 0;
-      const char* c;
+  /* Construct the command line in the allocated buffer.  */
+  cmd = newCommands[cp->NumberOfCommands];
+  for(arg = command; *arg; ++arg)
+    {
+    /* Keep track of how many backslashes have been encountered in a
+       row in an argument.  */
+    int backslashes = 0;
+    int spaces = 0;
+    const char* c;
 
-      /* Scan the string for spaces.  If there are no spaces, we can
+    /* Scan the string for spaces.  If there are no spaces, we can
          pass the argument verbatim.  */
-      for(c=*arg; *c; ++c)
-        {
-        if(*c == ' ' || *c == '\t')
-          {
-          spaces = 1;
-          break;
-          }
-        }      
-      
-      /* Add the separating space if this is not the first argument.  */
-      if(arg != command)
+    for(c=*arg; *c; ++c)
+      {
+      if(*c == ' ' || *c == '\t')
         {
-        *cmd++ = ' ';
+        spaces = 1;
+        break;
         }
+      }      
       
-      if(spaces)
-        {
-        /* Add the opening double-quote for this argument.  */
-        *cmd++ = '"';
+    /* Add the separating space if this is not the first argument.  */
+    if(arg != command)
+      {
+      *cmd++ = ' ';
+      }
+      
+    if(spaces)
+      {
+      /* Add the opening double-quote for this argument.  */
+      *cmd++ = '"';
         
         /* Add the characters of the argument, possibly escaping them.  */
-        for(c=*arg; *c; ++c)
+      for(c=*arg; *c; ++c)
+        {
+        if(*c == '\\')
+          {
+          /* Found a backslash.  It may need to be escaped later.  */
+          ++backslashes;
+          *cmd++ = '\\';
+          }
+        else if(*c == '"')
           {
-          if(*c == '\\')
+          /* Add enough backslashes to escape any that preceded the
+             double-quote.  */
+          while(backslashes > 0)
             {
-            /* Found a backslash.  It may need to be escaped later.  */
-            ++backslashes;
+            --backslashes;
             *cmd++ = '\\';
             }
-          else if(*c == '"')
-            {
-            /* Add enough backslashes to escape any that preceded the
-               double-quote.  */
-            while(backslashes > 0)
-              {
-              --backslashes;
-              *cmd++ = '\\';
-              }
             
-            /* Add the backslash to escape the double-quote.  */
-            *cmd++ = '\\';
+          /* Add the backslash to escape the double-quote.  */
+          *cmd++ = '\\';
             
-            /* Add the double-quote itself.  */
-            *cmd++ = '"';
-            }
-          else
-            {
-            /* We encountered a normal character.  This eliminates any
-               escaping needed for preceding backslashes.  Add the
-               character.  */
-            backslashes = 0;
-            *cmd++ = *c;
-            }
+          /* Add the double-quote itself.  */
+          *cmd++ = '"';
           }
-        
-        /* Add enough backslashes to escape any trailing ones.  */
-        while(backslashes > 0)
+        else
           {
-          --backslashes;
-          *cmd++ = '\\';
+          /* We encountered a normal character.  This eliminates any
+             escaping needed for preceding backslashes.  Add the
+             character.  */
+          backslashes = 0;
+          *cmd++ = *c;
           }
-
-        /* Add the closing double-quote for this argument.  */
-        *cmd++ = '"';
         }
-      else
+        
+      /* Add enough backslashes to escape any trailing ones.  */
+      while(backslashes > 0)
         {
-        /* No spaces.  Add the argument verbatim.  */
-        for(c=*arg; *c; ++c)
-          {
-          *cmd++ = *c;
-          }
+        --backslashes;
+        *cmd++ = '\\';
+        }
+
+      /* Add the closing double-quote for this argument.  */
+      *cmd++ = '"';
+      }
+    else
+      {
+      /* No spaces.  Add the argument verbatim.  */
+      for(c=*arg; *c; ++c)
+        {
+        *cmd++ = *c;
         }
       }
-    
-    /* Add the terminating null character to the command line.  */
-    *cmd = 0;
     }
+
+  /* Add the terminating null character to the command line.  */
+  *cmd = 0;
+  }
+
+  /* Save the new array of commands.  */
+  free(cp->Commands);
+  cp->Commands = newCommands;
+  cp->NumberOfCommands = newNumberOfCommands;
+  return 1;
 }
 
 /*--------------------------------------------------------------------------*/
@@ -698,122 +779,141 @@ void kwsysProcess_Execute(kwsysProcess* cp)
 {
   int i;
 
-  /* Windows child startup control data.  */
-  STARTUPINFO si;
-  DWORD dwCreationFlags=0;
+  /* Child startup control data.  */
+  kwsysProcessCreateInformation si;
   
   /* Do not execute a second time.  */
   if(cp->State == kwsysProcess_State_Executing)
     {
     return;
     }
+
+  /* Initialize the control structure for a new process.  */
+  if(!kwsysProcessInitialize(cp))
+    {
+    strcpy(cp->ErrorMessage, "Out of memory");
+    cp->State = kwsysProcess_State_Error;
+    return;
+    }
   
-  /* Initialize startup info data.  */
-  ZeroMemory(&si, sizeof(si));
-  si.cb = sizeof(si);
-  
-  /* Reset internal status flags.  */
-  cp->TimeoutExpired = 0;
-  cp->Terminated = 0;
-  cp->Killed = 0;
-  cp->ExitException = kwsysProcess_Exception_None;
-  cp->ExitCode = 1;
-  cp->ExitValue = 1;
-  
-  /* Reset error data.  */
-  cp->ErrorMessage[0] = 0;
-  cp->ErrorMessageLength = 0;
-  
-  /* Reset the Win9x kill event.  */
+  /* Reset the Win9x resume and kill events.  */
   if(cp->Win9x)
     {
+    if(!ResetEvent(cp->Win9xResumeEvent))
+      {
+      kwsysProcessCleanup(cp, 1);
+      return;
+      }
     if(!ResetEvent(cp->Win9xKillEvent))
       {
       kwsysProcessCleanup(cp, 1);
       return;
       }
     }
+
+  /* Initialize startup info data.  */
+  ZeroMemory(&si, sizeof(si));
+  si.StartupInfo.cb = sizeof(si.StartupInfo);
+  
+  /* Decide whether a child window should be shown.  */
+  si.StartupInfo.dwFlags |= STARTF_USESHOWWINDOW;
+  si.StartupInfo.wShowWindow =
+    (unsigned short)(cp->HideWindow?SW_HIDE:SW_SHOWDEFAULT);
   
-  /* Create a pipe for each child output.  */
-  for(i=0; i < cp->PipeCount; ++i)
+  /* Connect the child's output pipes to the threads.  */
+  si.StartupInfo.dwFlags = STARTF_USESTDHANDLES;
+
+  /* Create stderr pipe to be shared by all processes in the pipeline.
+     Neither end is directly inherited.  */
+  if(!CreatePipe(&cp->Pipe[KWSYSPE_PIPE_STDERR].Read,
+                 &cp->Pipe[KWSYSPE_PIPE_STDERR].Write, 0, 0))
     {
-    HANDLE writeEnd;
-    
-    /* The pipe is not closed.  */
-    cp->Pipe[i].Closed = 0;
+    kwsysProcessCleanup(cp, 1);
+    return;
+    }
     
-    /* Create the pipe.  Neither end is directly inherited.  */
-    if(!CreatePipe(&cp->Pipe[i].Read, &writeEnd, 0, 0))
+  /* Create an inherited duplicate of the write end, but do not
+     close the non-inherited version.  We need to keep it open
+     to use in waking up the pipe threads.  */
+  if(!DuplicateHandle(GetCurrentProcess(), cp->Pipe[KWSYSPE_PIPE_STDERR].Write,
+                      GetCurrentProcess(), &si.StartupInfo.hStdError,
+                      0, TRUE, DUPLICATE_SAME_ACCESS))
+    {
+    kwsysProcessCleanup(cp, 1);
+    kwsysProcessCleanupHandle(&si.StartupInfo.hStdError);
+    return;
+    }
+
+  /* Create the pipeline of processes.  */
+  {
+  HANDLE readEnd = 0;
+  for(i=0; i < cp->NumberOfCommands; ++i)
+    {
+    if(kwsysProcessCreate(cp, i, &si, &readEnd))
       {
-      kwsysProcessCleanup(cp, 1);
-      return;
+      cp->ProcessEvents[i+1] = cp->ProcessInformation[i].hProcess;
       }
-    
-    /* Create an inherited duplicate of the write end.  This also closes
-       the non-inherited version. */
-    if(!DuplicateHandle(GetCurrentProcess(), writeEnd,
-                        GetCurrentProcess(), &cp->Pipe[i].Write,
-                        0, TRUE, (DUPLICATE_CLOSE_SOURCE |
-                                  DUPLICATE_SAME_ACCESS)))
+    else
       {
       kwsysProcessCleanup(cp, 1);
+
+      /* Release resources that may have been allocated for this
+         process before an error occurred.  */
+      kwsysProcessCleanupHandle(&readEnd);
+      if(i > 0)
+        {
+        kwsysProcessCleanupHandle(&si.StartupInfo.hStdInput);
+        }
+      kwsysProcessCleanupHandle(&si.StartupInfo.hStdOutput);
+      kwsysProcessCleanupHandle(&si.StartupInfo.hStdError);
+      kwsysProcessCleanupHandle(&si.ErrorPipeRead);
+      kwsysProcessCleanupHandle(&si.ErrorPipeWrite);
       return;
       }
     }
+
+  /* Save a handle to the output pipe for the last process.  */
+  cp->Pipe[KWSYSPE_PIPE_STDOUT].Read = readEnd;
+  }
+
+  /* Close the inherited handles to the stderr pipe shared by all
+     processes in the pipeline.  */
+  kwsysProcessCleanupHandle(&si.StartupInfo.hStdError);
+
+  /* The timeout period starts now.  */
+  cp->StartTime = kwsysProcessTimeGetCurrent();
+  cp->TimeoutTime = kwsysProcessTimeFromDouble(-1);
   
-  /* Construct the real command line.  */
+  /* All processes in the pipeline have been started in suspended
+     mode.  Resume them all now.  */
   if(cp->Win9x)
     {
-    /* Windows 9x */
-    
-    /* The forwarding executable is given a handle to the error pipe
-       and a handle to the kill event.  */
-    cp->RealCommand = malloc(strlen(cp->Win9x)+strlen(cp->Command)+100);
-    sprintf(cp->RealCommand, "%s %p %p %d %s", cp->Win9x,
-            cp->Pipe[CMPE_PIPE_ERROR].Write, cp->Win9xKillEvent,
-            cp->HideWindow, cp->Command);
+    SetEvent(cp->Win9xResumeEvent);
     }
   else
     {
-    /* Not Windows 9x */    
-    cp->RealCommand = strdup(cp->Command);
-    }
-  
-  /* Connect the child's output pipes to the threads.  */
-  si.dwFlags = STARTF_USESTDHANDLES;
-  si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
-  si.hStdOutput = cp->Pipe[CMPE_PIPE_STDOUT].Write;
-  si.hStdError = cp->Pipe[CMPE_PIPE_STDERR].Write;
-  
-  /* Decide whether a child window should be shown.  */
-  si.dwFlags |= STARTF_USESHOWWINDOW;
-  si.wShowWindow = (unsigned short)(cp->HideWindow?SW_HIDE:SW_SHOWDEFAULT);
-  
-  /* The timeout period starts now.  */
-  cp->StartTime = kwsysProcessTimeGetCurrent();
-  cp->TimeoutTime = kwsysProcessTimeFromDouble(-1);
-  
-  /* CREATE THE CHILD PROCESS */
-  if(!CreateProcess(0, cp->RealCommand, 0, 0, TRUE, dwCreationFlags, 0,
-                    cp->WorkingDirectory, &si, &cp->ProcessInformation))
-    {
-    kwsysProcessCleanup(cp, 1);
-    return;
+    for(i=0; i < cp->NumberOfCommands; ++i)
+      {
+      ResumeThread(cp->ProcessInformation[i].hThread);
+      }
     }
-  
-  /* ---- It is no longer safe to call kwsysProcessCleanup. ----- */
+
+  /* ---- It is no longer safe to call kwsysProcessCleanup. ----- */  
   /* Tell the pipe threads that a process has started.  */
-  for(i=0; i < cp->PipeCount; ++i)
+  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
     {
     ReleaseSemaphore(cp->Pipe[i].Ready, 1, 0);
     }
-  
-  /* We don't care about the child's main thread.  */
-  kwsysProcessCleanupHandle(&cp->ProcessInformation.hThread);
+
+  /* We don't care about the children's main threads.  */
+  for(i=0; i < cp->NumberOfCommands; ++i)
+    {
+    kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
+    }
   
   /* No pipe has reported data.  */
-  cp->CurrentIndex = CMPE_PIPE_COUNT;
-  cp->PipesLeft = cp->PipeCount;
+  cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
+  cp->PipesLeft = KWSYSPE_PIPE_COUNT;
   
   /* The process has now started.  */
   cp->State = kwsysProcess_State_Executing;
@@ -833,7 +933,6 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
   int expired = 0;
   int pipeId = 0;
   DWORD w;
-  HANDLE events[2];
 
   /* Make sure we are executing a process.  */
   if(cp->State != kwsysProcess_State_Executing || cp->Killed ||
@@ -842,11 +941,6 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
     return 0;
     }
   
-  /* We will wait for data until the process termiantes or data are
-     available. */
-  events[0] = cp->Full;
-  events[1] = cp->ProcessInformation.hProcess;
-  
   /* Record the time at which user timeout period starts.  */
   userStartTime = kwsysProcessTimeGetCurrent();
   
@@ -859,10 +953,10 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
     {
     /* If we previously got data from a thread, let it know we are
        done with the data.  */
-    if(cp->CurrentIndex < CMPE_PIPE_COUNT)
+    if(cp->CurrentIndex < KWSYSPE_PIPE_COUNT)
       {
       ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Empty, 1, 0);
-      cp->CurrentIndex = CMPE_PIPE_COUNT;
+      cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
       }
     
     /* Setup a timeout if required.  */
@@ -881,9 +975,9 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
       timeout = kwsysProcessTimeToDWORD(timeoutLength);
       }
     
-    /* Wait for a pipe's thread to signal or the application to
-       terminate.  */
-    w = WaitForMultipleObjects(cp->Terminated?1:2, events, 0, timeout);
+    /* Wait for a pipe's thread to signal or a process to terminate.  */
+    w = WaitForMultipleObjects(cp->ProcessEventsLength, cp->ProcessEvents,
+                               0, timeout);
     if(w == WAIT_TIMEOUT)
       {
       /* Timeout has expired.  */
@@ -903,26 +997,6 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
         /* The pipe closed.  */
         --cp->PipesLeft;
         }
-      else if(cp->CurrentIndex == CMPE_PIPE_ERROR)
-        {
-        /* This is data on the special error reporting pipe for Win9x.
-           Append it to the error buffer.  */
-        int length = cp->Pipe[cp->CurrentIndex].DataLength;
-        if(length > CMPE_PIPE_BUFFER_SIZE - cp->ErrorMessageLength)
-          {
-          length = CMPE_PIPE_BUFFER_SIZE - cp->ErrorMessageLength;
-          }
-        if(length > 0)
-          {
-          memcpy(cp->ErrorMessage+cp->ErrorMessageLength,
-                 cp->Pipe[cp->CurrentIndex].DataBuffer, length);
-          cp->ErrorMessageLength += length;
-          }
-        else
-          {
-          cp->ErrorMessage[cp->ErrorMessageLength] = 0;
-          }
-        }
       else if(pipes & (1 << cp->CurrentIndex))
         {
         /* Caller wants this data.  Report it.  */
@@ -938,17 +1012,8 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
       }
     else
       {
-      int i;
-
-      /* Process has terminated.  */
-      cp->Terminated = 1;
-      
-      /* Close our copies of the pipe write handles so the pipe
-         threads can detect end-of-data.  */
-      for(i=0; i < cp->PipeCount; ++i)
-        {
-        kwsysProcessCleanupHandle(&cp->Pipe[i].Write);
-        }
+      /* A process has terminated.  */
+      kwsysProcessDestroy(cp, w-WAIT_OBJECT_0);
       }
     }
   
@@ -991,7 +1056,7 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
     }
   else
     {
-    /* The process has terminated and no more data are available.  */
+    /* The children have terminated and no more data are available.  */
     return 0;
     }
 }
@@ -1020,14 +1085,14 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
 
   /* When the last pipe closes in WaitForData, the loop terminates
      without releaseing the pipe's thread.  Release it now.  */
-  if(cp->CurrentIndex < CMPE_PIPE_COUNT)
+  if(cp->CurrentIndex < KWSYSPE_PIPE_COUNT)
     {
     ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Empty, 1, 0);
-    cp->CurrentIndex = CMPE_PIPE_COUNT;
+    cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
     }
 
   /* Wait for all pipe threads to reset.  */
-  for(i=0; i < cp->PipeCount; ++i)
+  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
     {
     WaitForSingleObject(cp->Pipe[i].Reset, INFINITE);
     }
@@ -1036,35 +1101,21 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
   /* Close all the pipes.  */
   kwsysProcessCleanup(cp, 0);
   
-  /* We are done reading all data.  Wait for the child to terminate.
-     This will only block if we killed the child and are waiting for
-     it to cleanup.  */
-  WaitForSingleObject(cp->ProcessInformation.hProcess, INFINITE);
-  
   /* Determine the outcome.  */
   if(cp->Killed)
     {
     /* We killed the child.  */
     cp->State = kwsysProcess_State_Killed;
     }
-  else if(cp->ErrorMessageLength)
-    {
-    /* The Win9x forwarding executing repored data on the special
-       error pipe.  Failed to run the process.  */
-    cp->State = kwsysProcess_State_Error;
-    
-    /* Remove trailing period and newline from message, if any.  */
-    kwsysProcessCleanErrorMessage(cp);
-    }
   else if(cp->TimeoutExpired)
     {
     /* The timeout expired.  */
     cp->State = kwsysProcess_State_Expired;
     }
-  else if(GetExitCodeProcess(cp->ProcessInformation.hProcess,
-                             &cp->ExitCode))
+  else
     {
-    /* The child exited.  */
+    /* The children exited.  Report the outcome of the last process.  */
+    cp->ExitCode = cp->CommandExitCodes[cp->NumberOfCommands-1];
     if(cp->ExitCode & 0xC0000000)
       {
       /* Child terminated due to exceptional behavior.  */
@@ -1111,16 +1162,7 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
       cp->ExitValue = cp->ExitCode & 0x000000FF;
       }
     }
-  else
-    {
-    /* Error getting the child return code.  */
-    strcpy(cp->ErrorMessage, "Error getting child return code");
-    cp->State = kwsysProcess_State_Error;
-    }
-  
-  /* The child process is terminated.  */
-  CloseHandle(cp->ProcessInformation.hProcess);  
-  
+
   return 1;
 }
 
@@ -1138,14 +1180,14 @@ void kwsysProcess_Kill(kwsysProcess* cp)
   
   /* If we are killing a process that just reported data, release
      the pipe's thread.  */
-  if(cp->CurrentIndex < CMPE_PIPE_COUNT)
+  if(cp->CurrentIndex < KWSYSPE_PIPE_COUNT)
     {
     ReleaseSemaphore(cp->Pipe[cp->CurrentIndex].Empty, 1, 0);
-    cp->CurrentIndex = CMPE_PIPE_COUNT;
+    cp->CurrentIndex = KWSYSPE_PIPE_COUNT;
     }
   
   /* Wake up all the pipe threads with dummy data.  */
-  for(i=0; i < cp->PipeCount; ++i)
+  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
     {
     DWORD dummy;
     WriteFile(cp->Pipe[i].Write, "", 1, &dummy, 0);
@@ -1162,7 +1204,7 @@ void kwsysProcess_Kill(kwsysProcess* cp)
     --cp->PipesLeft;
     }
   
-  /* Kill the child.  */
+  /* Kill the children.  */
   cp->Killed = 1;
   if(cp->Win9x)
     {
@@ -1171,8 +1213,17 @@ void kwsysProcess_Kill(kwsysProcess* cp)
     }
   else
     {
-    /* Not Windows 9x.  Just terminate the child.  */
-    TerminateProcess(cp->ProcessInformation.hProcess, 255);
+    /* Not Windows 9x.  Just terminate the children.  */
+    for(i=0; i < cp->NumberOfCommands; ++i)
+      {
+      TerminateProcess(cp->ProcessInformation[i].hProcess, 255);
+      }
+    }
+
+  /* Wait for windows to finish cleaning up the children.  */
+  for(i=0; i < cp->NumberOfCommands; ++i)
+    {
+    WaitForSingleObject(cp->ProcessInformation[i].hProcess, INFINITE);
     }
 }
 
@@ -1215,7 +1266,7 @@ void kwsysProcessPipeThreadReadPipe(kwsysProcess* cp, kwsysProcessPipeData* td)
   while((WaitForSingleObject(td->Empty, INFINITE), !td->Closed))
     {
     /* Read data from the pipe.  This may block until data are available.  */
-    if(!ReadFile(td->Read, td->DataBuffer, CMPE_PIPE_BUFFER_SIZE,
+    if(!ReadFile(td->Read, td->DataBuffer, KWSYSPE_PIPE_BUFFER_SIZE,
                  &td->DataLength, 0))
       {
       if(GetLastError() != ERROR_BROKEN_PIPE)
@@ -1237,6 +1288,262 @@ void kwsysProcessPipeThreadReadPipe(kwsysProcess* cp, kwsysProcessPipeData* td)
 }
 
 /*--------------------------------------------------------------------------*/
+/* Initialize a process control structure for kwsysProcess_Execute.  */
+int kwsysProcessInitialize(kwsysProcess* cp)
+{
+  /* Reset internal status flags.  */
+  cp->TimeoutExpired = 0;
+  cp->Terminated = 0;
+  cp->Killed = 0;
+  cp->ExitException = kwsysProcess_Exception_None;
+  cp->ExitCode = 1;
+  cp->ExitValue = 1;
+  
+  /* Reset error data.  */
+  cp->ErrorMessage[0] = 0;
+  
+  /* Allocate process information for each process.  */
+  cp->ProcessInformation =
+    (PROCESS_INFORMATION*)malloc(sizeof(PROCESS_INFORMATION) *
+                                 cp->NumberOfCommands);
+  if(!cp->ProcessInformation)
+    {
+    return 0;
+    }
+  ZeroMemory(cp->ProcessInformation,
+             sizeof(PROCESS_INFORMATION) * cp->NumberOfCommands);
+  if(cp->CommandExitCodes)
+    {
+    free(cp->CommandExitCodes);
+    }
+  cp->CommandExitCodes = (DWORD*)malloc(sizeof(DWORD)*cp->NumberOfCommands);
+  if(!cp->CommandExitCodes)
+    {
+    return 0;
+    }
+  ZeroMemory(cp->CommandExitCodes, sizeof(DWORD)*cp->NumberOfCommands);
+
+  /* Allocate event wait array.  The first event is cp->Full, the rest
+     are the process termination events.  */
+  cp->ProcessEvents = (PHANDLE)malloc(sizeof(HANDLE)*(cp->NumberOfCommands+1));
+  if(!cp->ProcessEvents)
+    {
+    return 0;
+    }
+  ZeroMemory(cp->ProcessEvents, sizeof(HANDLE) * (cp->NumberOfCommands+1));
+  cp->ProcessEvents[0] = cp->Full;
+  cp->ProcessEventsLength = cp->NumberOfCommands+1;
+
+  return 1;
+}
+
+/*--------------------------------------------------------------------------*/
+int kwsysProcessCreate(kwsysProcess* cp, int index,
+                       kwsysProcessCreateInformation* si,
+                       PHANDLE readEnd)
+{
+  /* Setup the process's stdin.  */
+  if(*readEnd)
+    {
+    /* Create an inherited duplicate of the read end from the output
+       pipe of the previous process.  This also closes the
+       non-inherited version. */
+    if(!DuplicateHandle(GetCurrentProcess(), *readEnd,
+                        GetCurrentProcess(), readEnd,
+                        0, TRUE, (DUPLICATE_CLOSE_SOURCE |
+                                  DUPLICATE_SAME_ACCESS)))
+      {
+      return 0;
+      }
+    si->StartupInfo.hStdInput = *readEnd;
+
+    /* This function is done with this handle.  */
+    *readEnd = 0;
+    }
+  else
+    {
+    si->StartupInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
+    }
+
+  /* Setup the process's stdout.  */
+  {
+  DWORD maybeClose = DUPLICATE_CLOSE_SOURCE;
+  HANDLE writeEnd;
+
+  /* Create the output pipe for this process.  Neither end is directly
+     inherited.  */
+  if(!CreatePipe(readEnd, &writeEnd, 0, 0))
+    {
+    return 0;
+    }
+
+  /* Create an inherited duplicate of the write end.  Close the
+     non-inherited version unless this is the last process.  Save the
+     non-inherited write end of the last process.  */
+  if(index == cp->NumberOfCommands-1)
+    {
+    cp->Pipe[KWSYSPE_PIPE_STDOUT].Write = writeEnd;
+    maybeClose = 0;
+    }
+  if(!DuplicateHandle(GetCurrentProcess(), writeEnd,
+                      GetCurrentProcess(), &si->StartupInfo.hStdOutput,
+                      0, TRUE, (maybeClose | DUPLICATE_SAME_ACCESS)))
+    {
+    return 0;
+    }
+  }
+
+  /* Create the child process.  */
+  {
+  BOOL r;
+  char* realCommand;
+  if(cp->Win9x)
+    {
+    /* Create an error reporting pipe for the forwarding executable.
+       Neither end is directly inherited.  */
+    if(!CreatePipe(&si->ErrorPipeRead, &si->ErrorPipeWrite, 0, 0))
+      {
+      return 0;
+      }
+    
+    /* Create an inherited duplicate of the write end.  This also closes
+       the non-inherited version. */
+    if(!DuplicateHandle(GetCurrentProcess(), si->ErrorPipeWrite,
+                        GetCurrentProcess(), &si->ErrorPipeWrite,
+                        0, TRUE, (DUPLICATE_CLOSE_SOURCE |
+                                  DUPLICATE_SAME_ACCESS)))
+      {
+      return 0;
+      }
+
+    /* The forwarding executable is given a handle to the error pipe
+       and resume and kill events.  */
+    realCommand = malloc(strlen(cp->Win9x)+strlen(cp->Commands[index])+100);
+    if(!realCommand)
+      {
+      return 0;
+      }
+    sprintf(realCommand, "%s %p %p %p %d %s", cp->Win9x,
+            si->ErrorPipeWrite, cp->Win9xResumeEvent, cp->Win9xKillEvent,
+            cp->HideWindow, cp->Commands[index]);
+    }
+  else
+    {
+    realCommand = cp->Commands[index];
+    }
+
+  /* Create the child in a suspended state so we can wait until all
+     children have been created before running any one.  */
+  r = CreateProcess(0, realCommand, 0, 0, TRUE,
+                    cp->Win9x? 0 : CREATE_SUSPENDED, 0,
+                    cp->WorkingDirectory, &si->StartupInfo,
+                    &cp->ProcessInformation[index]);
+
+  if(cp->Win9x)
+    {
+    /* Free memory.  */
+    free(realCommand);
+
+    /* Close the error pipe write end so we can detect when the
+       forwarding executable closes it.  */
+    kwsysProcessCleanupHandle(&si->ErrorPipeWrite);
+    if(r)
+      {
+      /* Wait for the forwarding executable to report an error or
+         close the error pipe to report success.  */
+      DWORD total = 0;
+      DWORD n = 1;
+      while(total < KWSYSPE_PIPE_BUFFER_SIZE && n > 0)
+        {
+        if(ReadFile(si->ErrorPipeRead, cp->ErrorMessage+total,
+                    KWSYSPE_PIPE_BUFFER_SIZE-total, &n, 0))
+          {
+          total += n;
+          }
+        else
+          {
+          n = 0;
+          }
+        }
+      if(total > 0 || GetLastError() != ERROR_BROKEN_PIPE)
+        {
+        /* The forwarding executable could not run the process, or
+           there was an error reading from its error pipe.  Preserve
+           the last error while cleaning up the forwarding executable
+           so the cleanup our caller does reports the proper error.  */
+        DWORD error = GetLastError();
+        kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hThread);
+        kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hProcess);
+        SetLastError(error);
+        return 0;
+        }
+      }
+    kwsysProcessCleanupHandle(&si->ErrorPipeRead);
+    }
+
+  if(!r)
+    {
+    return 0;
+    }
+  }
+
+  /* Successfully created this child process.  */
+  if(index > 0)
+    {
+    /* Close our handle to the input pipe for the current process.  */
+    kwsysProcessCleanupHandle(&si->StartupInfo.hStdInput);
+    }
+
+  /* The parent process does not need the inhertied pipe write end.  */
+  kwsysProcessCleanupHandle(&si->StartupInfo.hStdOutput);
+
+  return 1;
+}
+
+/*--------------------------------------------------------------------------*/
+void kwsysProcessDestroy(kwsysProcess* cp, int event)
+{
+  int i;
+  int index;
+
+  /* Find the process index for the termination event.  */
+  for(index=0; index < cp->NumberOfCommands; ++index)
+    {
+    if(cp->ProcessInformation[index].hProcess == cp->ProcessEvents[event])
+      {
+      break;
+      }
+    }
+
+  /* Check the exit code of the process.  */
+  GetExitCodeProcess(cp->ProcessInformation[index].hProcess,
+                     &cp->CommandExitCodes[index]);
+
+  /* Close the process handle for the terminated process.  */
+  kwsysProcessCleanupHandle(&cp->ProcessInformation[index].hProcess);
+
+  /* Remove the process from the available events.  */
+  cp->ProcessEventsLength -= 1;
+  for(i=event; i < cp->ProcessEventsLength; ++i)
+    {
+    cp->ProcessEvents[i] = cp->ProcessEvents[i+1];
+    }
+
+  /* Check if all processes have terminated.  */
+  if(cp->ProcessEventsLength == 1)
+    {
+    cp->Terminated = 1;
+
+    /* Close our copies of the pipe write handles so the pipe threads
+       can detect end-of-data.  */
+    for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
+      {
+      kwsysProcessCleanupHandle(&cp->Pipe[i].Write);
+      }
+    }
+}
+
+/*--------------------------------------------------------------------------*/
 
 /* Close the given handle if it is open.  Reset its value to 0.  */
 void kwsysProcessCleanupHandle(PHANDLE h)
@@ -1258,37 +1565,71 @@ void kwsysProcessCleanup(kwsysProcess* cp, int error)
   /* If this is an error case, report the error.  */
   if(error)
     {
-    /* Format the error message.  */
-    DWORD original = GetLastError();
-    DWORD length = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
-                                 FORMAT_MESSAGE_IGNORE_INSERTS, 0, original,
-                                 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
-                                 cp->ErrorMessage, CMPE_PIPE_BUFFER_SIZE, 0);
-    if(length < 1)
+    /* Construct an error message if one has not been provided already.  */
+    if(cp->ErrorMessage[0] == 0)
       {
-      /* FormatMessage failed.  Use a default message.  */
-      _snprintf(cp->ErrorMessage, CMPE_PIPE_BUFFER_SIZE,
-                "Process execution failed with error 0x%X.  "
-                "FormatMessage failed with error 0x%X",
-                original, GetLastError());
+      /* Format the error message.  */
+      DWORD original = GetLastError();
+      DWORD length = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
+                                   FORMAT_MESSAGE_IGNORE_INSERTS, 0, original,
+                                   MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
+                                   cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE, 0);
+      if(length < 1)
+        {
+        /* FormatMessage failed.  Use a default message.  */
+        _snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE,
+                  "Process execution failed with error 0x%X.  "
+                  "FormatMessage failed with error 0x%X",
+                  original, GetLastError());
+        }
       }
 
+    /* Remove trailing period and newline, if any.  */
+    kwsysProcessCleanErrorMessage(cp);    
+
     /* Set the error state.  */
     cp->State = kwsysProcess_State_Error;
 
-    /* Remove trailing period and newline, if any.  */
-    kwsysProcessCleanErrorMessage(cp);    
+    /* Cleanup any processes already started in a suspended state.  */
+    if(cp->ProcessInformation)
+      {
+      if(cp->Win9x)
+        {
+        SetEvent(cp->Win9xKillEvent);
+        }
+      else
+        {
+        for(i=0; i < cp->NumberOfCommands; ++i)
+          {
+          if(cp->ProcessInformation[i].hProcess)
+            {
+            TerminateProcess(cp->ProcessInformation[i].hProcess, 255);
+            WaitForSingleObject(cp->ProcessInformation[i].hProcess, INFINITE);
+            }
+          }
+        }      
+      for(i=0; i < cp->NumberOfCommands; ++i)
+        {
+        kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hThread);
+        kwsysProcessCleanupHandle(&cp->ProcessInformation[i].hProcess);
+        }
+      }
     }
-  
+
   /* Free memory.  */
-  if(cp->RealCommand)
+  if(cp->ProcessInformation)
+    {
+    free(cp->ProcessInformation);
+    cp->ProcessInformation = 0;
+    }
+  if(cp->ProcessEvents)
     {
-    free(cp->RealCommand);
-    cp->RealCommand = 0;
+    free(cp->ProcessEvents);
+    cp->ProcessEvents = 0;
     }
 
   /* Close each pipe.  */
-  for(i=0; i < cp->PipeCount; ++i)
+  for(i=0; i < KWSYSPE_PIPE_COUNT; ++i)
     {
     kwsysProcessCleanupHandle(&cp->Pipe[i].Write);
     kwsysProcessCleanupHandle(&cp->Pipe[i].Read);