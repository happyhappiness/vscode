@@ -61,25 +61,6 @@ bool cmWin32ProcessExecution::Wait(int timeout)
   return this->PrivateClose(timeout);
 }
 
-#define PERROR(str) //::ErrorMessage(__LINE__, str)
-static void ErrorMessage(int line, char *str)  //display detailed error info
-{
-  DWORD lastmsg = GetLastError();
-  LPVOID msg;
-  FormatMessage(
-    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
-    NULL,
-    lastmsg,
-    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
-    (LPTSTR) &msg,
-    0,
-    NULL
-  );
-  printf("%d - %s: %s (%d)\n",line,str,msg, lastmsg);
-  LocalFree(msg);
-  ::SetLastError(ERROR_SUCCESS);
-}
-
 /*
  * Internal dictionary mapping popen* file pointers to process handles,
  * for use when retrieving the process exit code.  See _PyPclose() below
@@ -95,25 +76,18 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
 				   HANDLE hStderr,
 				   HANDLE *hProcess)
 {
-  PERROR("Start");
-  //std::cout << "Run: " << cmdstring << std::endl;
-  PERROR("Start");
   PROCESS_INFORMATION piProcInfo;
-  PERROR("PROCESS_INFORMATION");
   STARTUPINFO siStartInfo;
-  PERROR("STARTUPINFO");
   char *s1,*s2, *s3 = " /c ";
   int i;
   int x;
   if (i = GetEnvironmentVariable("COMSPEC",NULL,0)) 
     {
-    PERROR("GetEnvironmentVariable");
     char *comshell;
 
     s1 = (char *)_alloca(i);
     if (!(x = GetEnvironmentVariable("COMSPEC", s1, i)))
       {
-      PERROR("GetEnvironmentVariable");
       return x;
       }
 
@@ -133,8 +107,6 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
       s2 = (char *)_alloca(x);
       ZeroMemory(s2, x);
       sprintf(s2, "%s%s%s", s1, s3, cmdstring);
-      //std::cout << "s1: " << s1 << " s2: " << s2 << " s3: " << s3 
-      //		<< std::endl;
       }
     else 
       {
@@ -156,9 +128,9 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
 	      -strlen(modulepath));
       if (stat(modulepath, &statinfo) != 0) 
 	{
-				/* Eeek - file-not-found - possibly an embedding 
-				   situation - see if we can locate it in sys.prefix 
-				*/
+	  /* Eeek - file-not-found - possibly an embedding 
+	     situation - see if we can locate it in sys.prefix 
+	  */
 	strncpy(modulepath, 
 		".", 
 		sizeof(modulepath)/sizeof(modulepath[0]));
@@ -177,7 +149,7 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
 	if (stat(modulepath, &statinfo) != 0) 
 	  {
 	  std::cout 
-	    << "Can not locate '" << szConsoleSpawn 
+	    << "Can not locate '" << modulepath
 	    << "' which is needed "
 	    "for popen to work with your shell "
 	    "or platform." << std::endl;
@@ -197,6 +169,11 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
 	s1,
 	s3,
 	cmdstring);
+      sprintf(
+	s2,
+	"%s \"%s\"",
+	modulepath,
+	cmdstring);
       }
     }
 
@@ -228,10 +205,8 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
 		    &siStartInfo,
 		    &piProcInfo) ) 
     {
-    PERROR("CreateProcess");
     /* Close the handles now so anyone waiting is woken. */
     CloseHandle(piProcInfo.hThread);
-    PERROR("Close Handle");
     /* Return process handle */
     *hProcess = piProcInfo.hProcess;
     //std::cout << "Process created..." << std::endl;
@@ -265,7 +240,6 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
     {
     return win32_error("CreatePipe", NULL);
     }
-  PERROR("CreatePipe");
     
   /* Create new output read handle and the input write handle. Set
    * the inheritance properties to FALSE. Otherwise, the child inherits
@@ -277,13 +251,11 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 			     DUPLICATE_SAME_ACCESS);
   if (!fSuccess)
     return win32_error("DuplicateHandle", NULL);
-  PERROR("DuplicateHandle");
 
 
   /* Close the inheritable version of ChildStdin
      that we're using. */
   CloseHandle(hChildStdinWr);
-  PERROR("CloseHandle");
 
   if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0))
     return win32_error("CreatePipe", NULL);
@@ -293,29 +265,25 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 			     FALSE, DUPLICATE_SAME_ACCESS);
   if (!fSuccess)
     return win32_error("DuplicateHandle", NULL);
-  PERROR("DuplicateHandle");
 
   /* Close the inheritable version of ChildStdout
      that we're using. */
   CloseHandle(hChildStdoutRd);
-  PERROR("CloseHandle");
 
   if (n != POPEN_4) 
     {
     if (!CreatePipe(&hChildStderrRd, &hChildStderrWr, &saAttr, 0))
       return win32_error("CreatePipe", NULL);
-   PERROR("CreatePipe");
    fSuccess = DuplicateHandle(GetCurrentProcess(),
 			       hChildStderrRd,
 			       GetCurrentProcess(),
 			       &hChildStderrRdDup, 0,
 			       FALSE, DUPLICATE_SAME_ACCESS);
     if (!fSuccess)
       return win32_error("DuplicateHandle", NULL);
-    PERROR("DuplicateHandle");
     /* Close the inheritable version of ChildStdErr that we're using. */
     CloseHandle(hChildStderrRd);
-    PERROR("CloseHandle");
+
     }
 	  
   switch (n) 
