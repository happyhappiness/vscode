@@ -12,12 +12,14 @@
 #include "kwsysPrivate.h"
 #include KWSYS_HEADER(Process.h)
 #include KWSYS_HEADER(System.h)
+#include KWSYS_HEADER(Encoding.h)
 
 /* Work-around CMake dependency scanning limitation.  This must
    duplicate the above list of headers.  */
 #if 0
 # include "Process.h.in"
 # include "System.h.in"
+# include "Encoding_c.h.in"
 #endif
 
 /*
@@ -88,9 +90,10 @@ typedef LARGE_INTEGER kwsysProcessTime;
 typedef struct kwsysProcessCreateInformation_s
 {
   /* Windows child startup control data.  */
-  STARTUPINFO StartupInfo;
+  STARTUPINFOW StartupInfo;
 } kwsysProcessCreateInformation;
 
+
 /*--------------------------------------------------------------------------*/
 typedef struct kwsysProcessPipeData_s kwsysProcessPipeData;
 static DWORD WINAPI kwsysProcessPipeThreadRead(LPVOID ptd);
@@ -197,14 +200,14 @@ struct kwsysProcess_s
   int State;
 
   /* The command lines to execute.  */
-  char** Commands;
+  wchar_t** Commands;
   int NumberOfCommands;
 
   /* The exit code of each command.  */
   DWORD* CommandExitCodes;
 
   /* The working directory for the child process.  */
-  char* WorkingDirectory;
+  wchar_t* WorkingDirectory;
 
   /* Whether to create the child as a detached process.  */
   int OptionDetach;
@@ -299,7 +302,7 @@ struct kwsysProcess_s
 
   /* Real working directory of our own process.  */
   DWORD RealWorkingDirectoryLength;
-  char* RealWorkingDirectory;
+  wchar_t* RealWorkingDirectory;
 };
 
 /*--------------------------------------------------------------------------*/
@@ -546,17 +549,18 @@ int kwsysProcess_SetCommand(kwsysProcess* cp, char const* const* command)
 int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
 {
   int newNumberOfCommands;
-  char** newCommands;
+  wchar_t** newCommands;
 
   /* Make sure we have a command to add.  */
   if(!cp || !command || !*command)
     {
     return 0;
     }
 
+
   /* Allocate a new array for command pointers.  */
   newNumberOfCommands = cp->NumberOfCommands + 1;
-  if(!(newCommands = (char**)malloc(sizeof(char*) * newNumberOfCommands)))
+  if(!(newCommands = (wchar_t**)malloc(sizeof(wchar_t*) * newNumberOfCommands)))
     {
     /* Out of memory.  */
     return 0;
@@ -585,8 +589,8 @@ int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
   /* Allocate enough space for the command.  We do not need an extra
      byte for the terminating null because we allocated a space for
      the first argument that we will not use.  */
-  newCommands[cp->NumberOfCommands] = (char*)malloc(length);
-  if(!newCommands[cp->NumberOfCommands])
+  char* new_cmd = malloc(length);
+  if(!new_cmd)
     {
     /* Out of memory.  */
     free(newCommands);
@@ -595,9 +599,13 @@ int kwsysProcess_AddCommand(kwsysProcess* cp, char const* const* command)
 
   /* Construct the command line in the allocated buffer.  */
   kwsysProcessComputeCommandLine(cp, command,
-                                 newCommands[cp->NumberOfCommands]);
+                                 new_cmd);
+
+  newCommands[cp->NumberOfCommands] = kwsysEncoding_DupToWide(new_cmd);
+  free(new_cmd);
   }
 
+
   /* Save the new array of commands.  */
   free(cp->Commands);
   cp->Commands = newCommands;
@@ -633,22 +641,26 @@ int kwsysProcess_SetWorkingDirectory(kwsysProcess* cp, const char* dir)
     }
   if(dir && dir[0])
     {
+    wchar_t* wdir = kwsysEncoding_DupToWide(dir);
     /* We must convert the working directory to a full path.  */
-    DWORD length = GetFullPathName(dir, 0, 0, 0);
+    DWORD length = GetFullPathNameW(wdir, 0, 0, 0);
     if(length > 0)
       {
-      cp->WorkingDirectory = (char*)malloc(length);
-      if(!cp->WorkingDirectory)
+      wchar_t* work_dir = malloc(length*sizeof(wchar_t));
+      if(!work_dir)
         {
+        free(wdir);
         return 0;
         }
-      if(!GetFullPathName(dir, length, cp->WorkingDirectory, 0))
+      if(!GetFullPathNameW(wdir, length, work_dir, 0))
         {
-        free(cp->WorkingDirectory);
-        cp->WorkingDirectory = 0;
+        free(work_dir);
+        free(wdir);
         return 0;
         }
+      cp->WorkingDirectory = work_dir;
       }
+    free(wdir);
     }
   return 1;
 }
