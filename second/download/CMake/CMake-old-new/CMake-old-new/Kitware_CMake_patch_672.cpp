@@ -22,7 +22,7 @@
 #endif
 
 int runChild(const char* cmd[], int state, int exception, int value,
-             int share, double timeout);
+             int share, int delay, double timeout);
 
 int test1(int argc, const char* argv[])
 {
@@ -84,17 +84,39 @@ int test5(int argc, const char* argv[])
   fflush(stdout);
   fflush(stderr);
   r = runChild(cmd, kwsysProcess_State_Exception,
-               kwsysProcess_Exception_Fault, 1, 1, 2);
+               kwsysProcess_Exception_Fault, 1, 1, 0, 2);
   fprintf(stdout, "Output on stdout after recursive test.\n");
   fprintf(stderr, "Output on stderr after recursive test.\n");
   fflush(stdout);
   fflush(stderr);
   return r;
 }
 
+#define TEST6_SIZE (4096*2)
+int test6(int argc, const char* argv[])
+{
+  int i;
+  char runaway[TEST6_SIZE+2];
+  (void)argc; (void)argv;
+  for(i=0;i < TEST6_SIZE;++i)
+    {
+    runaway[i] = '.';
+    }
+  runaway[TEST6_SIZE] = '\n';
+  runaway[TEST6_SIZE] = 0;
+
+  /* Generate huge amounts of output to test killing.  */
+  for(;;)
+    {
+    fwrite(runaway, 1, TEST6_SIZE+2, stdout);
+    fflush(stdout);
+    }
+  return 0;
+}
+
 
 int runChild(const char* cmd[], int state, int exception, int value,
-             int share, double timeout)
+             int share, int delay, double timeout)
 {
   int result = 0;
   char* data = 0;
@@ -121,6 +143,12 @@ int runChild(const char* cmd[], int state, int exception, int value,
       {
       fwrite(data, 1, length, stdout);
       fflush(stdout);
+      if(delay)
+        {
+#if defined(_WIN32)
+        Sleep(100);
+#endif
+        }
       }
     }
   
@@ -203,7 +231,7 @@ int main(int argc, const char* argv[])
     n = atoi(argv[2]);
     }
   /* Check arguments.  */
-  if(n < 1 || n > 5 || (argc == 3 && strcmp(argv[1], "run") != 0))
+  if(n < 1 || n > 6 || (argc == 3 && strcmp(argv[1], "run") != 0))
     {
     fprintf(stdout, "Usage: %s <test number>\n", argv[0]);
     return 1;
@@ -217,30 +245,35 @@ int main(int argc, const char* argv[])
       case 3: return test3(argc, argv);
       case 4: return test4(argc, argv);
       case 5: return test5(argc, argv);
+      case 6: return test6(argc, argv);
       }
     fprintf(stderr, "Invalid test number %d.\n", n);
     return 1;
     }
   
-  if(n >= 0 && n <= 5)
+  if(n >= 0 && n <= 6)
     {
-    int states[5] =
+    int states[6] =
     {
       kwsysProcess_State_Exited,
       kwsysProcess_State_Exited,
       kwsysProcess_State_Expired,
       kwsysProcess_State_Exception,
-      kwsysProcess_State_Exited
+      kwsysProcess_State_Exited,
+      kwsysProcess_State_Expired
     };
-    int exceptions[5] =
+    int exceptions[6] =
     {
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_None,
       kwsysProcess_Exception_Fault,
+      kwsysProcess_Exception_None,
       kwsysProcess_Exception_None
     };
-    int values[5] = {0, 123, 1, 1, 0};
+    int values[6] = {0, 123, 1, 1, 0, 0};
+    int delays[6] = {0, 0, 0, 0, 0, 1};
+    double timeouts[6] = {3, 3, 3, 3, 3, 0.1};
     int r;
     const char* cmd[4];
     cmd[0] = argv[0];
@@ -251,7 +284,8 @@ int main(int argc, const char* argv[])
     fprintf(stderr, "Output on stderr before test %d.\n", n);
     fflush(stdout);
     fflush(stderr);
-    r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], 0, 3);
+    r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], 0,
+                 delays[n-1], timeouts[n-1]);
     fprintf(stdout, "Output on stdout after test %d.\n", n);
     fprintf(stderr, "Output on stderr after test %d.\n", n);
     fflush(stdout);