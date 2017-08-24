@@ -247,25 +247,19 @@ kwsysProcess* kwsysProcess_New()
     char tempDir[_MAX_PATH+1] = "";
     
     /* We will try putting the executable in the system temp
-       directory.  */
-    DWORD length = GetEnvironmentVariable("TEMP", tempDir, _MAX_PATH);
+       directory.  Note that the returned path already has a trailing
+       slash.  */
+    DWORD length = GetTempPath(_MAX_PATH+1, tempDir);
     
     /* Construct the executable name from the process id and kwsysProcess
        instance.  This should be unique.  */
     sprintf(fwdName, "cmw9xfwd_%u_%p.exe", GetCurrentProcessId(), cp);
     
-    /* If the environment variable "TEMP" gave us a directory, use it.  */
+    /* If we have a temp directory, use it.  */
     if(length > 0 && length <= _MAX_PATH)
       {
-      /* Make sure there is no trailing slash.  */
-      size_t tdlen = strlen(tempDir);
-      if(tempDir[tdlen-1] == '/' || tempDir[tdlen-1] == '\\')
-        {
-        tempDir[tdlen-1] = 0;
-        --tdlen;
-        }
-      
       /* Allocate a buffer to hold the forwarding executable path.  */
+      size_t tdlen = strlen(tempDir);
       win9x = (char*)malloc(tdlen + strlen(fwdName) + 2);
       if(!win9x)
         {
@@ -274,7 +268,7 @@ kwsysProcess* kwsysProcess_New()
         }
       
       /* Construct the full path to the forwarding executable.  */
-      sprintf(win9x, "%s/%s", tempDir, fwdName);
+      sprintf(win9x, "%s%s", tempDir, fwdName);
       }
     
     /* If we found a place to put the forwarding executable, try to