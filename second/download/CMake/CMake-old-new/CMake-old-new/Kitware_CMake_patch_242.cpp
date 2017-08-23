@@ -29,26 +29,48 @@
 # include <windows.h>
 #else
 # include <unistd.h>
+# include <signal.h>
 #endif
 
 #if defined(__BORLANDC__)
 # pragma warn -8060 /* possibly incorrect assignment */
 #endif
 
+/* Platform-specific sleep functions. */
+
 #if defined(__BEOS__) && !defined(__ZETA__)
 /* BeOS 5 doesn't have usleep(), but it has snooze(), which is identical. */
 # include <be/kernel/OS.h>
-static inline void testProcess_usleep(unsigned int msec)
+static inline void testProcess_usleep(unsigned int usec)
+{
+  snooze(usec);
+}
+#elif defined(_WIN32)
+/* Windows can only sleep in millisecond intervals. */
+static void testProcess_usleep(unsigned int usec)
 {
-  snooze(msec);
+  Sleep(usec / 1000);
 }
 #else
 # define testProcess_usleep usleep
 #endif
 
+#if defined(_WIN32)
+static void testProcess_sleep(unsigned int sec)
+{
+  Sleep(sec*1000);
+}
+#else
+static void testProcess_sleep(unsigned int sec)
+{
+  sleep(sec);
+}
+#endif
+
 int runChild(const char* cmd[], int state, int exception, int value,
              int share, int output, int delay, double timeout, int poll,
-             int repeat, int disown);
+             int repeat, int disown, int createNewGroup,
+             unsigned int interruptDelay);
 
 static int test1(int argc, const char* argv[])
 {
@@ -73,11 +95,7 @@ static int test3(int argc, const char* argv[])
   fprintf(stderr, "Output before sleep on stderr from timeout test.\n");
   fflush(stdout);
   fflush(stderr);
-#if defined(_WIN32)
-  Sleep(15000);
-#else
-  sleep(15);
-#endif
+  testProcess_sleep(15);
   fprintf(stdout, "Output after sleep on stdout from timeout test.\n");
   fprintf(stderr, "Output after sleep on stderr from timeout test.\n");
   return 0;
@@ -102,7 +120,7 @@ static int test4(int argc, const char* argv[])
 #endif
   (void)argc; (void)argv;
   fprintf(stdout, "Output before crash on stdout from crash test.\n");
-  fprintf(stderr, "Output before crash on stderr from crash test.\n");  
+  fprintf(stderr, "Output before crash on stderr from crash test.\n");
   fflush(stdout);
   fflush(stderr);
   assert(invalidAddress); /* Quiet Clang scan-build. */
@@ -127,7 +145,7 @@ static int test5(int argc, const char* argv[])
   fflush(stdout);
   fflush(stderr);
   r = runChild(cmd, kwsysProcess_State_Exception,
-               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15, 0, 1, 0);
+               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15, 0, 1, 0, 0, 0);
   fprintf(stdout, "Output on stdout after recursive test.\n");
   fprintf(stderr, "Output on stderr after recursive test.\n");
   fflush(stdout);
@@ -168,11 +186,7 @@ static int test7(int argc, const char* argv[])
   fflush(stdout);
   fflush(stderr);
   /* Sleep for 1 second.  */
-#if defined(_WIN32)
-  Sleep(1000);
-#else
-  sleep(1);
-#endif
+  testProcess_sleep(1);
   fprintf(stdout, "Output on stdout after sleep.\n");
   fprintf(stderr, "Output on stderr after sleep.\n");
   fflush(stdout);
@@ -196,7 +210,7 @@ static int test8(int argc, const char* argv[])
   fflush(stdout);
   fflush(stderr);
   r = runChild(cmd, kwsysProcess_State_Disowned, kwsysProcess_Exception_None,
-               1, 1, 1, 0, 10, 0, 1, 1);
+               1, 1, 1, 0, 10, 0, 1, 1, 0, 0);
   fprintf(stdout, "Output on stdout after grandchild test.\n");
   fprintf(stderr, "Output on stderr after grandchild test.\n");
   fflush(stdout);
@@ -217,18 +231,137 @@ static int test8_grandchild(int argc, const char* argv[])
      implemented.  */
   fclose(stdout);
   fclose(stderr);
