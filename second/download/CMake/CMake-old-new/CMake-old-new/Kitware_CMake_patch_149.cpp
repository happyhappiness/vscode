@@ -1,23 +1,14 @@
-/*============================================================================
-  KWSys - Kitware System Library
-  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium
-
-  Distributed under the OSI-approved BSD License (the "License");
-  see accompanying file Copyright.txt for details.
-
-  This software is distributed WITHOUT ANY WARRANTY; without even the
-  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
-  See the License for more information.
-============================================================================*/
+/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
+   file Copyright.txt or https://cmake.org/licensing#kwsys for details.  */
 #include "kwsysPrivate.h"
 #include KWSYS_HEADER(Process.h)
 #include KWSYS_HEADER(Encoding.h)
 
 /* Work-around CMake dependency scanning limitation.  This must
    duplicate the above list of headers.  */
 #if 0
-# include "Process.h.in"
-# include "Encoding.h.in"
+#include "Encoding.h.in"
+#include "Process.h.in"
 #endif
 
 #include <assert.h>
@@ -27,21 +18,21 @@
 #include <string.h>
 
 #if defined(_WIN32)
-# include <windows.h>
+#include <windows.h>
 #else
-# include <unistd.h>
-# include <signal.h>
+#include <signal.h>
+#include <unistd.h>
 #endif
 
 #if defined(__BORLANDC__)
-# pragma warn -8060 /* possibly incorrect assignment */
+#pragma warn - 8060 /* possibly incorrect assignment */
 #endif
 
 /* Platform-specific sleep functions. */
 
 #if defined(__BEOS__) && !defined(__ZETA__)
 /* BeOS 5 doesn't have usleep(), but it has snooze(), which is identical. */
-# include <be/kernel/OS.h>
+#include <be/kernel/OS.h>
 static inline void testProcess_usleep(unsigned int usec)
 {
   snooze(usec);
@@ -53,13 +44,13 @@ static void testProcess_usleep(unsigned int usec)
   Sleep(usec / 1000);
 }
 #else
-# define testProcess_usleep usleep
+#define testProcess_usleep usleep
 #endif
 
 #if defined(_WIN32)
 static void testProcess_sleep(unsigned int sec)
 {
-  Sleep(sec*1000);
+  Sleep(sec * 1000);
 }
 #else
 static void testProcess_sleep(unsigned int sec)
@@ -68,10 +59,9 @@ static void testProcess_sleep(unsigned int sec)
 }
 #endif
 
