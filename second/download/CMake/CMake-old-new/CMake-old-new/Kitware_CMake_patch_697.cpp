@@ -526,8 +526,7 @@ int kwsysProcess_WaitForData(kwsysProcess* cp, int pipes, char** data, int* leng
       {
       /* Select returned an error.  Leave the error description in the
          pipe buffer.  */
-      snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE,
-               "%s", strerror(errno));
+      strncpy(cp->ErrorMessage, strerror(errno), KWSYSPE_PIPE_BUFFER_SIZE);
       
       /* Kill the child now.  */
       kwsysProcess_Kill(cp);
@@ -730,7 +729,7 @@ static void kwsysProcessCleanup(kwsysProcess* cp, int error)
   /* If cleaning up due to an error, report the error message.  */
   if(error)
     {
-    snprintf(cp->ErrorMessage, KWSYSPE_PIPE_BUFFER_SIZE, "%s", strerror(errno));
+    strncpy(cp->ErrorMessage, strerror(errno), KWSYSPE_PIPE_BUFFER_SIZE);
     cp->State = kwsysProcess_State_Error;
     }
   
@@ -887,7 +886,7 @@ static void kwsysProcessChildErrorExit(kwsysProcess* cp)
 {
   /* Construct the error message.  */
   char buffer[KWSYSPE_PIPE_BUFFER_SIZE];
-  snprintf(buffer, KWSYSPE_PIPE_BUFFER_SIZE, "%s", strerror(errno));
+  strncpy(buffer, strerror(errno), KWSYSPE_PIPE_BUFFER_SIZE);
   
   /* Report the error to the parent through the special pipe.  */
   write(cp->PipeWriteEnds[KWSYSPE_PIPE_ERROR], buffer, strlen(buffer));