@@ -279,12 +279,12 @@ bool cmWin32ProcessExecution::Wait(int timeout)
 static void *_PyPopenProcs = NULL;
 
 static BOOL RealPopenCreateProcess(const char *cmdstring,
-				   const char *path, 
-				   const char *szConsoleSpawn,
-				   HANDLE hStdin,
-				   HANDLE hStdout,
-				   HANDLE hStderr,
-				   HANDLE *hProcess)
+                                   const char *path, 
+                                   const char *szConsoleSpawn,
+                                   HANDLE hStdin,
+                                   HANDLE hStdout,
+                                   HANDLE hStderr,
+                                   HANDLE *hProcess)
 {
   PROCESS_INFORMATION piProcInfo;
   STARTUPINFO siStartInfo;
@@ -310,13 +310,14 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
     ++comshell;
 
     if (GetVersion() < 0x80000000 &&
-	STRICMP(comshell, "command.com") != 0) 
+        STRICMP(comshell, "command.com") != 0) 
       {
       /* NT/2000 and not using command.com. */
       x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1;
       s2 = (char *)_alloca(x);
       ZeroMemory(s2, x);
-      sprintf(s2, "%s%s%s", s1, s3, cmdstring);
+      //sprintf(s2, "%s%s%s", s1, s3, cmdstring);
+      sprintf(s2, "%s", cmdstring);
       }
     else 
       {
@@ -328,62 +329,62 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
       struct stat statinfo;
       GetModuleFileName(NULL, modulepath, sizeof(modulepath));
       for (i = x = 0; modulepath[i]; i++)
-	if (modulepath[i] == '\\')
-	  x = i+1;
+        if (modulepath[i] == '\\')
+          x = i+1;
       modulepath[x] = '\0';
       /* Create the full-name to w9xpopen, so we can test it exists */
       strncat(modulepath, 
-	      szConsoleSpawn, 
-	      (sizeof(modulepath)/sizeof(modulepath[0]))
-	      -strlen(modulepath));
+              szConsoleSpawn, 
+              (sizeof(modulepath)/sizeof(modulepath[0]))
+              -strlen(modulepath));
       if (stat(modulepath, &statinfo) != 0) 
-	{
-	  /* Eeek - file-not-found - possibly an embedding 
-	     situation - see if we can locate it in sys.prefix 
-	  */
-	strncpy(modulepath, 
-		".", 
-		sizeof(modulepath)/sizeof(modulepath[0]));
-	if (modulepath[strlen(modulepath)-1] != '\\')
-	  strcat(modulepath, "\\");
-	strncat(modulepath, 
-		szConsoleSpawn, 
-		(sizeof(modulepath)/sizeof(modulepath[0]))
-		-strlen(modulepath));
-	/* No where else to look - raise an easily identifiable
-	   error, rather than leaving Windows to report
-	   "file not found" - as the user is probably blissfully
-	   unaware this shim EXE is used, and it will confuse them.
-	   (well, it confused me for a while ;-)
-	*/
-	if (stat(modulepath, &statinfo) != 0) 
-	  {
-	  std::cout 
-	    << "Can not locate '" << modulepath
-	    << "' which is needed "
-	    "for popen to work with your shell "
-	    "or platform." << std::endl;
-	  return FALSE;
-	  }
-	}
+        {
+          /* Eeek - file-not-found - possibly an embedding 
+             situation - see if we can locate it in sys.prefix 
+          */
+        strncpy(modulepath, 
+                ".", 
+                sizeof(modulepath)/sizeof(modulepath[0]));
+        if (modulepath[strlen(modulepath)-1] != '\\')
+          strcat(modulepath, "\\");
+        strncat(modulepath, 
+                szConsoleSpawn, 
+                (sizeof(modulepath)/sizeof(modulepath[0]))
+                -strlen(modulepath));
+        /* No where else to look - raise an easily identifiable
+           error, rather than leaving Windows to report
+           "file not found" - as the user is probably blissfully
+           unaware this shim EXE is used, and it will confuse them.
+           (well, it confused me for a while ;-)
+        */
+        if (stat(modulepath, &statinfo) != 0) 
+          {
+          std::cout 
+            << "Can not locate '" << modulepath
+            << "' which is needed "
+            "for popen to work with your shell "
+            "or platform." << std::endl;
+          return FALSE;
+          }
+        }
       x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1 +