-int runChild(const char* cmd[], int state, int exception, int value,
-             int share, int output, int delay, double timeout, int poll,
-             int repeat, int disown, int createNewGroup,
-             unsigned int interruptDelay);
+int runChild(const char* cmd[], int state, int exception, int value, int share,
+             int output, int delay, double timeout, int poll, int repeat,
+             int disown, int createNewGroup, unsigned int interruptDelay);
 
 static int test1(int argc, const char* argv[])
 {
@@ -85,23 +75,26 @@ static int test1(int argc, const char* argv[])
      If you have problems with this test timing out on your system, or want to
      run more than 257 iterations, you can change the number of iterations by
      setting the KWSYS_TEST_PROCESS_1_COUNT environment variable.  */
-  (void)argc; (void)argv;
+  (void)argc;
+  (void)argv;
   fprintf(stdout, "Output on stdout from test returning 0.\n");
   fprintf(stderr, "Output on stderr from test returning 0.\n");
   return 0;
 }
 
 static int test2(int argc, const char* argv[])
 {
-  (void)argc; (void)argv;
+  (void)argc;
+  (void)argv;
   fprintf(stdout, "Output on stdout from test returning 123.\n");
   fprintf(stderr, "Output on stderr from test returning 123.\n");
   return 123;
 }
 
 static int test3(int argc, const char* argv[])
 {
-  (void)argc; (void)argv;
+  (void)argc;
+  (void)argv;
   fprintf(stdout, "Output before sleep on stdout from timeout test.\n");
   fprintf(stderr, "Output before sleep on stderr from timeout test.\n");
   fflush(stdout);
@@ -120,7 +113,7 @@ static int test4(int argc, const char* argv[])
   optimize away the write. We hope to 'outsmart' them by using
   'volatile' and a slightly larger address, based on a runtime value. */
   volatile int* invalidAddress = 0;
-  invalidAddress += argc?1:2;
+  invalidAddress += argc ? 1 : 2;
 
 #if defined(_WIN32)
   /* Avoid error diagnostic popups since we are crashing on purpose.  */
@@ -129,7 +122,8 @@ static int test4(int argc, const char* argv[])
   /* Avoid error diagnostic popups since we are crashing on purpose.  */
   disable_debugger(1);
 #endif
-  (void)argc; (void)argv;
+  (void)argc;
+  (void)argv;
   fprintf(stdout, "Output before crash on stdout from crash test.\n");
   fprintf(stderr, "Output before crash on stderr from crash test.\n");
   fflush(stdout);
@@ -155,33 +149,32 @@ static int test5(int argc, const char* argv[])
   fprintf(stderr, "Output on stderr before recursive test.\n");
   fflush(stdout);
   fflush(stderr);
-  r = runChild(cmd, kwsysProcess_State_Exception,
-               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15, 0, 1, 0, 0, 0);
+  r = runChild(cmd, kwsysProcess_State_Exception, kwsysProcess_Exception_Fault,
+               1, 1, 1, 0, 15, 0, 1, 0, 0, 0);
   fprintf(stdout, "Output on stdout after recursive test.\n");
   fprintf(stderr, "Output on stderr after recursive test.\n");
   fflush(stdout);
   fflush(stderr);
   return r;
 }
 
-#define TEST6_SIZE (4096*2)
+#define TEST6_SIZE (4096 * 2)
 static void test6(int argc, const char* argv[])
 {
   int i;
-  char runaway[TEST6_SIZE+1];
-  (void)argc; (void)argv;
-  for(i=0;i < TEST6_SIZE;++i)
-    {
+  char runaway[TEST6_SIZE + 1];
+  (void)argc;
+  (void)argv;
+  for (i = 0; i < TEST6_SIZE; ++i) {
     runaway[i] = '.';
-    }
+  }
   runaway[TEST6_SIZE] = '\n';
 
   /* Generate huge amounts of output to test killing.  */
-  for(;;)
-    {
-    fwrite(runaway, 1, TEST6_SIZE+1, stdout);
+  for (;;) {
+    fwrite(runaway, 1, TEST6_SIZE + 1, stdout);
     fflush(stdout);
-    }
+  }
 }
 
 /* Define MINPOLL to be one more than the number of times output is
@@ -191,7 +184,8 @@ static void test6(int argc, const char* argv[])
 #define MAXPOLL 20
 static int test7(int argc, const char* argv[])
 {
-  (void)argc; (void)argv;
+  (void)argc;
+  (void)argv;
   fprintf(stdout, "Output on stdout before sleep.\n");
   fprintf(stderr, "Output on stderr before sleep.\n");
   fflush(stdout);
@@ -231,7 +225,8 @@ static int test8(int argc, const char* argv[])
 
 static int test8_grandchild(int argc, const char* argv[])
 {
-  (void)argc; (void)argv;
+  (void)argc;
+  (void)argv;
   fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
   fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
   fflush(stdout);
@@ -266,9 +261,8 @@ static int test9(int argc, const char* argv[])
   fprintf(stderr, "Output on stderr before grandchild test.\n");
   fflush(stdout);
   fflush(stderr);
-  r = runChild(cmd, kwsysProcess_State_Exited,
-               kwsysProcess_Exception_None,
-               0, 1, 1, 0, 30, 0, 1, 0, 0, 0);
+  r = runChild(cmd, kwsysProcess_State_Exited, kwsysProcess_Exception_None, 0,
+               1, 1, 0, 30, 0, 1, 0, 0, 0);
   /* This sleep will avoid a race condition between this function exiting
      normally and our Ctrl+C handler exiting abnormally after the process
      exits.  */
