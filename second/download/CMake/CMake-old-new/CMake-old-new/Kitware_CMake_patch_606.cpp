@@ -22,7 +22,7 @@
 #endif
 
 int runChild(const char* cmd[], int state, int exception, int value,
-             int share, int delay, double timeout);
+             int share, int output, int delay, double timeout);
 
 int test1(int argc, const char* argv[])
 {
@@ -84,7 +84,7 @@ int test5(int argc, const char* argv[])
   fflush(stdout);
   fflush(stderr);
   r = runChild(cmd, kwsysProcess_State_Exception,
-               kwsysProcess_Exception_Fault, 1, 1, 0, 2);
+               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 2);
   fprintf(stdout, "Output on stdout after recursive test.\n");
   fprintf(stderr, "Output on stderr after recursive test.\n");
   fflush(stdout);
@@ -115,7 +115,7 @@ int test6(int argc, const char* argv[])
 
 
 int runChild(const char* cmd[], int state, int exception, int value,
-             int share, int delay, double timeout)
+             int share, int output, int delay, double timeout)
 {
   int result = 0;
   char* data = 0;
@@ -140,10 +140,14 @@ int runChild(const char* cmd[], int state, int exception, int value,
     {
     while(kwsysProcess_WaitForData(kp, &data, &length, 0))
       {
-      fwrite(data, 1, length, stdout);
-      fflush(stdout);
+      if(output)
+        {
+        fwrite(data, 1, length, stdout);
+        fflush(stdout);
+        }
       if(delay)
         {
+        /* Purposely sleeping only on Win32 to let pipe fill up.  */
 #if defined(_WIN32)
         Sleep(100);
 #endif
@@ -271,6 +275,7 @@ int main(int argc, const char* argv[])
       kwsysProcess_Exception_None
     };
     int values[6] = {0, 123, 1, 1, 0, 0};
+    int outputs[6] = {1, 1, 1, 1, 1, 0};
     int delays[6] = {0, 0, 0, 0, 0, 1};
     double timeouts[6] = {3, 3, 3, 3, 3, 0.1};
     int r;
@@ -284,7 +289,7 @@ int main(int argc, const char* argv[])
     fflush(stdout);
     fflush(stderr);
     r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], 0,
-                 delays[n-1], timeouts[n-1]);
+                 outputs[n-1], delays[n-1], timeouts[n-1]);
     fprintf(stdout, "Output on stdout after test %d.\n", n);
     fprintf(stderr, "Output on stderr after test %d.\n", n);
     fflush(stdout);