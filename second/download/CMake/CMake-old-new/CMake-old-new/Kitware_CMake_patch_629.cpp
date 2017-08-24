@@ -187,6 +187,9 @@ struct kwsysProcess_s
   char* PipeFileSTDOUT;
   char* PipeFileSTDERR;
 
+  /* Handle to automatically delete the Win9x forwarding executable.  */
+  HANDLE Win9xHandle;
+
   /* ------------- Data managed per call to Execute ------------- */
 
   /* The exceptional behavior that terminated the process, if any.  */
@@ -286,7 +289,8 @@ kwsysProcess* kwsysProcess_New()
 
     /* Construct the executable name from the process id and kwsysProcess
        instance.  This should be unique.  */
-    sprintf(fwdName, "cmw9xfwd_%u_%p.exe", GetCurrentProcessId(), cp);
+    sprintf(fwdName, KWSYS_NAMESPACE_STRING "pew9xfwd_%u_%p.exe",
+            GetCurrentProcessId(), cp);
 
     /* If we have a temp directory, use it.  */
     if(length > 0 && length <= _MAX_PATH)
@@ -315,6 +319,19 @@ kwsysProcess* kwsysProcess_New()
         kwsysProcess_Delete(cp);
         return 0;
         }
+
+      /* Get a handle to the file that will delete it when closed.  */
+      cp->Win9xHandle = CreateFile(win9x, GENERIC_READ, FILE_SHARE_READ, 0,
+                                   OPEN_EXISTING, FILE_FLAG_DELETE_ON_CLOSE, 0);
+      if(cp->Win9xHandle == INVALID_HANDLE_VALUE)
+        {
+        /* We were not able to get a read handle for the forwarding
+           executable.  It will not be deleted properly.  Give up.  */
+        _unlink(win9x);
+        free(win9x);
+        kwsysProcess_Delete(cp);
+        return 0;
+        }
       }
     else
       {
@@ -475,8 +492,9 @@ void kwsysProcess_Delete(kwsysProcess* cp)
     }
   if(cp->Win9x)
     {
-    _unlink(cp->Win9x);
-    free(cp->Win9x);
+    /* Close or handle to the forwarding executable file.  This will
+       cause it to be deleted.  */
+    kwsysProcessCleanupHandle(&cp->Win9xHandle);
     }
   free(cp);
 }