@@ -294,21 +288,20 @@ static BOOL WINAPI test9_grandchild_handler(DWORD dwCtrlType)
 static int test9_grandchild(int argc, const char* argv[])
 {
   /* The grandchild just sleeps for a few seconds while ignoring signals.  */
-  (void)argc; (void)argv;
+  (void)argc;
+  (void)argv;
 #if defined(_WIN32)
-  if(!SetConsoleCtrlHandler(test9_grandchild_handler, TRUE))
-    {
+  if (!SetConsoleCtrlHandler(test9_grandchild_handler, TRUE)) {
     return 1;
-    }
+  }
 #else
   struct sigaction sa;
   memset(&sa, 0, sizeof(sa));
   sa.sa_handler = SIG_IGN;
   sigemptyset(&sa.sa_mask);
-  if(sigaction(SIGINT, &sa, 0) < 0)
-    {
+  if (sigaction(SIGINT, &sa, 0) < 0) {
     return 1;
-    }
+  }
 #endif
   fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
   fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
@@ -341,9 +334,9 @@ static int test10(int argc, const char* argv[])
   fprintf(stderr, "Output on stderr before grandchild test.\n");
   fflush(stdout);
   fflush(stderr);
-  r = runChild(cmd, kwsysProcess_State_Exception,
-               kwsysProcess_Exception_Interrupt,
-               0, 1, 1, 0, 30, 0, 1, 0, 1, 0);
+  r =
+    runChild(cmd, kwsysProcess_State_Exception,
+             kwsysProcess_Exception_Interrupt, 0, 1, 1, 0, 30, 0, 1, 0, 1, 0);
   fprintf(stdout, "Output on stdout after grandchild test.\n");
   fprintf(stderr, "Output on stderr after grandchild test.\n");
   fflush(stdout);
@@ -354,7 +347,8 @@ static int test10(int argc, const char* argv[])
 static int test10_grandchild(int argc, const char* argv[])
 {
   /* The grandchild just sleeps for a few seconds and handles signals.  */
-  (void)argc; (void)argv;
+  (void)argc;
+  (void)argv;
   fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
   fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
   fflush(stdout);
@@ -368,158 +362,139 @@ static int test10_grandchild(int argc, const char* argv[])
   return 0;
 }
 
-static int runChild2(kwsysProcess* kp,
-              const char* cmd[], int state, int exception, int value,
-              int share, int output, int delay, double timeout,
-              int poll, int disown, int createNewGroup,
-              unsigned int interruptDelay)
+static int runChild2(kwsysProcess* kp, const char* cmd[], int state,
+                     int exception, int value, int share, int output,
+                     int delay, double timeout, int poll, int disown,
+                     int createNewGroup, unsigned int interruptDelay)
 {
   int result = 0;
   char* data = 0;
   int length = 0;
   double userTimeout = 0;
   double* pUserTimeout = 0;
   kwsysProcess_SetCommand(kp, cmd);
-  if(timeout >= 0)
-    {
+  if (timeout >= 0) {
     kwsysProcess_SetTimeout(kp, timeout);
-    }
-  if(share)
-    {
+  }
+  if (share) {
     kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDOUT, 1);
     kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDERR, 1);
-    }
-  if(disown)
-    {
+  }
+  if (disown) {
     kwsysProcess_SetOption(kp, kwsysProcess_Option_Detach, 1);
-    }
-  if(createNewGroup)
-    {
+  }
+  if (createNewGroup) {
     kwsysProcess_SetOption(kp, kwsysProcess_Option_CreateProcessGroup, 1);
-    }
+  }
   kwsysProcess_Execute(kp);
 
-  if(poll)
-    {
+  if (poll) {
     pUserTimeout = &userTimeout;
-    }
+  }
 
-  if(interruptDelay)
-    {
+  if (interruptDelay) {
     testProcess_sleep(interruptDelay);
     kwsysProcess_Interrupt(kp);
-    }
+  }
 
