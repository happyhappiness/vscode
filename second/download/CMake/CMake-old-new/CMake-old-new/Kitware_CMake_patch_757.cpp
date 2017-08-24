@@ -88,7 +88,7 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
 	_stricmp(comshell, "command.com") != 0) 
       {
       /* NT/2000 and not using command.com. */
-      x = i + strlen(s3) + strlen(cmdstring) + 1;
+      x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1;
       s2 = (char *)_alloca(x);
       ZeroMemory(s2, x);
       sprintf(s2, "%s%s%s", s1, s3, cmdstring);
@@ -143,9 +143,9 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
 	  return FALSE;
 	  }
 	}
-      x = i + strlen(s3) + strlen(cmdstring) + 1 +
-	strlen(modulepath) + 
-	strlen(szConsoleSpawn) + 1;
+      x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1 +
+	(int)strlen(modulepath) + 
+	(int)strlen(szConsoleSpawn) + 1;
 
       s2 = (char *)_alloca(x);
       ZeroMemory(s2, x);
@@ -272,7 +272,7 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 	{
 	case _O_WRONLY | _O_TEXT:
 	  /* Case for writing to child Stdin in text mode. */
-	  fd1 = _open_osfhandle((long)hChildStdinWrDup, mode);
+	  fd1 = _open_osfhandle((intptr_t)hChildStdinWrDup, mode);
 	  f1 = _fdopen(fd1, "w");
 	  /* We don't care about these pipes anymore,
 	     so close them. */
@@ -282,7 +282,7 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 
 	case _O_RDONLY | _O_TEXT:
 	  /* Case for reading from child Stdout in text mode. */
-	  fd1 = _open_osfhandle((long)hChildStdoutRdDup, mode);
+	  fd1 = _open_osfhandle((intptr_t)hChildStdoutRdDup, mode);
 	  f1 = _fdopen(fd1, "r");
 	  /* We don't care about these pipes anymore,
 	     so close them. */
@@ -293,7 +293,7 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 	case _O_RDONLY | _O_BINARY:
 	  /* Case for readinig from child Stdout in
 	     binary mode. */
-	  fd1 = _open_osfhandle((long)hChildStdoutRdDup, mode);
+	  fd1 = _open_osfhandle((intptr_t)hChildStdoutRdDup, mode);
 	  f1 = _fdopen(fd1, "rb");
 	  /* We don't care about these pipes anymore,
 	     so close them. */
@@ -303,7 +303,7 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 
 	case _O_WRONLY | _O_BINARY:
 	  /* Case for writing to child Stdin in binary mode. */
-	  fd1 = _open_osfhandle((long)hChildStdinWrDup, mode);
+	  fd1 = _open_osfhandle((intptr_t)hChildStdinWrDup, mode);
 	  f1 = _fdopen(fd1, "wb");
 	  /* We don't care about these pipes anymore,
 	     so close them. */
@@ -331,9 +331,9 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 	  m2 = "wb";
 	  }
 
-	fd1 = _open_osfhandle((long)hChildStdinWrDup, mode);
+	fd1 = _open_osfhandle((intptr_t)hChildStdinWrDup, mode);
 	f1 = _fdopen(fd1, m2);
-	fd2 = _open_osfhandle((long)hChildStdoutRdDup, mode);
+	fd2 = _open_osfhandle((intptr_t)hChildStdoutRdDup, mode);
 	f2 = _fdopen(fd2, m1);
 
 	if (n != 4)
@@ -359,11 +359,11 @@ bool cmWin32ProcessExecution::PrivateOpen(const char *cmdstring,
 	  m2 = "wb";
 	  }
 
-	fd1 = _open_osfhandle((long)hChildStdinWrDup, mode);
+	fd1 = _open_osfhandle((intptr_t)hChildStdinWrDup, mode);
 	f1 = _fdopen(fd1, m2);
-	fd2 = _open_osfhandle((long)hChildStdoutRdDup, mode);
+	fd2 = _open_osfhandle((intptr_t)hChildStdoutRdDup, mode);
 	f2 = _fdopen(fd2, m1);
-	fd3 = _open_osfhandle((long)hChildStderrRdDup, mode);
+	fd3 = _open_osfhandle((intptr_t)hChildStderrRdDup, mode);
 	f3 = _fdopen(fd3, m1);	
 
 	file_count = 3;