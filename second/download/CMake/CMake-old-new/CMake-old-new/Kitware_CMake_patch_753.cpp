@@ -68,22 +68,13 @@ bool cmWin32ProcessExecution::Wait(int timeout)
  */
 static void *_PyPopenProcs = NULL;
 
-static bool IsWinNT() 
-//check if we're running NT 
-{
-  OSVERSIONINFO osv;
-  osv.dwOSVersionInfoSize = sizeof(osv);
-  GetVersionEx(&osv);
-  return (osv.dwPlatformId == VER_PLATFORM_WIN32_NT); 
-}
-
 static BOOL RealPopenCreateProcess(const char *cmdstring,
-                                   const char *path, 
-                                   const char *szConsoleSpawn,
-                                   HANDLE hStdin,
-                                   HANDLE hStdout,
-                                   HANDLE hStderr,
-                                   HANDLE *hProcess)
+				   const char *path, 
+				   const char *szConsoleSpawn,
+				   HANDLE hStdin,
+				   HANDLE hStdout,
+				   HANDLE hStderr,
+				   HANDLE *hProcess)
 {
   PROCESS_INFORMATION piProcInfo;
   STARTUPINFO siStartInfo;
@@ -109,7 +100,7 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
     ++comshell;
 
     if (GetVersion() < 0x80000000 &&
-        STRICMP(comshell, "command.com") != 0) 
+	STRICMP(comshell, "command.com") != 0) 
       {
       /* NT/2000 and not using command.com. */
       x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1;
@@ -127,62 +118,62 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
       struct stat statinfo;
       GetModuleFileName(NULL, modulepath, sizeof(modulepath));
       for (i = x = 0; modulepath[i]; i++)
-        if (modulepath[i] == '\\')
-          x = i+1;
+	if (modulepath[i] == '\\')
+	  x = i+1;
       modulepath[x] = '\0';
       /* Create the full-name to w9xpopen, so we can test it exists */
       strncat(modulepath, 
-              szConsoleSpawn, 
-              (sizeof(modulepath)/sizeof(modulepath[0]))
-              -strlen(modulepath));
+	      szConsoleSpawn, 
+	      (sizeof(modulepath)/sizeof(modulepath[0]))
+	      -strlen(modulepath));
       if (stat(modulepath, &statinfo) != 0) 
-        {
-          /* Eeek - file-not-found - possibly an embedding 
-             situation - see if we can locate it in sys.prefix 
-          */
-        strncpy(modulepath, 
-                ".", 
-                sizeof(modulepath)/sizeof(modulepath[0]));
-        if (modulepath[strlen(modulepath)-1] != '\\')
-          strcat(modulepath, "\\");
-        strncat(modulepath, 
-                szConsoleSpawn, 
-                (sizeof(modulepath)/sizeof(modulepath[0]))
-                -strlen(modulepath));
-        /* No where else to look - raise an easily identifiable
-           error, rather than leaving Windows to report
-           "file not found" - as the user is probably blissfully
-           unaware this shim EXE is used, and it will confuse them.
-           (well, it confused me for a while ;-)
-        */
-        if (stat(modulepath, &statinfo) != 0) 
-          {
-          std::cout 
-            << "Can not locate '" << modulepath
-            << "' which is needed "
-            "for popen to work with your shell "
-            "or platform." << std::endl;
-          return FALSE;
-          }
-        }
+	{
+	  /* Eeek - file-not-found - possibly an embedding 
+	     situation - see if we can locate it in sys.prefix 
+	  */
+	strncpy(modulepath, 
+		".", 
+		sizeof(modulepath)/sizeof(modulepath[0]));
+	if (modulepath[strlen(modulepath)-1] != '\\')
+	  strcat(modulepath, "\\");
+	strncat(modulepath, 
+		szConsoleSpawn, 
+		(sizeof(modulepath)/sizeof(modulepath[0]))
+		-strlen(modulepath));
+	/* No where else to look - raise an easily identifiable
+	   error, rather than leaving Windows to report
+	   "file not found" - as the user is probably blissfully
+	   unaware this shim EXE is used, and it will confuse them.
+	   (well, it confused me for a while ;-)
+	*/
+	if (stat(modulepath, &statinfo) != 0) 
+	  {
+	  std::cout 
+	    << "Can not locate '" << modulepath
+	    << "' which is needed "
+	    "for popen to work with your shell "
+	    "or platform." << std::endl;
+	  return FALSE;
+	  }
+	}
       x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1 +
