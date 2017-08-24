@@ -57,9 +57,9 @@ int test3(int argc, const char* argv[])
   fflush(stdout);
   fflush(stderr);
 #if defined(_WIN32)
-  Sleep(5000);
+  Sleep(15000);
 #else
-  sleep(5);
+  sleep(15);
 #endif
   fprintf(stdout, "Output after sleep on stdout from timeout test.\n");
   fprintf(stderr, "Output after sleep on stderr from timeout test.\n");
@@ -293,7 +293,7 @@ int main(int argc, const char* argv[])
     int values[6] = {0, 123, 1, 1, 0, 0};
     int outputs[6] = {1, 1, 1, 1, 1, 0};
     int delays[6] = {0, 0, 0, 0, 0, 1};
-    double timeouts[6] = {3, 3, 3, 3, 30, 3};
+    double timeouts[6] = {10, 10, 10, 10, 30, 10};
     int r;
     const char* cmd[4];
     cmd[0] = argv[0];