@@ -70,6 +70,7 @@ static DWORD WINAPI kwsysProcessPipeThread(LPVOID ptd);
 static void kwsysProcessPipeThreadReadPipe(kwsysProcess* cp, kwsysProcessPipeData* td);
 static void kwsysProcessCleanupHandle(PHANDLE h);
 static void kwsysProcessCleanup(kwsysProcess* cp, int error);
+static void kwsysProcessCleanErrorMessage(kwsysProcess* cp);
 static int kwsysProcessGetTimeoutTime(kwsysProcess* cp, double* userTimeout,
                                       kwsysProcessTime* timeoutTime);
 static int kwsysProcessGetTimeoutLeft(kwsysProcessTime* timeoutTime,
@@ -1050,8 +1051,12 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
     }
   else if(cp->ErrorMessageLength)
     {
-    /* Failed to run the process.  */
+    /* The Win9x forwarding executing repored data on the special
+       error pipe.  Failed to run the process.  */
     cp->State = kwsysProcess_State_Error;
+    
+    /* Remove trailing period and newline from message, if any.  */
+    kwsysProcessCleanErrorMessage(cp);
     }
   else if(cp->TimeoutExpired)
     {
@@ -1111,7 +1116,7 @@ int kwsysProcess_WaitForExit(kwsysProcess* cp, double* userTimeout)
   else
     {
     /* Error getting the child return code.  */
-    strcpy(cp->ErrorMessage, "Error getting child return code.");
+    strcpy(cp->ErrorMessage, "Error getting child return code");
     cp->State = kwsysProcess_State_Error;
     }
   
@@ -1261,37 +1266,20 @@ void kwsysProcessCleanup(kwsysProcess* cp, int error)
                                  FORMAT_MESSAGE_IGNORE_INSERTS, 0, original,
                                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                  cp->ErrorMessage, CMPE_PIPE_BUFFER_SIZE, 0);
-    
-    if(length > 0)
-      {
-      /* Remove trailing period and newline, if any.  */
-      if(cp->ErrorMessage[length-1] == '\n')
-        {
-        cp->ErrorMessage[length-1] = 0;
-        --length;
-        if(length > 0 && cp->ErrorMessage[length-1] == '\r')
-          {
-          cp->ErrorMessage[length-1] = 0;
-          --length;
-          }
-        }
-      if(cp->ErrorMessage[length-1] == '.')
-        {
-        cp->ErrorMessage[length-1] = 0;
-        --length;
-        }
-      }
-    else
+    if(length < 1)
       {
       /* FormatMessage failed.  Use a default message.  */
       _snprintf(cp->ErrorMessage, CMPE_PIPE_BUFFER_SIZE,
                 "Process execution failed with error 0x%X.  "
-                "FormatMessage failed with error 0x%X.",
+                "FormatMessage failed with error 0x%X",
                 original, GetLastError());
       }
-    
+
     /* Set the error state.  */
     cp->State = kwsysProcess_State_Error;
+
+    /* Remove trailing period and newline, if any.  */
+    kwsysProcessCleanErrorMessage(cp);    
     }
   
   /* Free memory.  */
@@ -1310,6 +1298,28 @@ void kwsysProcessCleanup(kwsysProcess* cp, int error)
 }
 
 /*--------------------------------------------------------------------------*/
+void kwsysProcessCleanErrorMessage(kwsysProcess* cp)
+{
+  /* Remove trailing period and newline, if any.  */
+  int length = strlen(cp->ErrorMessage);
+  if(cp->ErrorMessage[length-1] == '\n')
+    {
+    cp->ErrorMessage[length-1] = 0;
+    --length;
+    if(length > 0 && cp->ErrorMessage[length-1] == '\r')
+      {
+      cp->ErrorMessage[length-1] = 0;
+      --length;
+      }
+    }
+  if(length > 0 && cp->ErrorMessage[length-1] == '.')
+    {
+    cp->ErrorMessage[length-1] = 0;
+    --length;
+    }
+}
+
+/*--------------------------------------------------------------------------*/
 /* Get the time at which either the process or user timeout will
    expire.  Returns 1 if the user timeout is first, and 0 otherwise.  */
 int kwsysProcessGetTimeoutTime(kwsysProcess* cp, double* userTimeout,