-        (int)strlen(modulepath) + 
-        (int)strlen(szConsoleSpawn) + 1;
+	(int)strlen(modulepath) + 
+	(int)strlen(szConsoleSpawn) + 1;
 
       s2 = (char *)_alloca(x);
       ZeroMemory(s2, x);
       sprintf(
-        s2,
-        "%s %s%s%s",
-        modulepath,
-        s1,
-        s3,
-        cmdstring);
+	s2,
+	"%s %s%s%s",
+	modulepath,
+	s1,
+	s3,
+	cmdstring);
       sprintf(
-        s2,
-        "%s %s",
-        modulepath,
-        cmdstring);
+	s2,
+	"%s %s",
+	modulepath,
+	cmdstring);
       }
     }
 
@@ -191,7 +182,7 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
   else 
     {
     std::cout << "Cannot locate a COMSPEC environment variable to "
-              << "use as the shell" << std::endl;
+	      << "use as the shell" << std::endl;
     return FALSE;
     }
   
@@ -204,20 +195,21 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
   siStartInfo.wShowWindow = SW_HIDE;
 
   if (CreateProcess(NULL,
-                    s2,
-                    NULL,
-                    NULL,
-                    TRUE,
-                    CREATE_NEW_CONSOLE,
-                    NULL,
-                    path,
-                    &siStartInfo,
-                    &piProcInfo) ) 
+		    s2,
+		    NULL,
+		    NULL,
+		    TRUE,
+		    CREATE_NEW_CONSOLE,
+		    NULL,
+		    path,
+		    &siStartInfo,
+		    &piProcInfo) ) 
     {
     /* Close the handles now so anyone waiting is woken. */
     CloseHandle(piProcInfo.hThread);
     /* Return process handle */
     *hProcess = piProcInfo.hProcess;
+    //std::cout << "Process created..." << std::endl;
     return TRUE;
     }
   win32_error("CreateProcess", s2);
@@ -227,9 +219,9 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
 /* The following code is based off of KB: Q190351 */
 
 bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring, 
-                                          const char* path,
-                                          int mode, 
-                                          int n)
+					  const char* path,
+					  int mode, 
+					  int n)
 {
   HANDLE hChildStdinRd, hChildStdinWr, hChildStdoutRd, hChildStdoutWr,
     hChildStderrRd, hChildStderrWr, hChildStdinWrDup, hChildStdoutRdDup,
@@ -240,22 +232,9 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
   int fd1, fd2, fd3;
   //FILE *f1, *f2, *f3;
 
-  SECURITY_DESCRIPTOR sd;
-  if (IsWinNT()) 
-//initialize security descriptor (Windows NT) 
-    {
-    InitializeSecurityDescriptor(&sd,SECURITY_DESCRIPTOR_REVISION);
-    SetSecurityDescriptorDacl(&sd, true, NULL, false);
-    saAttr.lpSecurityDescriptor = &sd;
- 
-    }
-  else saAttr.lpSecurityDescriptor = NULL;
   saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
-  saAttr.bInheritHandle = true;
-
-  //saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
-  //saAttr.bInheritHandle = TRUE;
-  //saAttr.lpSecurityDescriptor = NULL;
+  saAttr.bInheritHandle = TRUE;
+  saAttr.lpSecurityDescriptor = NULL;
 
   if (!CreatePipe(&hChildStdinRd, &hChildStdinWr, &saAttr, 0))
     {
@@ -267,9 +246,9 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
    * the these handles; resulting in non-closeable handles to the pipes
    * being created. */
   fSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdinWr,
-                             GetCurrentProcess(), &hChildStdinWrDup, 0,
-                             FALSE,
-                             DUPLICATE_SAME_ACCESS);
+			     GetCurrentProcess(), &hChildStdinWrDup, 0,
+			     FALSE,
+			     DUPLICATE_SAME_ACCESS);
   if (!fSuccess)
     return win32_error("DuplicateHandle", NULL);
 
@@ -282,8 +261,8 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
     return win32_error("CreatePipe", NULL);
 
   fSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdoutRd,
-                             GetCurrentProcess(), &hChildStdoutRdDup, 0,
-                             FALSE, DUPLICATE_SAME_ACCESS);
+			     GetCurrentProcess(), &hChildStdoutRdDup, 0,
+			     FALSE, DUPLICATE_SAME_ACCESS);
   if (!fSuccess)
     return win32_error("DuplicateHandle", NULL);
 
@@ -296,147 +275,147 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
     if (!CreatePipe(&hChildStderrRd, &hChildStderrWr, &saAttr, 0))
       return win32_error("CreatePipe", NULL);
    fSuccess = DuplicateHandle(GetCurrentProcess(),
-                               hChildStderrRd,
-                               GetCurrentProcess(),
-                               &hChildStderrRdDup, 0,
-                               FALSE, DUPLICATE_SAME_ACCESS);
+			       hChildStderrRd,
+			       GetCurrentProcess(),
+			       &hChildStderrRdDup, 0,
+			       FALSE, DUPLICATE_SAME_ACCESS);
     if (!fSuccess)
       return win32_error("DuplicateHandle", NULL);
     /* Close the inheritable version of ChildStdErr that we're using. */
     CloseHandle(hChildStderrRd);
 
     }
