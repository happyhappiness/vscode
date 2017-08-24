@@ -31,7 +31,8 @@
 #endif
 
 int runChild(const char* cmd[], int state, int exception, int value,
-             int share, int output, int delay, double timeout, int poll);
+             int share, int output, int delay, double timeout, int poll,
+             int repeat);
 
 int test1(int argc, const char* argv[])
 {
@@ -97,7 +98,7 @@ int test5(int argc, const char* argv[])
   fflush(stdout);
   fflush(stderr);
   r = runChild(cmd, kwsysProcess_State_Exception,
-               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15, 0);
+               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15, 0, 1);
   fprintf(stdout, "Output on stdout after recursive test.\n");
   fprintf(stderr, "Output on stderr after recursive test.\n");
   fflush(stdout);
@@ -150,22 +151,16 @@ int test7(int argc, const char* argv[])
   return 0;
 }
 
-int runChild(const char* cmd[], int state, int exception, int value,
-             int share, int output, int delay, double timeout,
-             int poll)
+int runChild2(kwsysProcess* kp,
+              const char* cmd[], int state, int exception, int value,
+              int share, int output, int delay, double timeout,
+              int poll)
 {
   int result = 0;
   char* data = 0;
   int length = 0;
   double userTimeout = 0;
   double* pUserTimeout = 0;
-  kwsysProcess* kp = kwsysProcess_New();
-  if(!kp)
-    {
-    fprintf(stderr, "kwsysProcess_New returned NULL!\n");
-    return 1;
-    }
-  
   kwsysProcess_SetCommand(kp, cmd);
   if(timeout >= 0)
     {
@@ -288,7 +283,26 @@ int runChild(const char* cmd[], int state, int exception, int value,
             poll, MINPOLL);
     result = 1;
     }
-  
+
+  return result;
+}
+
+int runChild(const char* cmd[], int state, int exception, int value,
+             int share, int output, int delay, double timeout,
+             int poll, int repeat)
+{
+  int result;
+  kwsysProcess* kp = kwsysProcess_New();
+  if(!kp)
+    {
+    fprintf(stderr, "kwsysProcess_New returned NULL!\n");
+    return 1;
+    }
+  while(repeat-- > 0)
+    {
+    result = runChild2(kp, cmd, state, exception, value, share,
+                       output, delay, timeout, poll);
+    }
   kwsysProcess_Delete(kp);
   return result;
 }
@@ -369,6 +383,7 @@ int main(int argc, const char* argv[])
     int delays[7] = {0, 0, 0, 0, 0, 1, 0};
     double timeouts[7] = {10, 10, 10, 10, 30, 10, -1};
     int polls[7] = {0, 0, 0, 0, 0, 0, 1};
+    int repeat[7] = {2, 1, 1, 1, 1, 1, 1};
     int r;
     const char* cmd[4];
 #ifdef _WIN32
@@ -402,7 +417,7 @@ int main(int argc, const char* argv[])
     fflush(stderr);
     r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], 0,
                  outputs[n-1], delays[n-1], timeouts[n-1],
-                 polls[n-1]);
+                 polls[n-1], repeat[n-1]);
     fprintf(stdout, "Output on stdout after test %d.\n", n);
     fprintf(stderr, "Output on stderr after test %d.\n", n);
     fflush(stdout);