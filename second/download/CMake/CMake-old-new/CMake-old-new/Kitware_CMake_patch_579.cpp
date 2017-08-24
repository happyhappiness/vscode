@@ -31,7 +31,7 @@
 #endif
 
 int runChild(const char* cmd[], int state, int exception, int value,
-             int share, int output, int delay, double timeout);
+             int share, int output, int delay, double timeout, int poll);
 
 int test1(int argc, const char* argv[])
 {
@@ -97,7 +97,7 @@ int test5(int argc, const char* argv[])
   fflush(stdout);
   fflush(stderr);
   r = runChild(cmd, kwsysProcess_State_Exception,
-               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15);
+               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15, 0);
   fprintf(stdout, "Output on stdout after recursive test.\n");
   fprintf(stderr, "Output on stderr after recursive test.\n");
   fflush(stdout);
@@ -125,13 +125,40 @@ void test6(int argc, const char* argv[])
     }
 }
 
+/* Define MINPOLL to be one more than the number of times output is
+   written.  Define MAXPOLL to be the largest number of times a loop
+   delaying 1/10th of a second should ever have to poll.  */
+#define MINPOLL 5
+#define MAXPOLL 20
+int test7(int argc, const char* argv[])
+{
+  (void)argc; (void)argv;
+  fprintf(stdout, "Output on stdout before sleep.\n");
+  fprintf(stderr, "Output on stderr before sleep.\n");
+  fflush(stdout);
+  fflush(stderr);
+  /* Sleep for 1 second.  */
+#if defined(_WIN32)
+  Sleep(1000);
+#else
+  usleep(1000000);
+#endif
+  fprintf(stdout, "Output on stdout after sleep.\n");
+  fprintf(stderr, "Output on stderr after sleep.\n");
+  fflush(stdout);
+  fflush(stderr);
+  return 0;
+}
 
 int runChild(const char* cmd[], int state, int exception, int value,
-             int share, int output, int delay, double timeout)
+             int share, int output, int delay, double timeout,
+             int poll)
 {
   int result = 0;
   char* data = 0;
   int length = 0;
+  double userTimeout = 0;
+  double* pUserTimeout = 0;
   kwsysProcess* kp = kwsysProcess_New();
   if(!kp)
     {
@@ -140,22 +167,57 @@ int runChild(const char* cmd[], int state, int exception, int value,
     }
   
   kwsysProcess_SetCommand(kp, cmd);
-  kwsysProcess_SetTimeout(kp, timeout);
+  if(timeout >= 0)
+    {
+    kwsysProcess_SetTimeout(kp, timeout);
+    }
   if(share)
     {
     kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDOUT, 1);
     kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDERR, 1);
     }
   kwsysProcess_Execute(kp);
 
+  if(poll)
+    {
+    pUserTimeout = &userTimeout;
+    }
+
   if(!share)
     {
-    while(kwsysProcess_WaitForData(kp, &data, &length, 0))
+    int p;
+    while((p = kwsysProcess_WaitForData(kp, &data, &length, pUserTimeout)))
       {
       if(output)
         {
-        fwrite(data, 1, length, stdout);
-        fflush(stdout);
+        if(poll && p == kwsysProcess_Pipe_Timeout)
+          {
+          fprintf(stdout, "WaitForData timeout reached.\n");
+          fflush(stdout);
+
+          /* Count the number of times we polled without getting data.
+             If it is excessive then kill the child and fail.  */
+          if(++poll >= MAXPOLL)
+            {
+            fprintf(stdout, "Poll count reached limit %d.\n",
+                    MAXPOLL);
+            kwsysProcess_Kill(kp);
+            }
+          }
+        else
+          {
+          fwrite(data, 1, length, stdout);
+          fflush(stdout);
+          }
+        }
+      if(poll)
+        {
+        /* Delay to avoid busy loop during polling.  */
+#if defined(_WIN32)
+        Sleep(100);
+#else
+        usleep(100000);
+#endif
         }
       if(delay)
         {
@@ -168,7 +230,7 @@ int runChild(const char* cmd[], int state, int exception, int value,
     }
   
   kwsysProcess_WaitForExit(kp, 0);
-  
+
   switch (kwsysProcess_GetState(kp))
     {
     case kwsysProcess_State_Starting:
@@ -217,6 +279,15 @@ int runChild(const char* cmd[], int state, int exception, int value,
             state, kwsysProcess_GetState(kp));
     result = 1;
     }
+
+  /* We should have polled more times than there were data if polling
+     was enabled.  */
+  if(poll && poll < MINPOLL)
+    {
+    fprintf(stderr, "Poll count is %d, which is less than %d.\n",
+            poll, MINPOLL);
+    result = 1;
+    }
   
   kwsysProcess_Delete(kp);
   return result;
@@ -250,7 +321,7 @@ int main(int argc, const char* argv[])
     n = atoi(argv[2]);
     }
   /* Check arguments.  */
-  if(n < 1 || n > 6 || (argc == 3 && strcmp(argv[1], "run") != 0))
+  if(n < 1 || n > 7 || (argc == 3 && strcmp(argv[1], "run") != 0))
     {
     fprintf(stdout, "Usage: %s <test number>\n", argv[0]);
     return 1;
@@ -265,35 +336,39 @@ int main(int argc, const char* argv[])
       case 4: return test4(argc, argv);
       case 5: return test5(argc, argv);
       case 6: test6(argc, argv); return 0;
+      case 7: return test7(argc, argv);
       }
     fprintf(stderr, "Invalid test number %d.\n", n);
     return 1;
     }
   
-  if(n >= 0 && n <= 6)
+  if(n >= 0 && n <= 7)
     {
-    int states[6] =
+    int states[7] =
     {
       kwsysProcess_State_Exited,
       kwsysProcess_State_Exited,
       kwsysProcess_State_Expired,
       kwsysProcess_State_Exception,
       kwsysProcess_State_Exited,
-      kwsysProcess_State_Expired
+      kwsysProcess_State_Expired,
+      kwsysProcess_State_Exited
     };
-    int exceptions[6] =
+    int exceptions[7] =
     {
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_Fault,
       kwsysProcess_Exception_None,
+      kwsysProcess_Exception_None,
       kwsysProcess_Exception_None
     };
-    int values[6] = {0, 123, 1, 1, 0, 0};
-    int outputs[6] = {1, 1, 1, 1, 1, 0};
-    int delays[6] = {0, 0, 0, 0, 0, 1};
-    double timeouts[6] = {10, 10, 10, 10, 30, 10};
+    int values[7] = {0, 123, 1, 1, 0, 0, 0};
+    int outputs[7] = {1, 1, 1, 1, 1, 0, 1};
+    int delays[7] = {0, 0, 0, 0, 0, 1, 0};
+    double timeouts[7] = {10, 10, 10, 10, 30, 10, -1};
+    int polls[7] = {0, 0, 0, 0, 0, 0, 1};
     int r;
     const char* cmd[4];
 #ifdef _WIN32
@@ -326,7 +401,8 @@ int main(int argc, const char* argv[])
     fflush(stdout);
     fflush(stderr);
     r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], 0,
-                 outputs[n-1], delays[n-1], timeouts[n-1]);
+                 outputs[n-1], delays[n-1], timeouts[n-1],
+                 polls[n-1]);
     fprintf(stdout, "Output on stdout after test %d.\n", n);
     fprintf(stderr, "Output on stderr after test %d.\n", n);
     fflush(stdout);