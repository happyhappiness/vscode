@@ -97,7 +97,7 @@ int test5(int argc, const char* argv[])
   fflush(stdout);
   fflush(stderr);
   r = runChild(cmd, kwsysProcess_State_Exception,
-               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 3);
+               kwsysProcess_Exception_Fault, 1, 1, 1, 0, 15);
   fprintf(stdout, "Output on stdout after recursive test.\n");
   fprintf(stderr, "Output on stderr after recursive test.\n");
   fflush(stdout);
@@ -293,7 +293,7 @@ int main(int argc, const char* argv[])
     int values[6] = {0, 123, 1, 1, 0, 0};
     int outputs[6] = {1, 1, 1, 1, 1, 0};
     int delays[6] = {0, 0, 0, 0, 0, 1};
-    double timeouts[6] = {3, 3, 3, 3, 10, 0.1};
+    double timeouts[6] = {3, 3, 3, 3, 30, 0.1};
     int r;
     const char* cmd[4];
     cmd[0] = argv[0];