-  if(!share && !disown)
-    {
+  if (!share && !disown) {
     int p;
-    while((p = kwsysProcess_WaitForData(kp, &data, &length, pUserTimeout)))
-      {
-      if(output)
-        {
-        if(poll && p == kwsysProcess_Pipe_Timeout)
-          {
+    while ((p = kwsysProcess_WaitForData(kp, &data, &length, pUserTimeout))) {
+      if (output) {
+        if (poll && p == kwsysProcess_Pipe_Timeout) {
           fprintf(stdout, "WaitForData timeout reached.\n");
           fflush(stdout);
 
           /* Count the number of times we polled without getting data.
              If it is excessive then kill the child and fail.  */
-          if(++poll >= MAXPOLL)
-            {
-            fprintf(stdout, "Poll count reached limit %d.\n",
-                    MAXPOLL);
+          if (++poll >= MAXPOLL) {
+            fprintf(stdout, "Poll count reached limit %d.\n", MAXPOLL);
             kwsysProcess_Kill(kp);
-            }
           }
-        else
-          {
-          fwrite(data, 1, (size_t) length, stdout);
+        } else {
+          fwrite(data, 1, (size_t)length, stdout);
           fflush(stdout);
-          }
         }
-      if(poll)
-        {
+      }
+      if (poll) {
         /* Delay to avoid busy loop during polling.  */
         testProcess_usleep(100000);
-        }
-      if(delay)
-        {
-        /* Purposely sleeping only on Win32 to let pipe fill up.  */
+      }
+      if (delay) {
+/* Purposely sleeping only on Win32 to let pipe fill up.  */
 #if defined(_WIN32)
         testProcess_usleep(100000);
 #endif
-        }
       }
     }
+  }
 
-  if(disown)
-    {
+  if (disown) {
     kwsysProcess_Disown(kp);
-    }
-  else
-    {
+  } else {
     kwsysProcess_WaitForExit(kp, 0);
-    }
+  }
 
-  switch (kwsysProcess_GetState(kp))
-    {
+  switch (kwsysProcess_GetState(kp)) {
     case kwsysProcess_State_Starting:
-      printf("No process has been executed.\n"); break;
+      printf("No process has been executed.\n");
+      break;
     case kwsysProcess_State_Executing:
-      printf("The process is still executing.\n"); break;
+      printf("The process is still executing.\n");
+      break;
     case kwsysProcess_State_Expired:
-      printf("Child was killed when timeout expired.\n"); break;
+      printf("Child was killed when timeout expired.\n");
+      break;
     case kwsysProcess_State_Exited:
-      printf("Child exited with value = %d\n",
-             kwsysProcess_GetExitValue(kp));
+      printf("Child exited with value = %d\n", kwsysProcess_GetExitValue(kp));
       result = ((exception != kwsysProcess_GetExitException(kp)) ||
-                (value != kwsysProcess_GetExitValue(kp))); break;
+                (value != kwsysProcess_GetExitValue(kp)));
+      break;
     case kwsysProcess_State_Killed:
-      printf("Child was killed by parent.\n"); break;
+      printf("Child was killed by parent.\n");
+      break;
     case kwsysProcess_State_Exception:
       printf("Child terminated abnormally: %s\n",
              kwsysProcess_GetExceptionString(kp));
       result = ((exception != kwsysProcess_GetExitException(kp)) ||
-                (value != kwsysProcess_GetExitValue(kp))); break;
+                (value != kwsysProcess_GetExitValue(kp)));
+      break;
     case kwsysProcess_State_Disowned:
-      printf("Child was disowned.\n"); break;
+      printf("Child was disowned.\n");
+      break;
     case kwsysProcess_State_Error:
       printf("Error in administrating child process: [%s]\n",
-             kwsysProcess_GetErrorString(kp)); break;
-    };
+             kwsysProcess_GetErrorString(kp));
+      break;
+  };
 
-  if(result)
-    {
-    if(exception != kwsysProcess_GetExitException(kp))
-      {
+  if (result) {
+    if (exception != kwsysProcess_GetExitException(kp)) {
       fprintf(stderr, "Mismatch in exit exception.  "
-              "Should have been %d, was %d.\n",
+                      "Should have been %d, was %d.\n",
               exception, kwsysProcess_GetExitException(kp));
-      }
-    if(value != kwsysProcess_GetExitValue(kp))
-      {
+    }
+    if (value != kwsysProcess_GetExitValue(kp)) {
       fprintf(stderr, "Mismatch in exit value.  "
-              "Should have been %d, was %d.\n",
+                      "Should have been %d, was %d.\n",
               value, kwsysProcess_GetExitValue(kp));
-      }
     }
+  }
 
-  if(kwsysProcess_GetState(kp) != state)
-    {
+  if (kwsysProcess_GetState(kp) != state) {
     fprintf(stderr, "Mismatch in state.  "
-            "Should have been %d, was %d.\n",
+                    "Should have been %d, was %d.\n",
             state, kwsysProcess_GetState(kp));
     result = 1;
-    }
+  }
 
   /* We should have polled more times than there were data if polling
      was enabled.  */
-  if(poll && poll < MINPOLL)
-    {
-    fprintf(stderr, "Poll count is %d, which is less than %d.\n",
-            poll, MINPOLL);
+  if (poll && poll < MINPOLL) {
+    fprintf(stderr, "Poll count is %d, which is less than %d.\n", poll,
+            MINPOLL);
     result = 1;
-    }
+  }
 
   return result;
 }
@@ -551,28 +526,23 @@ static int runChild2(kwsysProcess* kp,
  *                  BEFORE any reading/polling of pipes occurs and before any
  *                  detachment occurs.
  */
-int runChild(const char* cmd[], int state, int exception, int value,
-             int share, int output, int delay, double timeout,
-             int poll, int repeat, int disown, int createNewGroup,
-             unsigned int interruptDelay)
+int runChild(const char* cmd[], int state, int exception, int value, int share,
+             int output, int delay, double timeout, int poll, int repeat,
+             int disown, int createNewGroup, unsigned int interruptDelay)
 {
   int result = 1;
   kwsysProcess* kp = kwsysProcess_New();
-  if(!kp)
-    {
+  if (!kp) {
     fprintf(stderr, "kwsysProcess_New returned NULL!\n");
     return 1;
-    }
-  while(repeat-- > 0)
-    {
-    result = runChild2(kp, cmd, state, exception, value, share,
-                       output, delay, timeout, poll, disown, createNewGroup,
-                       interruptDelay);
-    if(result)
-      {
+  }
+  while (repeat-- > 0) {
+    result = runChild2(kp, cmd, state, exception, value, share, output, delay,
+                       timeout, poll, disown, createNewGroup, interruptDelay);
+    if (result) {
       break;
-      }
     }
+  }
   kwsysProcess_Delete(kp);
   return result;
 }
@@ -585,8 +555,7 @@ int main(int argc, const char* argv[])
   int i;
   char new_args[10][_MAX_PATH];
   LPWSTR* w_av = CommandLineToArgvW(GetCommandLineW(), &argc);
-  for(i=0; i<argc; i++)
-  {
+  for (i = 0; i < argc; i++) {
     kwsysEncoding_wcstombs(new_args[i], w_av[i], _MAX_PATH);
     argv[i] = new_args[i];
   }
@@ -609,107 +578,96 @@ int main(int argc, const char* argv[])
     SetStdHandle(STD_ERROR_HANDLE, out);
     }
 #endif
-  if(argc == 2)
-    {
+  if (argc == 2) {
     n = atoi(argv[1]);
-    }
-  else if(argc == 3 && strcmp(argv[1], "run") == 0)
-    {
+  } else if (argc == 3 && strcmp(argv[1], "run") == 0) {
     n = atoi(argv[2]);
-    }
+  }
   /* Check arguments.  */
-  if(((n >= 1 && n <= 10) || n == 108 || n == 109 || n == 110) && argc == 3)
-    {
+  if (((n >= 1 && n <= 10) || n == 108 || n == 109 || n == 110) && argc == 3) {
     /* This is the child process for a requested test number.  */
-    switch (n)
-      {
-      case 1: return test1(argc, argv);
-      case 2: return test2(argc, argv);
-      case 3: return test3(argc, argv);
-      case 4: return test4(argc, argv);
-      case 5: return test5(argc, argv);
-      case 6: test6(argc, argv); return 0;
-      case 7: return test7(argc, argv);
-      case 8: return test8(argc, argv);
-      case 9: return test9(argc, argv);
-      case 10: return test10(argc, argv);
-      case 108: return test8_grandchild(argc, argv);
-      case 109: return test9_grandchild(argc, argv);
-      case 110: return test10_grandchild(argc, argv);
-      }
+    switch (n) {
+      case 1:
+        return test1(argc, argv);
+      case 2:
+        return test2(argc, argv);
+      case 3:
+        return test3(argc, argv);
+      case 4:
+        return test4(argc, argv);
+      case 5:
+        return test5(argc, argv);
+      case 6:
+        test6(argc, argv);
+        return 0;
+      case 7:
+        return test7(argc, argv);
+      case 8:
+        return test8(argc, argv);
+      case 9:
+        return test9(argc, argv);
+      case 10:
+        return test10(argc, argv);
+      case 108:
+        return test8_grandchild(argc, argv);
+      case 109:
+        return test9_grandchild(argc, argv);
+      case 110:
+        return test10_grandchild(argc, argv);
+    }
     fprintf(stderr, "Invalid test number %d.\n", n);
     return 1;
-    }
-  else if(n >= 1 && n <= 10)
-    {
+  } else if (n >= 1 && n <= 10) {
     /* This is the parent process for a requested test number.  */
-    int states[10] =
-    {
-      kwsysProcess_State_Exited,
-      kwsysProcess_State_Exited,
-      kwsysProcess_State_Expired,
-      kwsysProcess_State_Exception,
-      kwsysProcess_State_Exited,
-      kwsysProcess_State_Expired,
-      kwsysProcess_State_Exited,
-      kwsysProcess_State_Exited,
-      kwsysProcess_State_Expired, /* Ctrl+C handler test */
+    int states[10] = {
+      kwsysProcess_State_Exited,   kwsysProcess_State_Exited,
+      kwsysProcess_State_Expired,  kwsysProcess_State_Exception,
+      kwsysProcess_State_Exited,   kwsysProcess_State_Expired,
+      kwsysProcess_State_Exited,   kwsysProcess_State_Exited,
+      kwsysProcess_State_Expired,  /* Ctrl+C handler test */
       kwsysProcess_State_Exception /* Process group test */
     };
-    int exceptions[10] =
-    {
-      kwsysProcess_Exception_None,
-      kwsysProcess_Exception_None,
-      kwsysProcess_Exception_None,
-      kwsysProcess_Exception_Fault,
-      kwsysProcess_Exception_None,
-      kwsysProcess_Exception_None,
-      kwsysProcess_Exception_None,
-      kwsysProcess_Exception_None,
-      kwsysProcess_Exception_None,
-      kwsysProcess_Exception_Interrupt
+    int exceptions[10] = {
+      kwsysProcess_Exception_None, kwsysProcess_Exception_None,
+      kwsysProcess_Exception_None, kwsysProcess_Exception_Fault,
+      kwsysProcess_Exception_None, kwsysProcess_Exception_None,
+      kwsysProcess_Exception_None, kwsysProcess_Exception_None,
+      kwsysProcess_Exception_None, kwsysProcess_Exception_Interrupt
     };
-    int values[10] = {0, 123, 1, 1, 0, 0, 0, 0, 1, 1};
-    int shares[10] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
-    int outputs[10] = {1, 1, 1, 1, 1, 0, 1, 1, 1, 1};
-    int delays[10] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
-    double timeouts[10] = {10, 10, 10, 30, 30, 10, -1, 10, 6, 4};
-    int polls[10] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
-    int repeat[10] = {257, 1, 1, 1, 1, 1, 1, 1, 1, 1};
-    int createNewGroups[10] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
-    unsigned int interruptDelays[10] = {0, 0, 0, 0, 0, 0, 0, 0, 3, 2};
+    int values[10] = { 0, 123, 1, 1, 0, 0, 0, 0, 1, 1 };
+    int shares[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
+    int outputs[10] = { 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 };
+    int delays[10] = { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 };
+    double timeouts[10] = { 10, 10, 10, 30, 30, 10, -1, 10, 6, 4 };
+    int polls[10] = { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 };
+    int repeat[10] = { 257, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
+    int createNewGroups[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
+    unsigned int interruptDelays[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 3, 2 };
     int r;
     const char* cmd[4];
 #ifdef _WIN32
     char* argv0 = 0;
 #endif
     char* test1IterationsStr = getenv("KWSYS_TEST_PROCESS_1_COUNT");
-    if(test1IterationsStr)
-      {
+    if (test1IterationsStr) {
       long int test1Iterations = strtol(test1IterationsStr, 0, 10);
-      if(test1Iterations > 10 && test1Iterations != LONG_MAX)
-        {
+      if (test1Iterations > 10 && test1Iterations != LONG_MAX) {
         repeat[0] = (int)test1Iterations;
-        }
       }
+    }
 #ifdef _WIN32
-    if(n == 0 && (argv0 = strdup(argv[0])))
-      {
+    if (n == 0 && (argv0 = strdup(argv[0]))) {
       /* Try converting to forward slashes to see if it works.  */
       char* c;
-      for(c=argv0; *c; ++c)
-        {
-        if(*c == '\\')
-          {
+      for (c = argv0; *c; ++c) {
+        if (*c == '\\') {
           *c = '/';
-          }
         }
-      cmd[0] = argv0;
       }
-    else
-      {
+      cmd[0] = argv0;
+    } else {
       cmd[0] = argv[0];
-      }
+    }
 #else
     cmd[0] = argv[0];
 #endif
@@ -720,36 +678,34 @@ int main(int argc, const char* argv[])
     fprintf(stderr, "Output on stderr before test %d.\n", n);
     fflush(stdout);
     fflush(stderr);
-    r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], shares[n-1],
-                 outputs[n-1], delays[n-1], timeouts[n-1],
-                 polls[n-1], repeat[n-1], 0, createNewGroups[n-1],
-                 interruptDelays[n-1]);
+    r = runChild(cmd, states[n - 1], exceptions[n - 1], values[n - 1],
+                 shares[n - 1], outputs[n - 1], delays[n - 1], timeouts[n - 1],
+                 polls[n - 1], repeat[n - 1], 0, createNewGroups[n - 1],
+                 interruptDelays[n - 1]);
     fprintf(stdout, "Output on stdout after test %d.\n", n);
     fprintf(stderr, "Output on stderr after test %d.\n", n);
     fflush(stdout);
     fflush(stderr);
 #if defined(_WIN32)
-    if(argv0) { free(argv0); }
+    if (argv0) {
+      free(argv0);
+    }
 #endif
     return r;
-    }
-  else if(argc > 2 && strcmp(argv[1], "0") == 0)
-    {
+  } else if (argc > 2 && strcmp(argv[1], "0") == 0) {
     /* This is the special debugging test to run a given command
        line.  */
-    const char** cmd = argv+2;
+    const char** cmd = argv + 2;
     int state = kwsysProcess_State_Exited;
     int exception = kwsysProcess_Exception_None;
     int value = 0;
     double timeout = 0;
-    int r = runChild(cmd, state, exception, value, 0, 1, 0, timeout,
-      0, 1, 0, 0, 0);
+    int r =
+      runChild(cmd, state, exception, value, 0, 1, 0, timeout, 0, 1, 0, 0, 0);
     return r;
-    }
-  else
-    {
+  } else {
     /* Improper usage.  */
     fprintf(stdout, "Usage: %s <test number>\n", argv[0]);
     return 1;
-    }
+  }
 }