-	(int)strlen(modulepath) + 
-	(int)strlen(szConsoleSpawn) + 1;
+        (int)strlen(modulepath) + 
+        (int)strlen(szConsoleSpawn) + 1;
 
       s2 = (char *)_alloca(x);
       ZeroMemory(s2, x);
       sprintf(
-	s2,
-	"%s %s%s%s",
-	modulepath,
-	s1,
-	s3,
-	cmdstring);
+        s2,
+        "%s %s%s%s",
+        modulepath,
+        s1,
+        s3,
+        cmdstring);
       sprintf(
-	s2,
-	"%s %s",
-	modulepath,
-	cmdstring);
+        s2,
+        "%s %s",
+        modulepath,
+        cmdstring);
       }
     }
 
@@ -392,7 +393,7 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
   else 
     {
     std::cout << "Cannot locate a COMSPEC environment variable to "
-	      << "use as the shell" << std::endl;
+              << "use as the shell" << std::endl;
     return FALSE;
     }
   
@@ -404,16 +405,17 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
   siStartInfo.hStdError = hStderr;
   siStartInfo.wShowWindow = SW_HIDE;
 
+  //std::cout << "Create process: " << s2 << std::endl;
   if (CreateProcess(NULL,
-		    s2,
-		    NULL,
-		    NULL,
-		    TRUE,
-		    CREATE_NEW_CONSOLE,
-		    NULL,
-		    path,
-		    &siStartInfo,
-		    &piProcInfo) ) 
+                    s2,
+                    NULL,
+                    NULL,
+                    TRUE,
+                    CREATE_NEW_CONSOLE,
+                    NULL,
+                    path,
+                    &siStartInfo,
+                    &piProcInfo) ) 
     {
     /* Close the handles now so anyone waiting is woken. */
     CloseHandle(piProcInfo.hThread);
@@ -429,9 +431,9 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
 /* The following code is based off of KB: Q190351 */
 
 bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring, 
-					  const char* path,
-					  int mode, 
-					  int n)
+                                          const char* path,
+                                          int mode, 
+                                          int n)
 {
   HANDLE hChildStdinRd, hChildStdinWr, hChildStdoutRd, hChildStdoutWr,
     hChildStderrRd, hChildStderrWr, hChildStdinWrDup, hChildStdoutRdDup,
@@ -456,9 +458,9 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
    * the these handles; resulting in non-closeable handles to the pipes
    * being created. */
   fSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdinWr,
-			     GetCurrentProcess(), &hChildStdinWrDup, 0,
-			     FALSE,
-			     DUPLICATE_SAME_ACCESS);
+                             GetCurrentProcess(), &hChildStdinWrDup, 0,
+                             FALSE,
+                             DUPLICATE_SAME_ACCESS);
   if (!fSuccess)
     return win32_error("DuplicateHandle", NULL);
 
@@ -471,8 +473,8 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
     return win32_error("CreatePipe", NULL);
 
   fSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdoutRd,
-			     GetCurrentProcess(), &hChildStdoutRdDup, 0,
-			     FALSE, DUPLICATE_SAME_ACCESS);
+                             GetCurrentProcess(), &hChildStdoutRdDup, 0,
+                             FALSE, DUPLICATE_SAME_ACCESS);
   if (!fSuccess)
     return win32_error("DuplicateHandle", NULL);
 
