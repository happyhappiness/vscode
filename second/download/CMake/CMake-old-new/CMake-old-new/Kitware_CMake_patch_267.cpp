@@ -21,6 +21,7 @@
 #endif
 
 #include <assert.h>
+#include <limits.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
@@ -74,6 +75,16 @@ int runChild(const char* cmd[], int state, int exception, int value,
 
 static int test1(int argc, const char* argv[])
 {
+  /* This is a very basic functional test of kwsysProcess.  It is repeated
+     numerous times to verify that there are no resource leaks in kwsysProcess
+     that eventually lead to an error.  Many versions of OS X will fail after
+     256 leaked file handles, so 257 iterations seems to be a good test.  On
+     the other hand, too many iterations will cause the test to time out -
+     especially if the test is instrumented with e.g. valgrind.
+
+     If you have problems with this test timing out on your system, or want to
+     run more than 257 iterations, you can change the number of iterations by
+     setting the KWSYS_TEST_PROCESS_1_COUNT environment variable.  */
   (void)argc; (void)argv;
   fprintf(stdout, "Output on stdout from test returning 0.\n");
   fprintf(stderr, "Output on stderr from test returning 0.\n");
@@ -557,6 +568,10 @@ int runChild(const char* cmd[], int state, int exception, int value,
     result = runChild2(kp, cmd, state, exception, value, share,
                        output, delay, timeout, poll, disown, createNewGroup,
                        interruptDelay);
+    if(result)
+      {
+      break;
+      }
     }
   kwsysProcess_Delete(kp);
   return result;
@@ -660,13 +675,24 @@ int main(int argc, const char* argv[])
     int delays[10] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
     double timeouts[10] = {10, 10, 10, 30, 30, 10, -1, 10, 6, 4};
     int polls[10] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
-    int repeat[10] = {2, 1, 1, 1, 1, 1, 1, 1, 1, 1};
+    int repeat[10] = {257, 1, 1, 1, 1, 1, 1, 1, 1, 1};
     int createNewGroups[10] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
     unsigned int interruptDelays[10] = {0, 0, 0, 0, 0, 0, 0, 0, 3, 2};
     int r;
     const char* cmd[4];
 #ifdef _WIN32
     char* argv0 = 0;
+#endif
+    char* test1IterationsStr = getenv("KWSYS_TEST_PROCESS_1_COUNT");
+    if(test1IterationsStr)
+      {
+      long int test1Iterations = strtol(test1IterationsStr, 0, 10);
+      if(test1Iterations > 10 && test1Iterations != LONG_MAX)
+        {
+        repeat[0] = (int)test1Iterations;
+        }
+      }
+#ifdef _WIN32
     if(n == 0 && (argv0 = strdup(argv[0])))
       {
       /* Try converting to forward slashes to see if it works.  */