@@ -331,7 +299,6 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 	     so close them. */
 	  CloseHandle(hChildStdoutRdDup);
 	  CloseHandle(hChildStderrRdDup);
-          PERROR("CloseHandle");
 	  break;
 
 	case _O_RDONLY | _O_TEXT:
@@ -342,7 +309,6 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 	     so close them. */
 	  CloseHandle(hChildStdinWrDup);
 	  CloseHandle(hChildStderrRdDup);
-          PERROR("CloseHandle");
 	  break;
 
 	case _O_RDONLY | _O_BINARY:
@@ -354,7 +320,6 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 	     so close them. */
 	  CloseHandle(hChildStdinWrDup);
 	  CloseHandle(hChildStderrRdDup);
-          PERROR("CloseHandle");
 	  break;
 
 	case _O_WRONLY | _O_BINARY:
@@ -365,7 +330,6 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 	     so close them. */
 	  CloseHandle(hChildStdoutRdDup);
 	  CloseHandle(hChildStderrRdDup);
-          PERROR("CloseHandle");
 	  break;
 	}
       break;
@@ -393,12 +357,10 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 	//f1 = _fdopen(fd1, m2);
 	fd2 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
 	//f2 = _fdopen(fd2, m1);
-        PERROR("_open_osfhandle");
 
 	if (n != 4)
           {
 	  CloseHandle(hChildStderrRdDup);
-          PERROR("CloseHandle");              
           }
 
 	break;
@@ -429,7 +391,6 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 	//f2 = _fdopen(fd2, m1);
 	fd3 = _open_osfhandle(TO_INTPTR(hChildStderrRdDup), mode);
 	//f3 = _fdopen(fd3, m1);	
-        PERROR("_open_osfhandle");
 
 	break;
 	}
@@ -478,15 +439,12 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 
   if (!CloseHandle(hChildStdinRd))
     return win32_error("CloseHandle", NULL);
-  PERROR("CloseHandle");
 	  
   if (!CloseHandle(hChildStdoutWr))
     return win32_error("CloseHandle", NULL);
-  PERROR("CloseHandle");
 	  
   if ((n != 4) && (!CloseHandle(hChildStderrWr)))
     return win32_error("CloseHandle", NULL);
-  PERROR("CloseHandle");
   
   this->m_ProcessHandle = hProcess;
   if ( fd1 >= 0 )
@@ -504,8 +462,6 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
     //  this->m_StdErr = f3;
     this->m_pStdErr = fd3;
     }
-  //std::cout << "Process created for real..." << std::endl;
-  //std::cout << fd1 << " " << fd2 << " " << fd3 << std::endl;
 
   return true;
 }
@@ -570,7 +526,6 @@ bool cmWin32ProcessExecution::PrivateClose(int timeout)
       }
     if (fserr.st_size > 0)
       {
-      //std::cout << "Some error" << std::endl;
       char buffer[1023];
       int len = read(this->m_pStdErr, buffer, 1023);
       buffer[len] = 0;
@@ -583,7 +538,6 @@ bool cmWin32ProcessExecution::PrivateClose(int timeout)
       }
     if (fsout.st_size > 0)
       {
-      //std::cout << "Some output" << std::endl;
       char buffer[1023];
       int len = read(this->m_pStdOut, buffer, 1023);
       buffer[len] = 0;
@@ -600,14 +554,11 @@ bool cmWin32ProcessExecution::PrivateClose(int timeout)
       GetExitCodeProcess(hProcess,&exitCode);
       if (exitCode != STILL_ACTIVE)
         {
-        //std::cout << "STILL_ACTIVE = " << STILL_ACTIVE << std::endl;
-        //std::cout << "Process is not active any more: " << exitCode << std::endl;
         break;
         }
       }
     }  
 
-  //std::cout << "Waiting for process to close" << std::endl;
   
   if (WaitForSingleObject(hProcess, INFINITE) != WAIT_FAILED &&
       GetExitCodeProcess(hProcess, &exit_code)) 
@@ -632,8 +583,6 @@ bool cmWin32ProcessExecution::PrivateClose(int timeout)
     result = -1;
     }
 
-  //std::cout << "Process closed with error code: " << result << std::endl;
-	
   /* Free up the native handle at this point */
   CloseHandle(hProcess);
   this->m_ExitValue = result;
@@ -666,11 +615,13 @@ int cmWin32ProcessExecution::Windows9xHack(const char* command)
   si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
   si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
 
+  
+  char * app = 0;
   char* cmd = new char[ strlen(command) + 1 ];
   strcpy(cmd, command);
 
   bRet = CreateProcess(
-    NULL, cmd,
+    app, cmd,
     NULL, NULL,
     TRUE, 0,
     NULL, NULL,