@@ -485,147 +487,147 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
     if (!CreatePipe(&hChildStderrRd, &hChildStderrWr, &saAttr, 0))
       return win32_error("CreatePipe", NULL);
    fSuccess = DuplicateHandle(GetCurrentProcess(),
-			       hChildStderrRd,
-			       GetCurrentProcess(),
-			       &hChildStderrRdDup, 0,
-			       FALSE, DUPLICATE_SAME_ACCESS);
+                               hChildStderrRd,
+                               GetCurrentProcess(),
+                               &hChildStderrRdDup, 0,
+                               FALSE, DUPLICATE_SAME_ACCESS);
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
-	{
-	case _O_WRONLY | _O_TEXT:
-	  /* Case for writing to child Stdin in text mode. */
-	  fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
-	  //f1 = _fdopen(fd1, "w");
-	  /* We don't care about these pipes anymore,
-	     so close them. */
-	  CloseHandle(hChildStdoutRdDup);
-	  CloseHandle(hChildStderrRdDup);
-	  break;
-
-	case _O_RDONLY | _O_TEXT:
-	  /* Case for reading from child Stdout in text mode. */
-	  fd1 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
-	  //f1 = _fdopen(fd1, "r");
-	  /* We don't care about these pipes anymore,
-	     so close them. */
-	  CloseHandle(hChildStdinWrDup);
-	  CloseHandle(hChildStderrRdDup);
-	  break;
-
-	case _O_RDONLY | _O_BINARY:
-	  /* Case for readinig from child Stdout in
-	     binary mode. */
-	  fd1 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
-	  //f1 = _fdopen(fd1, "rb");
-	  /* We don't care about these pipes anymore,
-	     so close them. */
-	  CloseHandle(hChildStdinWrDup);
-	  CloseHandle(hChildStderrRdDup);
-	  break;
-
-	case _O_WRONLY | _O_BINARY:
-	  /* Case for writing to child Stdin in binary mode. */
-	  fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
-	  //f1 = _fdopen(fd1, "wb");
-	  /* We don't care about these pipes anymore,
-	     so close them. */
-	  CloseHandle(hChildStdoutRdDup);
-	  CloseHandle(hChildStderrRdDup);
-	  break;
-	}
+        {
+        case _O_WRONLY | _O_TEXT:
+          /* Case for writing to child Stdin in text mode. */
+          fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
+          //f1 = _fdopen(fd1, "w");
+          /* We don't care about these pipes anymore,
+             so close them. */
+          CloseHandle(hChildStdoutRdDup);
+          CloseHandle(hChildStderrRdDup);
+          break;
+
+        case _O_RDONLY | _O_TEXT:
+          /* Case for reading from child Stdout in text mode. */
+          fd1 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
+          //f1 = _fdopen(fd1, "r");
+          /* We don't care about these pipes anymore,
+             so close them. */
+          CloseHandle(hChildStdinWrDup);
+          CloseHandle(hChildStderrRdDup);
+          break;
+
+        case _O_RDONLY | _O_BINARY:
+          /* Case for readinig from child Stdout in
+             binary mode. */
+          fd1 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
+          //f1 = _fdopen(fd1, "rb");
+          /* We don't care about these pipes anymore,
+             so close them. */
+          CloseHandle(hChildStdinWrDup);
+          CloseHandle(hChildStderrRdDup);
+          break;
+
+        case _O_WRONLY | _O_BINARY:
+          /* Case for writing to child Stdin in binary mode. */
+          fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
+          //f1 = _fdopen(fd1, "wb");
+          /* We don't care about these pipes anymore,
+             so close them. */
+          CloseHandle(hChildStdoutRdDup);
+          CloseHandle(hChildStderrRdDup);
+          break;
+        }
       break;
-	
+        
     case POPEN_2:
     case POPEN_4: 
       if ( 1 ) 
-	{
+        {
         // Comment this out. Maybe we will need it in the future.
         // file IO access to the process might be cool.
-	//char *m1,  *m2;
-	
-	//if (mode && _O_TEXT) 
-	//  {
-	//  m1 = "r";
-	//  m2 = "w";
-	//  } 
-	//else 
-	//  {
-	//  m1 = "rb";
-	//  m2 = "wb";
-	//  }
-
-	fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
-	//f1 = _fdopen(fd1, m2);
-	fd2 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
-	//f2 = _fdopen(fd2, m1);
-
-	if (n != 4)
+        //char *m1,  *m2;
+        
+        //if (mode && _O_TEXT) 
+        //  {
+        //  m1 = "r";
+        //  m2 = "w";
+        //  } 
+        //else 
+        //  {
+        //  m1 = "rb";
+        //  m2 = "wb";
+        //  }
+
+        fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
+        //f1 = _fdopen(fd1, m2);
+        fd2 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
+        //f2 = _fdopen(fd2, m1);
+
+        if (n != 4)
           {
-	  CloseHandle(hChildStderrRdDup);
+          CloseHandle(hChildStderrRdDup);
           }
 
-	break;
-	}
-	
+        break;
+        }
+        
     case POPEN_3:
       if ( 1) 