-          
+	  
   switch (n) 
     {
     case POPEN_1:
       switch (mode & (_O_RDONLY | _O_TEXT | _O_BINARY | _O_WRONLY)) 
-        {
-        case _O_WRONLY | _O_TEXT:
-          /* Case for writing to child Stdin in text mode. */
-          fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
-          //f1 = _fdopen(fd1, "w");
-          /* We don't care about these pipes anymore,
-             so close them. */
-          CloseHandle(hChildStdoutRdDup);
-          CloseHandle(hChildStderrRdDup);
-          break;
-
-        case _O_RDONLY | _O_TEXT:
-          /* Case for reading from child Stdout in text mode. */
-          fd1 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
-          //f1 = _fdopen(fd1, "r");
-          /* We don't care about these pipes anymore,
-             so close them. */
-          CloseHandle(hChildStdinWrDup);
-          CloseHandle(hChildStderrRdDup);
-          break;
-
-        case _O_RDONLY | _O_BINARY:
-          /* Case for readinig from child Stdout in
-             binary mode. */
-          fd1 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
-          //f1 = _fdopen(fd1, "rb");
-          /* We don't care about these pipes anymore,
-             so close them. */
-          CloseHandle(hChildStdinWrDup);
-          CloseHandle(hChildStderrRdDup);
-          break;
-
-        case _O_WRONLY | _O_BINARY:
-          /* Case for writing to child Stdin in binary mode. */
-          fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
-          //f1 = _fdopen(fd1, "wb");
-          /* We don't care about these pipes anymore,
-             so close them. */
-          CloseHandle(hChildStdoutRdDup);
-          CloseHandle(hChildStderrRdDup);
-          break;
-        }
+	{
+	case _O_WRONLY | _O_TEXT:
+	  /* Case for writing to child Stdin in text mode. */
+	  fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
+	  //f1 = _fdopen(fd1, "w");
+	  /* We don't care about these pipes anymore,
+	     so close them. */
+	  CloseHandle(hChildStdoutRdDup);
+	  CloseHandle(hChildStderrRdDup);
+	  break;
+
+	case _O_RDONLY | _O_TEXT:
+	  /* Case for reading from child Stdout in text mode. */
+	  fd1 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
+	  //f1 = _fdopen(fd1, "r");
+	  /* We don't care about these pipes anymore,
+	     so close them. */
+	  CloseHandle(hChildStdinWrDup);
+	  CloseHandle(hChildStderrRdDup);
+	  break;
+
+	case _O_RDONLY | _O_BINARY:
+	  /* Case for readinig from child Stdout in
+	     binary mode. */
+	  fd1 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
+	  //f1 = _fdopen(fd1, "rb");
+	  /* We don't care about these pipes anymore,
+	     so close them. */
+	  CloseHandle(hChildStdinWrDup);
+	  CloseHandle(hChildStderrRdDup);
+	  break;
+
+	case _O_WRONLY | _O_BINARY:
+	  /* Case for writing to child Stdin in binary mode. */
+	  fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
+	  //f1 = _fdopen(fd1, "wb");
+	  /* We don't care about these pipes anymore,
+	     so close them. */
+	  CloseHandle(hChildStdoutRdDup);
+	  CloseHandle(hChildStderrRdDup);
+	  break;
+	}
       break;
-        
+	
     case POPEN_2:
     case POPEN_4: 
       if ( 1 ) 
-        {
+	{
         // Comment this out. Maybe we will need it in the future.
         // file IO access to the process might be cool.
-        //char *m1,  *m2;
-        
-        //if (mode && _O_TEXT) 
-        //  {
-        //  m1 = "r";
-        //  m2 = "w";
-        //  } 
-        //else 
-        //  {
-        //  m1 = "rb";
-        //  m2 = "wb";
-        //  }
-
-        fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
-        //f1 = _fdopen(fd1, m2);
-        fd2 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
-        //f2 = _fdopen(fd2, m1);
-
-        if (n != 4)
+	//char *m1,  *m2;
+	
+	//if (mode && _O_TEXT) 
+	//  {
+	//  m1 = "r";
+	//  m2 = "w";
+	//  } 
+	//else 
+	//  {
+	//  m1 = "rb";
+	//  m2 = "wb";
+	//  }
+
+	fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
+	//f1 = _fdopen(fd1, m2);
+	fd2 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
+	//f2 = _fdopen(fd2, m1);
+
+	if (n != 4)
           {
-          CloseHandle(hChildStderrRdDup);
+	  CloseHandle(hChildStderrRdDup);
           }
 
-        break;
-        }
-        
+	break;
+	}
+	
     case POPEN_3:
       if ( 1) 
-        {
+	{
         // Comment this out. Maybe we will need it in the future.
         // file IO access to the process might be cool.
-        //char *m1, *m2;
+	//char *m1, *m2;
       
-        //if (mode && _O_TEXT) 
-        //  {
-        //  m1 = "r";
-        //  m2 = "w";
-        //  } 
-        //else 
-        //  {
-        //  m1 = "rb";
-        //  m2 = "wb";
-        //  }
-
-
-        fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
-        //f1 = _fdopen(fd1, m2);
-        fd2 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
-        //f2 = _fdopen(fd2, m1);
-        fd3 = _open_osfhandle(TO_INTPTR(hChildStderrRdDup), mode);
-        //f3 = _fdopen(fd3, m1);        
-
-        break;
-        }
+	//if (mode && _O_TEXT) 
+	//  {
+	//  m1 = "r";
+	//  m2 = "w";
+	//  } 
+	//else 
+	//  {
+	//  m1 = "rb";
+	//  m2 = "wb";
+	//  }
+
+
+	fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
+	//f1 = _fdopen(fd1, m2);
+	fd2 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
+	//f2 = _fdopen(fd2, m1);
+	fd3 = _open_osfhandle(TO_INTPTR(hChildStderrRdDup), mode);
+	//f3 = _fdopen(fd3, m1);	
+
+	break;
+	}
     }
 
   if (n == POPEN_4) 
     {
     if (!RealPopenCreateProcess(cmdstring,
-                                path,
-                                this->m_ConsoleSpawn.c_str(),
-                                hChildStdinRd,
-                                hChildStdoutWr,
-                                hChildStdoutWr,
-                                &hProcess))
+				path,
+				this->m_ConsoleSpawn.c_str(),
+				hChildStdinRd,
+				hChildStdoutWr,
+				hChildStdoutWr,
+				&hProcess))
       return NULL;
     }
   else 
     {
     if (!RealPopenCreateProcess(cmdstring,
-                                path,
-                                this->m_ConsoleSpawn.c_str(),
-                                hChildStdinRd,
-                                hChildStdoutWr,
-                                hChildStderrWr,
-                                &hProcess))
+				path,
+				this->m_ConsoleSpawn.c_str(),
+				hChildStdinRd,
+				hChildStdoutWr,
+				hChildStderrWr,
+				&hProcess))
       return NULL;
     }
 