+  testProcess_sleep(15);
+  return 0;
+}
+
+static int test9(int argc, const char* argv[])
+{
+  /* Test Ctrl+C behavior: the root test program will send a Ctrl+C to this
+     process.  Here, we start a child process that sleeps for a long time
+     while ignoring signals.  The test is successful if this process waits
+     for the child to return before exiting from the Ctrl+C handler.
+
+     WARNING:  This test will falsely pass if the share parameter of runChild
+     was set to 0 when invoking the test9 process.  */
+  int r;
+  const char* cmd[4];
+  (void)argc;
+  cmd[0] = argv[0];
+  cmd[1] = "run";
+  cmd[2] = "109";
+  cmd[3] = 0;
+  fprintf(stdout, "Output on stdout before grandchild test.\n");
+  fprintf(stderr, "Output on stderr before grandchild test.\n");
+  fflush(stdout);
+  fflush(stderr);
+  r = runChild(cmd, kwsysProcess_State_Exited,
+               kwsysProcess_Exception_None,
+               0, 1, 1, 0, 30, 0, 1, 0, 0, 0);
+  /* This sleep will avoid a race condition between this function exiting
+     normally and our Ctrl+C handler exiting abnormally after the process
+     exits.  */
+  testProcess_sleep(1);
+  fprintf(stdout, "Output on stdout after grandchild test.\n");
+  fprintf(stderr, "Output on stderr after grandchild test.\n");
+  fflush(stdout);
+  fflush(stderr);
+  return r;
+}
+
 #if defined(_WIN32)