-	{
+        {
         // Comment this out. Maybe we will need it in the future.
         // file IO access to the process might be cool.
-	//char *m1, *m2;
+        //char *m1, *m2;
       
-	//if (mode && _O_TEXT) 
-	//  {
-	//  m1 = "r";
-	//  m2 = "w";
-	//  } 
-	//else 
-	//  {
-	//  m1 = "rb";
-	//  m2 = "wb";
-	//  }
-
-
-	fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
-	//f1 = _fdopen(fd1, m2);
-	fd2 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
-	//f2 = _fdopen(fd2, m1);
-	fd3 = _open_osfhandle(TO_INTPTR(hChildStderrRdDup), mode);
-	//f3 = _fdopen(fd3, m1);	
-
-	break;
-	}
+        //if (mode && _O_TEXT) 
+        //  {
+        //  m1 = "r";
+        //  m2 = "w";
+        //  } 
+        //else 
+        //  {
+        //  m1 = "rb";
+        //  m2 = "wb";
+        //  }
+
+
+        fd1 = _open_osfhandle(TO_INTPTR(hChildStdinWrDup), mode);
+        //f1 = _fdopen(fd1, m2);
+        fd2 = _open_osfhandle(TO_INTPTR(hChildStdoutRdDup), mode);
+        //f2 = _fdopen(fd2, m1);
+        fd3 = _open_osfhandle(TO_INTPTR(hChildStderrRdDup), mode);
+        //f3 = _fdopen(fd3, m1);        
+
+        break;
+        }
     }
 
   if (n == POPEN_4) 
     {
     if (!RealPopenCreateProcess(cmdstring,
-				path,
-				this->m_ConsoleSpawn.c_str(),
-				hChildStdinRd,
-				hChildStdoutWr,
-				hChildStdoutWr,
-				&hProcess))
+                                path,
+                                this->m_ConsoleSpawn.c_str(),
+                                hChildStdinRd,
+                                hChildStdoutWr,
+                                hChildStdoutWr,
+                                &hProcess))
       return NULL;
     }
   else 
     {
     if (!RealPopenCreateProcess(cmdstring,
-				path,
-				this->m_ConsoleSpawn.c_str(),
-				hChildStdinRd,
-				hChildStdoutWr,
-				hChildStderrWr,
-				&hProcess))
+                                path,
+                                this->m_ConsoleSpawn.c_str(),
+                                hChildStdinRd,
+                                hChildStdoutWr,
+                                hChildStderrWr,
+                                &hProcess))
       return NULL;
     }
 
@@ -649,10 +651,10 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 
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
   
@@ -740,9 +742,9 @@ bool cmWin32ProcessExecution::PrivateClose(int /* timeout */)
       int len = read(this->m_pStdErr, buffer, 1023);
       buffer[len] = 0;
       if ( this->m_Verbose )
-	{
-	std::cout << buffer << std::flush;
-	}
+        {
+        std::cout << buffer << std::flush;
+        }
       output += buffer;
       have_some = true;
       }
@@ -752,9 +754,9 @@ bool cmWin32ProcessExecution::PrivateClose(int /* timeout */)
       int len = read(this->m_pStdOut, buffer, 1023);
       buffer[len] = 0;
       if ( this->m_Verbose )
-	{
-	std::cout << buffer << std::flush;
-	}
+        {
+        std::cout << buffer << std::flush;
+        }
       output += buffer;
       have_some = true;
       }