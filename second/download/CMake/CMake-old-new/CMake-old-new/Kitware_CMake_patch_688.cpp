@@ -291,16 +291,17 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
 {
   PROCESS_INFORMATION piProcInfo;
   STARTUPINFO siStartInfo;
-  char *s1,*s2, *s3 = " /c ";
+  char *s1=0,*s2=0, *s3 = " /c ";
   int i;
   int x;
   if (i = GetEnvironmentVariable("COMSPEC",NULL,0)) 
     {
     char *comshell;
 
-    s1 = (char *)_alloca(i);
+    s1 = (char *)malloc(i);
     if (!(x = GetEnvironmentVariable("COMSPEC", s1, i)))
       {
+      free(s1);
       return x;
       }
 
@@ -317,7 +318,7 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
       {
       /* NT/2000 and not using command.com. */
       x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1;
-      s2 = (char *)_alloca(x);
+      s2 = (char *)malloc(x);
       ZeroMemory(s2, x);
       //sprintf(s2, "%s%s%s", s1, s3, cmdstring);
       sprintf(s2, "%s", cmdstring);
@@ -366,15 +367,20 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
             << "Can not locate '" << modulepath
             << "' which is needed "
             "for popen to work with your shell "
-            "or platform." << std::endl;
+            "or platform." << std::endl;    
+          free(s1);
+          free(s2);
           return FALSE;
           }
         }
       x = i + (int)strlen(s3) + (int)strlen(cmdstring) + 1 +
         (int)strlen(modulepath) + 
         (int)strlen(szConsoleSpawn) + 1;
-
-      s2 = (char *)_alloca(x);
+      if(s2)
+        {
+        free(s2);
+        }
+      s2 = (char *)malloc(x);
       ZeroMemory(s2, x);
       sprintf(
         s2,
@@ -396,7 +402,9 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
   else 
     {
     std::cout << "Cannot locate a COMSPEC environment variable to "
-              << "use as the shell" << std::endl;
+              << "use as the shell" << std::endl; 
+    free(s2);
+    free(s1);
     return FALSE;
     }
   
@@ -429,11 +437,15 @@ static BOOL RealPopenCreateProcess(const char *cmdstring,
     /* Return process handle */
     *hProcess = piProcInfo.hProcess;
     //std::cout << "Process created..." << std::endl;
+    free(s2);
+    free(s1);
     return TRUE;
     }
   output += "CreateProcessError ";
   output += s2;
   output += "\n";
+  free(s2);
+  free(s1);
   return FALSE;
 }
 