-  Sleep(15000);
+static BOOL WINAPI test9_grandchild_handler(DWORD dwCtrlType)
+{
+  /* Ignore all Ctrl+C/Break signals.  We must use an actual handler function
+     instead of using SetConsoleCtrlHandler(NULL, TRUE) so that we can also
+     ignore Ctrl+Break in addition to Ctrl+C.  */
+  (void)dwCtrlType;
+  return TRUE;
+}
+#endif
+
+static int test9_grandchild(int argc, const char* argv[])
+{
+  /* The grandchild just sleeps for a few seconds while ignoring signals.  */
+  (void)argc; (void)argv;
+#if defined(_WIN32)
+  if(!SetConsoleCtrlHandler(test9_grandchild_handler, TRUE))
+    {
+    return 1;
+    }
 #else
-  sleep(15);
+  struct sigaction sa;
+  memset(&sa, 0, sizeof(sa));
+  sa.sa_handler = SIG_IGN;
+  sigemptyset(&sa.sa_mask);
+  if(sigaction(SIGINT, &sa, 0) < 0)
+    {
+    return 1;
+    }
 #endif
+  fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
+  fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
+  fflush(stdout);
+  fflush(stderr);
+  /* Sleep for 9 seconds.  */
+  testProcess_sleep(9);
+  fprintf(stdout, "Output on stdout from grandchild after sleep.\n");
+  fprintf(stderr, "Output on stderr from grandchild after sleep.\n");
+  fflush(stdout);
+  fflush(stderr);
+  return 0;
+}
+
+static int test10(int argc, const char* argv[])
+{
+  /* Test Ctrl+C behavior: the root test program will send a Ctrl+C to this
+     process.  Here, we start a child process that sleeps for a long time and
+     processes signals normally.  However, this grandchild is created in a new
+     process group - ensuring that Ctrl+C we receive is sent to our process
+     groups.  We make sure it exits anyway.  */
+  int r;
+  const char* cmd[4];
+  (void)argc;
+  cmd[0] = argv[0];
+  cmd[1] = "run";
+  cmd[2] = "110";
+  cmd[3] = 0;
+  fprintf(stdout, "Output on stdout before grandchild test.\n");
+  fprintf(stderr, "Output on stderr before grandchild test.\n");
+  fflush(stdout);
+  fflush(stderr);
+  r = runChild(cmd, kwsysProcess_State_Exception,
+               kwsysProcess_Exception_Interrupt,
+               0, 1, 1, 0, 30, 0, 1, 0, 1, 0);
+  fprintf(stdout, "Output on stdout after grandchild test.\n");
+  fprintf(stderr, "Output on stderr after grandchild test.\n");
+  fflush(stdout);
+  fflush(stderr);
+  return r;
+}
+
+static int test10_grandchild(int argc, const char* argv[])
+{
+  /* The grandchild just sleeps for a few seconds and handles signals.  */
+  (void)argc; (void)argv;
+  fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
+  fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
+  fflush(stdout);
+  fflush(stderr);
+  /* Sleep for 6 seconds.  */
+  testProcess_sleep(6);
+  fprintf(stdout, "Output on stdout from grandchild after sleep.\n");
+  fprintf(stderr, "Output on stderr from grandchild after sleep.\n");
+  fflush(stdout);
+  fflush(stderr);
   return 0;
 }
 
 static int runChild2(kwsysProcess* kp,
               const char* cmd[], int state, int exception, int value,
               int share, int output, int delay, double timeout,
-              int poll, int disown)
+              int poll, int disown, int createNewGroup,
+              unsigned int interruptDelay)
 {
   int result = 0;
   char* data = 0;
@@ -249,13 +382,23 @@ static int runChild2(kwsysProcess* kp,
     {
     kwsysProcess_SetOption(kp, kwsysProcess_Option_Detach, 1);
     }
+  if(createNewGroup)
+    {
+    kwsysProcess_SetOption(kp, kwsysProcess_Option_CreateProcessGroup, 1);
+    }
   kwsysProcess_Execute(kp);
 
   if(poll)
     {
     pUserTimeout = &userTimeout;
     }
 
+  if(interruptDelay)
+    {
+    testProcess_sleep(interruptDelay);
+    kwsysProcess_Interrupt(kp);
+    }
+
   if(!share && !disown)
     {
     int p;
@@ -286,17 +429,13 @@ static int runChild2(kwsysProcess* kp,
       if(poll)
         {
         /* Delay to avoid busy loop during polling.  */
-#if defined(_WIN32)
-        Sleep(100);
-#else
         testProcess_usleep(100000);
-#endif
         }
       if(delay)
         {
         /* Purposely sleeping only on Win32 to let pipe fill up.  */
 #if defined(_WIN32)
-        Sleep(100);
+        testProcess_usleep(100000);
 #endif
         }
       }
@@ -337,7 +476,7 @@ static int runChild2(kwsysProcess* kp,
       printf("Error in administrating child process: [%s]\n",
              kwsysProcess_GetErrorString(kp)); break;
     };
-  
+
   if(result)
     {
     if(exception != kwsysProcess_GetExitException(kp))
@@ -353,7 +492,7 @@ static int runChild2(kwsysProcess* kp,
               value, kwsysProcess_GetExitValue(kp));
       }
     }
-  
+
   if(kwsysProcess_GetState(kp) != state)
     {
     fprintf(stderr, "Mismatch in state.  "
@@ -374,9 +513,37 @@ static int runChild2(kwsysProcess* kp,
   return result;
 }
 
+/**
+ * Runs a child process and blocks until it returns.  Arguments as follows:
+ *
+ * cmd            = Command line to run.
+ * state          = Expected return value of kwsysProcess_GetState after exit.
+ * exception      = Expected return value of kwsysProcess_GetExitException.
+ * value          = Expected return value of kwsysProcess_GetExitValue.
+ * share          = Whether to share stdout/stderr child pipes with our pipes
+ *                  by way of kwsysProcess_SetPipeShared.  If false, new pipes
+ *                  are created.
+ * output         = If !share && !disown, whether to write the child's stdout
+ *                  and stderr output to our stdout.
+ * delay          = If !share && !disown, adds an additional short delay to
+ *                  the pipe loop to allow the pipes to fill up; Windows only.
+ * timeout        = Non-zero to sets a timeout in seconds via
+ *                  kwsysProcess_SetTimeout.
+ * poll           = If !share && !disown, we count the number of 0.1 second
+ *                  intervals where the child pipes had no new data.  We fail
+ *                  if not in the bounds of MINPOLL/MAXPOLL.
+ * repeat         = Number of times to run the process.
+ * disown         = If set, the process is disowned.
+ * createNewGroup = If set, the process is created in a new process group.
+ * interruptDelay = If non-zero, number of seconds to delay before
+ *                  interrupting the process.  Note that this delay will occur
+ *                  BEFORE any reading/polling of pipes occurs and before any
+ *                  detachment occurs.
+ */
 int runChild(const char* cmd[], int state, int exception, int value,
              int share, int output, int delay, double timeout,
-             int poll, int repeat, int disown)
+             int poll, int repeat, int disown, int createNewGroup,
+             unsigned int interruptDelay)
 {
   int result = 1;
   kwsysProcess* kp = kwsysProcess_New();
@@ -388,7 +555,8 @@ int runChild(const char* cmd[], int state, int exception, int value,
   while(repeat-- > 0)
     {
     result = runChild2(kp, cmd, state, exception, value, share,
-                       output, delay, timeout, poll, disown);
+                       output, delay, timeout, poll, disown, createNewGroup,
+                       interruptDelay);
     }
   kwsysProcess_Delete(kp);
   return result;
@@ -435,7 +603,7 @@ int main(int argc, const char* argv[])
     n = atoi(argv[2]);
     }
   /* Check arguments.  */
-  if(((n >= 1 && n <= 8) || n == 108) && argc == 3)
+  if(((n >= 1 && n <= 10) || n == 108 || n == 109 || n == 110) && argc == 3)
     {
     /* This is the child process for a requested test number.  */
     switch (n)
@@ -448,15 +616,19 @@ int main(int argc, const char* argv[])
       case 6: test6(argc, argv); return 0;
       case 7: return test7(argc, argv);
       case 8: return test8(argc, argv);
+      case 9: return test9(argc, argv);
+      case 10: return test10(argc, argv);
       case 108: return test8_grandchild(argc, argv);
+      case 109: return test9_grandchild(argc, argv);
+      case 110: return test10_grandchild(argc, argv);
       }
     fprintf(stderr, "Invalid test number %d.\n", n);
     return 1;
     }
-  else if(n >= 1 && n <= 8)
+  else if(n >= 1 && n <= 10)
     {
     /* This is the parent process for a requested test number.  */
-    int states[8] =
+    int states[10] =
     {
       kwsysProcess_State_Exited,
       kwsysProcess_State_Exited,
@@ -465,9 +637,11 @@ int main(int argc, const char* argv[])
       kwsysProcess_State_Exited,
       kwsysProcess_State_Expired,
       kwsysProcess_State_Exited,
-      kwsysProcess_State_Exited
+      kwsysProcess_State_Exited,
+      kwsysProcess_State_Expired, /* Ctrl+C handler test */
+      kwsysProcess_State_Exception /* Process group test */
     };
-    int exceptions[8] =
+    int exceptions[10] =
     {
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_None,
@@ -476,14 +650,19 @@ int main(int argc, const char* argv[])
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_None,
-      kwsysProcess_Exception_None
+      kwsysProcess_Exception_None,
+      kwsysProcess_Exception_None,
+      kwsysProcess_Exception_Interrupt
     };
-    int values[8] = {0, 123, 1, 1, 0, 0, 0, 0};
-    int outputs[8] = {1, 1, 1, 1, 1, 0, 1, 1};
-    int delays[8] = {0, 0, 0, 0, 0, 1, 0, 0};
-    double timeouts[8] = {10, 10, 10, 30, 30, 10, -1, 10};
-    int polls[8] = {0, 0, 0, 0, 0, 0, 1, 0};
-    int repeat[8] = {2, 1, 1, 1, 1, 1, 1, 1};
+    int values[10] = {0, 123, 1, 1, 0, 0, 0, 0, 1, 1};
+    int shares[10] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
+    int outputs[10] = {1, 1, 1, 1, 1, 0, 1, 1, 1, 1};
+    int delays[10] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
+    double timeouts[10] = {10, 10, 10, 30, 30, 10, -1, 10, 6, 4};
+    int polls[10] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
+    int repeat[10] = {2, 1, 1, 1, 1, 1, 1, 1, 1, 1};
+    int createNewGroups[10] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
+    unsigned int interruptDelays[10] = {0, 0, 0, 0, 0, 0, 0, 0, 3, 2};
     int r;
     const char* cmd[4];
 #ifdef _WIN32
@@ -515,9 +694,10 @@ int main(int argc, const char* argv[])
     fprintf(stderr, "Output on stderr before test %d.\n", n);
     fflush(stdout);
     fflush(stderr);
-    r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], 0,
+    r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], shares[n-1],
                  outputs[n-1], delays[n-1], timeouts[n-1],
-                 polls[n-1], repeat[n-1], 0);
+                 polls[n-1], repeat[n-1], 0, createNewGroups[n-1],
+                 interruptDelays[n-1]);
     fprintf(stdout, "Output on stdout after test %d.\n", n);
     fprintf(stderr, "Output on stderr after test %d.\n", n);
     fflush(stdout);
@@ -536,7 +716,8 @@ int main(int argc, const char* argv[])
     int exception = kwsysProcess_Exception_None;
     int value = 0;
     double timeout = 0;
-    int r = runChild(cmd, state, exception, value, 0, 1, 0, timeout, 0, 1, 0);
+    int r = runChild(cmd, state, exception, value, 0, 1, 0, timeout,
+      0, 1, 0, 0, 0);
     return r;
     }
   else