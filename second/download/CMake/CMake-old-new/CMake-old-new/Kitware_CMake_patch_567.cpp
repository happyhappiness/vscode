@@ -32,7 +32,7 @@
 
 int runChild(const char* cmd[], int state, int exception, int value,
              int share, int output, int delay, double timeout, int poll,
-             int repeat);
+             int repeat, int disown);
 
 int test1(int argc, const char* argv[])
 {
@@ -84,33 +84,21 @@ int test4(int argc, const char* argv[])
   return 0;
 }
 
-/* Quick hack to test grandchild killing.  */
-/*#define TEST5_GRANDCHILD_KILL*/
-#ifdef TEST5_GRANDCHILD_KILL
-# define TEST5_TIMEOUT 10
-#else
-# define TEST5_TIMEOUT 30
-#endif
-
 int test5(int argc, const char* argv[])
 {
   int r;
   const char* cmd[4];
   (void)argc;
   cmd[0] = argv[0];
   cmd[1] = "run";
-#ifdef TEST5_GRANDCHILD_KILL
-  cmd[2] = "3";
-#else
   cmd[2] = "4";
-#endif
   cmd[3] = 0;
   fprintf(stdout, "Output on stdout before recursive test.\n");
   fprintf(stderr, "Output on stderr before recursive test.\n");
   fflush(stdout);
   fflush(stderr);
   r = runChild(cmd, kwsysProcess_State_Exception,
-               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15, 0, 1);
+               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15, 0, 1, 0);
   fprintf(stdout, "Output on stdout after recursive test.\n");
   fprintf(stderr, "Output on stderr after recursive test.\n");
   fflush(stdout);
@@ -163,10 +151,56 @@ int test7(int argc, const char* argv[])
   return 0;
 }
 
+int test8(int argc, const char* argv[])
+{
+  /* Create a disowned grandchild to test handling of processes
+     that exit before their children.  */
+  int r;
+  const char* cmd[4];
+  (void)argc;
+  cmd[0] = argv[0];
+  cmd[1] = "run";
+  cmd[2] = "108";
+  cmd[3] = 0;
+  fprintf(stdout, "Output on stdout before grandchild test.\n");
+  fprintf(stderr, "Output on stderr before grandchild test.\n");
+  fflush(stdout);
+  fflush(stderr);
+  r = runChild(cmd, kwsysProcess_State_Disowned, kwsysProcess_Exception_None,
+               1, 1, 1, 0, 10, 0, 1, 1);
+  fprintf(stdout, "Output on stdout after grandchild test.\n");
+  fprintf(stderr, "Output on stderr after grandchild test.\n");
+  fflush(stdout);
+  fflush(stderr);
+  return r;
+}
+
+int test8_grandchild(int argc, const char* argv[])
+{
+  (void)argc; (void)argv;
+  fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
+  fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
+  fflush(stdout);
+  fflush(stderr);
+  /* TODO: Instead of closing pipes here leave them open to make sure
+     the grandparent can stop listening when the parent exits.  This
+     part of the test cannot be enabled until the feature is
+     implemented.  */
+  fclose(stdout);
+  fclose(stderr);
+#if defined(_WIN32)
+  Sleep(15000);
+#else
+  sleep(15);
+#endif
+  return 0;
+}
+
+
 int runChild2(kwsysProcess* kp,
               const char* cmd[], int state, int exception, int value,
               int share, int output, int delay, double timeout,
-              int poll)
+              int poll, int disown)
 {
   int result = 0;
   char* data = 0;
@@ -183,14 +217,18 @@ int runChild2(kwsysProcess* kp,
     kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDOUT, 1);
     kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDERR, 1);
     }
+  if(disown)
+    {
+    kwsysProcess_SetOption(kp, kwsysProcess_Option_Detach, 1);
+    }
   kwsysProcess_Execute(kp);
 
   if(poll)
     {
     pUserTimeout = &userTimeout;
     }
 
-  if(!share)
+  if(!share && !disown)
     {
     int p;
     while((p = kwsysProcess_WaitForData(kp, &data, &length, pUserTimeout)))
@@ -235,8 +273,15 @@ int runChild2(kwsysProcess* kp,
         }
       }
     }
