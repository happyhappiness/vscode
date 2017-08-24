@@ -84,14 +84,26 @@ int test4(int argc, const char* argv[])
   return 0;
 }
 
+/* Quick hack to test grandchild killing.  */
+/*#define TEST5_GRANDCHILD_KILL*/
+#ifdef TEST5_GRANDCHILD_KILL
+# define TEST5_TIMEOUT 10
+#else
+# define TEST5_TIMEOUT 30
+#endif
+
 int test5(int argc, const char* argv[])
 {
   int r;
   const char* cmd[4];
   (void)argc;
   cmd[0] = argv[0];
   cmd[1] = "run";
+#ifdef TEST5_GRANDCHILD_KILL
+  cmd[2] = "3";
+#else
   cmd[2] = "4";
+#endif
   cmd[3] = 0;
   fprintf(stdout, "Output on stdout before recursive test.\n");
   fprintf(stderr, "Output on stderr before recursive test.\n");
@@ -377,7 +389,7 @@ int main(int argc, const char* argv[])
     int values[7] = {0, 123, 1, 1, 0, 0, 0};
     int outputs[7] = {1, 1, 1, 1, 1, 0, 1};
     int delays[7] = {0, 0, 0, 0, 0, 1, 0};
-    double timeouts[7] = {10, 10, 10, 10, 30, 10, -1};
+    double timeouts[7] = {10, 10, 10, 10, TEST5_TIMEOUT, 10, -1};
     int polls[7] = {0, 0, 0, 0, 0, 0, 1};
     int repeat[7] = {2, 1, 1, 1, 1, 1, 1};
     int r;