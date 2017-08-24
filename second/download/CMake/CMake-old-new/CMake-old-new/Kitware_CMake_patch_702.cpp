@@ -38,7 +38,6 @@ Q190351 and Q150956.
 #include <windows.h> /* Windows API */
 #include <string.h>  /* strlen, strdup */
 #include <stdio.h>   /* sprintf */
-#include <process.h> /* _getpid */
 #include <io.h>      /* _unlink */
 
 /* The number of pipes for the child's output.  The standard stdout
@@ -234,7 +233,7 @@ kwsysProcess* kwsysProcess_New()
     
     /* Construct the executable name from the process id and kwsysProcess
        instance.  This should be unique.  */
-    sprintf(fwdName, "cmw9xfwd_%u_%p.exe", _getpid(), cp);
+    sprintf(fwdName, "cmw9xfwd_%u_%p.exe", GetCurrentProcessId(), cp);
     
     /* If the environment variable "TEMP" gave us a directory, use it.  */
     if(length > 0 && length <= _MAX_PATH)
@@ -344,8 +343,10 @@ kwsysProcess* kwsysProcess_New()
       return 0;
       }
     
-    /* Create the thread.  It will block immediately.  */
-    if(!(cp->Pipe[i].Thread = CreateThread(0, 0, kwsysProcessPipeThread,
+    /* Create the thread.  It will block immediately.  The thread will
+       not make deeply nested calls, so we need only a small
+       stack.  */
+    if(!(cp->Pipe[i].Thread = CreateThread(0, 1024, kwsysProcessPipeThread,
                                            &cp->Pipe[i], 0, &dummy)))
       {
       kwsysProcess_Delete(cp);