-  
-  kwsysProcess_WaitForExit(kp, 0);
+
+  if(disown)
+    {
+    kwsysProcess_Disown(kp);
+    }
+  else
+    {
+    kwsysProcess_WaitForExit(kp, 0);
+    }
 
   switch (kwsysProcess_GetState(kp))
     {
@@ -258,6 +303,8 @@ int runChild2(kwsysProcess* kp,
              kwsysProcess_GetExceptionString(kp));
       result = ((exception != kwsysProcess_GetExitException(kp)) ||
                 (value != kwsysProcess_GetExitValue(kp))); break;
+    case kwsysProcess_State_Disowned:
+      printf("Child was disowned.\n"); break;
     case kwsysProcess_State_Error:
       printf("Error in administrating child process: [%s]\n",
              kwsysProcess_GetErrorString(kp)); break;
@@ -301,7 +348,7 @@ int runChild2(kwsysProcess* kp,
 
 int runChild(const char* cmd[], int state, int exception, int value,
              int share, int output, int delay, double timeout,
-             int poll, int repeat)
+             int poll, int repeat, int disown)
 {
   int result = 1;
   kwsysProcess* kp = kwsysProcess_New();
@@ -313,7 +360,7 @@ int runChild(const char* cmd[], int state, int exception, int value,
   while(repeat-- > 0)
     {
     result = runChild2(kp, cmd, state, exception, value, share,
-                       output, delay, timeout, poll);
+                       output, delay, timeout, poll, disown);
     }
   kwsysProcess_Delete(kp);
   return result;
@@ -347,7 +394,7 @@ int main(int argc, const char* argv[])
     n = atoi(argv[2]);
     }
   /* Check arguments.  */
-  if(n >= 1 && n <= 7 && argc == 3)
+  if(((n >= 1 && n <= 8) || n == 108) && argc == 3)
     {
     /* This is the child process for a requested test number.  */
     switch (n)
@@ -359,39 +406,43 @@ int main(int argc, const char* argv[])
       case 5: return test5(argc, argv);
       case 6: test6(argc, argv); return 0;
       case 7: return test7(argc, argv);
+      case 8: return test8(argc, argv);
+      case 108: return test8_grandchild(argc, argv);
       }
     fprintf(stderr, "Invalid test number %d.\n", n);
     return 1;
     }
-  else if(n >= 1 && n <= 7)
+  else if(n >= 1 && n <= 8)
     {
     /* This is the parent process for a requested test number.  */
-    int states[7] =
+    int states[8] =
     {
       kwsysProcess_State_Exited,
       kwsysProcess_State_Exited,
       kwsysProcess_State_Expired,
       kwsysProcess_State_Exception,
       kwsysProcess_State_Exited,
       kwsysProcess_State_Expired,
+      kwsysProcess_State_Exited,
       kwsysProcess_State_Exited
     };
-    int exceptions[7] =
+    int exceptions[8] =
     {
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_Fault,
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_None,
+      kwsysProcess_Exception_None,
       kwsysProcess_Exception_None
     };
-    int values[7] = {0, 123, 1, 1, 0, 0, 0};
-    int outputs[7] = {1, 1, 1, 1, 1, 0, 1};
-    int delays[7] = {0, 0, 0, 0, 0, 1, 0};
-    double timeouts[7] = {10, 10, 10, 10, TEST5_TIMEOUT, 10, -1};
-    int polls[7] = {0, 0, 0, 0, 0, 0, 1};
-    int repeat[7] = {2, 1, 1, 1, 1, 1, 1};
+    int values[8] = {0, 123, 1, 1, 0, 0, 0, 0};
+    int outputs[8] = {1, 1, 1, 1, 1, 0, 1, 1};
+    int delays[8] = {0, 0, 0, 0, 0, 1, 0, 0};
+    double timeouts[8] = {10, 10, 10, 10, 30, 10, -1, 10};
+    int polls[8] = {0, 0, 0, 0, 0, 0, 1, 0};
+    int repeat[8] = {2, 1, 1, 1, 1, 1, 1, 1};
     int r;
     const char* cmd[4];
 #ifdef _WIN32
@@ -425,7 +476,7 @@ int main(int argc, const char* argv[])
     fflush(stderr);
     r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], 0,
                  outputs[n-1], delays[n-1], timeouts[n-1],
-                 polls[n-1], repeat[n-1]);
+                 polls[n-1], repeat[n-1], 0);
     fprintf(stdout, "Output on stdout after test %d.\n", n);
     fprintf(stderr, "Output on stderr after test %d.\n", n);
     fflush(stdout);
@@ -444,7 +495,7 @@ int main(int argc, const char* argv[])
     int exception = kwsysProcess_Exception_None;
     int value = 0;
     double timeout = 0;
-    int r = runChild(cmd, state, exception, value, 0, 1, 0, timeout, 0, 1);
+    int r = runChild(cmd, state, exception, value, 0, 1, 0, timeout, 0, 1, 0);
     return r;
     }
   else