@@ -460,10 +439,10 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 
   if (!CloseHandle(hChildStdinRd))
     return win32_error("CloseHandle", NULL);
-          
+	  
   if (!CloseHandle(hChildStdoutWr))
     return win32_error("CloseHandle", NULL);
-          
+	  
   if ((n != 4) && (!CloseHandle(hChildStderrWr)))
     return win32_error("CloseHandle", NULL);
   
@@ -533,31 +512,38 @@ bool cmWin32ProcessExecution::PrivateClose(int timeout)
 
   std::string output = "";
   bool done = false;
-    
   while(!done)
     {
-    char buffer[1023]="";
-    int len = 0;
-    Sleep(1);
+    Sleep(10);
     bool have_some = false;
-    len = read(this->m_pStdErr, buffer, 1023);
-    if ( len > 0 )
+    struct _stat fsout;
+    struct _stat fserr;
+    int rout = _fstat(this->m_pStdOut, &fsout);
+    int rerr = _fstat(this->m_pStdErr, &fserr);
+    if ( rout && rerr )
+      {
+      break;
+      }
+    if (fserr.st_size > 0)
       {
+      char buffer[1023];
+      int len = read(this->m_pStdErr, buffer, 1023);
       buffer[len] = 0;
       if ( this->m_Verbose )
-        {
-        std::cout << buffer << std::flush;
-        }
+	{
+	std::cout << buffer << std::flush;
+	}
       output += buffer;
       have_some = true;
       }
-    len = read(this->m_pStdOut, buffer, 1023);
-    if ( len > 0 )
+    if (fsout.st_size > 0)
       {
+      char buffer[1023];
+      int len = read(this->m_pStdOut, buffer, 1023);
       buffer[len] = 0;
       if ( this->m_Verbose )
 	{
-        std::cout << buffer << std::flush;
+	std::cout << buffer << std::flush;
 	}
       output += buffer;
       have_some = true;