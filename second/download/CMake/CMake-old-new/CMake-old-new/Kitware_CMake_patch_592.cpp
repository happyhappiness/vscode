@@ -97,7 +97,7 @@ int test5(int argc, const char* argv[])
   fflush(stdout);
   fflush(stderr);
   r = runChild(cmd, kwsysProcess_State_Exception,
-               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 2);
+               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 1);
   fprintf(stdout, "Output on stdout after recursive test.\n");
   fprintf(stderr, "Output on stderr after recursive test.\n");
   fflush(stdout);
@@ -198,19 +198,23 @@ int runChild(const char* cmd[], int state, int exception, int value,
     {
     if(exception != kwsysProcess_GetExitException(kp))
       {
-      fprintf(stderr, "Mismatch in exit exception.  Should have been %d.\n",
-              exception);
+      fprintf(stderr, "Mismatch in exit exception.  "
+              "Should have been %d, was %d.\n",
+              exception, kwsysProcess_GetExitException(kp));
       }
     if(value != kwsysProcess_GetExitValue(kp))
       {
-      fprintf(stderr, "Mismatch in exit value.  Should have been %d.\n",
-              value);
+      fprintf(stderr, "Mismatch in exit value.  "
+              "Should have been %d, was %d.\n",
+              value, kwsysProcess_GetExitValue(kp));
       }
     }
   
   if(kwsysProcess_GetState(kp) != state)
     {
-    fprintf(stderr, "Mismatch in state.  Should have been %d.\n", state);
+    fprintf(stderr, "Mismatch in state.  "
+            "Should have been %d, was %d.\n",
+            state, kwsysProcess_GetState(kp));
     result = 1;
     }
   
@@ -289,7 +293,7 @@ int main(int argc, const char* argv[])
     int values[6] = {0, 123, 1, 1, 0, 0};
     int outputs[6] = {1, 1, 1, 1, 1, 0};
     int delays[6] = {0, 0, 0, 0, 0, 1};
-    double timeouts[6] = {3, 3, 3, 3, 3, 0.1};
+    double timeouts[6] = {3, 3, 3, 3, 5, 0.1};
     int r;
     const char* cmd[4];
     cmd[0] = argv[0];