@@ -879,13 +891,13 @@ void kwsysProcess_Execute(kwsysProcess* cp)
      to make pipe file paths evaluate correctly.  */
   if(cp->WorkingDirectory)
     {
-    if(!GetCurrentDirectory(cp->RealWorkingDirectoryLength,
+    if(!GetCurrentDirectoryW(cp->RealWorkingDirectoryLength,
                             cp->RealWorkingDirectory))
       {
       kwsysProcessCleanup(cp, 1);
       return;
       }
-    SetCurrentDirectory(cp->WorkingDirectory);
+    SetCurrentDirectoryW(cp->WorkingDirectory);
     }
 
   /* Initialize startup info data.  */
@@ -1003,7 +1015,7 @@ void kwsysProcess_Execute(kwsysProcess* cp)
   /* Restore the working directory.  */
   if(cp->RealWorkingDirectory)
     {
-    SetCurrentDirectory(cp->RealWorkingDirectory);
+    SetCurrentDirectoryW(cp->RealWorkingDirectory);
     free(cp->RealWorkingDirectory);
     cp->RealWorkingDirectory = 0;
     }
@@ -1507,10 +1519,10 @@ int kwsysProcessInitialize(kwsysProcess* cp)
   /* Allocate space to save the real working directory of this process.  */
   if(cp->WorkingDirectory)
     {
-    cp->RealWorkingDirectoryLength = GetCurrentDirectory(0, 0);
+    cp->RealWorkingDirectoryLength = GetCurrentDirectoryW(0, 0);
     if(cp->RealWorkingDirectoryLength > 0)
       {
-      cp->RealWorkingDirectory = (char*)malloc(cp->RealWorkingDirectoryLength);
+      cp->RealWorkingDirectory = malloc(cp->RealWorkingDirectoryLength * sizeof(wchar_t));
       if(!cp->RealWorkingDirectory)
         {
         return 0;
@@ -1547,9 +1559,11 @@ int kwsysProcessCreate(kwsysProcess* cp, int index,
   else if(cp->PipeFileSTDIN)
     {
     /* Create a handle to read a file for stdin.  */
-    HANDLE fin = CreateFile(cp->PipeFileSTDIN, GENERIC_READ|GENERIC_WRITE,
+    wchar_t* wstdin = kwsysEncoding_DupToWide(cp->PipeFileSTDIN);
+    HANDLE fin = CreateFileW(wstdin, GENERIC_READ|GENERIC_WRITE,
                             FILE_SHARE_READ|FILE_SHARE_WRITE,
                             0, OPEN_EXISTING, 0, 0);
+    free(wstdin);
     if(fin == INVALID_HANDLE_VALUE)
       {
       return 0;
@@ -1655,7 +1669,7 @@ int kwsysProcessCreate(kwsysProcess* cp, int index,
 
   /* Create the child in a suspended state so we can wait until all
      children have been created before running any one.  */
-  if(!CreateProcess(0, cp->Commands[index], 0, 0, TRUE, CREATE_SUSPENDED, 0,
+  if(!CreateProcessW(0, cp->Commands[index], 0, 0, TRUE, CREATE_SUSPENDED, 0,
                     0, &si->StartupInfo, &cp->ProcessInformation[index]))
     {
     return 0;
@@ -1729,6 +1743,7 @@ void kwsysProcessDestroy(kwsysProcess* cp, int event)
 int kwsysProcessSetupOutputPipeFile(PHANDLE phandle, const char* name)
 {
   HANDLE fout;
+  wchar_t* wname;
   if(!name)
     {
     return 1;
@@ -1738,8 +1753,10 @@ int kwsysProcessSetupOutputPipeFile(PHANDLE phandle, const char* name)
   kwsysProcessCleanupHandle(phandle);
 
   /* Create a handle to write a file for the pipe.  */
-  fout = CreateFile(name, GENERIC_WRITE, FILE_SHARE_READ, 0,
+  wname = kwsysEncoding_DupToWide(name);
+  fout = CreateFileW(wname, GENERIC_WRITE, FILE_SHARE_READ, 0,
                     CREATE_ALWAYS, 0, 0);
+  free(wname);
   if(fout == INVALID_HANDLE_VALUE)
     {
     return 0;
@@ -1883,10 +1900,13 @@ void kwsysProcessCleanup(kwsysProcess* cp, int error)
       {
       /* Format the error message.  */
       DWORD original = GetLastError();
-      DWORD length = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
+      wchar_t err_msg[KWSYSPE_PIPE_BUFFER_SIZE];
+      DWORD length = FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM |
                                    FORMAT_MESSAGE_IGNORE_INSERTS, 0, original,
                                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
-                                   cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE, 0);
+                                   err_msg, KWSYSPE_PIPE_BUFFER_SIZE, 0);
+      WideCharToMultiByte(CP_UTF8, 0, err_msg, -1, cp->ErrorMessage,
+                          KWSYSPE_PIPE_BUFFER_SIZE, NULL, NULL);
       if(length < 1)
         {
         /* FormatMessage failed.  Use a default message.  */
@@ -1924,7 +1944,7 @@ void kwsysProcessCleanup(kwsysProcess* cp, int error)
     /* Restore the working directory.  */
     if(cp->RealWorkingDirectory)
       {
-      SetCurrentDirectory(cp->RealWorkingDirectory);
+      SetCurrentDirectoryW(cp->RealWorkingDirectory);
       }
     }
 
@@ -2222,7 +2242,7 @@ static void kwsysProcessSetExitException(kwsysProcess* cp, int code)
     case STATUS_NO_MEMORY:
     default:
       cp->ExitException = kwsysProcess_Exception_Other;
-      sprintf(cp->ExitExceptionString, "Exit code 0x%x\n", code);
+      _snprintf(cp->ExitExceptionString, KWSYSPE_PIPE_BUFFER_SIZE, "Exit code 0x%x\n", code);
       break;
     }
 }
@@ -2430,7 +2450,7 @@ static int kwsysProcess_List__New_NT4(kwsysProcess_List* self)
      loaded in this program.  This does not actually increment the
      reference count to the module so we do not need to close the
      handle.  */
-  HMODULE hNT = GetModuleHandle("ntdll.dll");
+  HMODULE hNT = GetModuleHandleW(L"ntdll.dll");
   if(hNT)
     {
     /* Get pointers to the needed API functions.  */
@@ -2534,7 +2554,7 @@ static int kwsysProcess_List__New_Snapshot(kwsysProcess_List* self)
      loaded in this program.  This does not actually increment the
      reference count to the module so we do not need to close the
      handle.  */
-  HMODULE hKernel = GetModuleHandle("kernel32.dll");
+  HMODULE hKernel = GetModuleHandleW(L"kernel32.dll");
   if(hKernel)
     {
     self->P_CreateToolhelp32Snapshot =