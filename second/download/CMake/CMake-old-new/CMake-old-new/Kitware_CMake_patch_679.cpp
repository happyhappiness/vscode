@@ -21,22 +21,28 @@
 # include <unistd.h>
 #endif
 
-int test1()
+int runChild(const char* cmd[], int state, int exception, int value,
+             int share, double timeout);
+
+int test1(int argc, const char* argv[])
 {
+  (void)argc; (void)argv;
   fprintf(stdout, "Output on stdout from test returning 0.\n");
   fprintf(stderr, "Output on stderr from test returning 0.\n");
   return 0;
 }
 
-int test2()
+int test2(int argc, const char* argv[])
 {
+  (void)argc; (void)argv;
   fprintf(stdout, "Output on stdout from test returning 123.\n");
   fprintf(stderr, "Output on stderr from test returning 123.\n");
   return 123;
 }
 
-int test3()
+int test3(int argc, const char* argv[])
 {
+  (void)argc; (void)argv;
   fprintf(stdout, "Output before sleep on stdout from timeout test.\n");
   fprintf(stderr, "Output before sleep on stderr from timeout test.\n");
   fflush(stdout);
@@ -51,8 +57,9 @@ int test3()
   return 0;
 }
 
-int test4()
+int test4(int argc, const char* argv[])
 {
+  (void)argc; (void)argv;
   fprintf(stdout, "Output before crash on stdout from crash test.\n");
   fprintf(stderr, "Output before crash on stderr from crash test.\n");  
   fflush(stdout);
@@ -63,7 +70,30 @@ int test4()
   return 0;
 }
 
-int runChild(const char* cmd[], int state, int exception, int value)
+int test5(int argc, const char* argv[])
+{
+  int r;
+  const char* cmd[4];
+  cmd[0] = argv[0];
+  cmd[1] = "run";
+  cmd[2] = "4";
+  cmd[3] = 0;
+  fprintf(stdout, "Output on stdout before recursive test.\n");
+  fprintf(stderr, "Output on stderr before recursive test.\n");
+  fflush(stdout);
+  fflush(stderr);
+  r = runChild(cmd, kwsysProcess_State_Exception,
+               kwsysProcess_Exception_Fault, 1, 1, 2);
+  fprintf(stdout, "Output on stdout after recursive test.\n");
+  fprintf(stderr, "Output on stderr after recursive test.\n");
+  fflush(stdout);
+  fflush(stderr);
+  return r;
+}
+
+
+int runChild(const char* cmd[], int state, int exception, int value,
+             int share, double timeout)
 {
   int result = 0;
   char* data = 0;
@@ -76,13 +106,21 @@ int runChild(const char* cmd[], int state, int exception, int value)
     }
   
   kwsysProcess_SetCommand(kp, cmd);
-  kwsysProcess_SetTimeout(kp, 3);
+  kwsysProcess_SetTimeout(kp, timeout);
+  if(share)
+    {
+    kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDOUT, 1);
+    kwsysProcess_SetPipeShared(kp, kwsysProcess_Pipe_STDERR, 1);
+    }
   kwsysProcess_Execute(kp);
-  
-  while(kwsysProcess_WaitForData(kp, &data, &length, 0))
+
+  if(!share)
     {
-    fwrite(data, 1, length, stdout);
-    fflush(stdout);
+    while(kwsysProcess_WaitForData(kp, &data, &length, 0))
+      {
+      fwrite(data, 1, length, stdout);
+      fflush(stdout);
+      }
     }
   
   kwsysProcess_WaitForExit(kp, 0);
@@ -138,6 +176,22 @@ int runChild(const char* cmd[], int state, int exception, int value)
 int main(int argc, const char* argv[])
 {
   int n = 0;
+#if 0
+    {
+    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
+    DuplicateHandle(GetCurrentProcess(), out,
+                    GetCurrentProcess(), &out, 0, FALSE,
+                    DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE);
+    SetStdHandle(STD_OUTPUT_HANDLE, out);
+    }
+    {
+    HANDLE out = GetStdHandle(STD_ERROR_HANDLE);
+    DuplicateHandle(GetCurrentProcess(), out,
+                    GetCurrentProcess(), &out, 0, FALSE,
+                    DUPLICATE_SAME_ACCESS | DUPLICATE_CLOSE_SOURCE);
+    SetStdHandle(STD_ERROR_HANDLE, out);
+    }
+#endif
   if(argc == 2)
     {
     n = atoi(argv[1]);
@@ -156,36 +210,55 @@ int main(int argc, const char* argv[])
     {
     switch (n)
       {
-      case 1: return test1();
-      case 2: return test2();
-      case 3: return test3();
-      case 4: return test4();
+      case 1: return test1(argc, argv);
+      case 2: return test2(argc, argv);
+      case 3: return test3(argc, argv);
+      case 4: return test4(argc, argv);
+      case 5: return test5(argc, argv);
       }
     fprintf(stderr, "Invalid test number %d.\n", n);
     return 1;
     }
   
-  if(n <= 4)
+  if(n >= 0 && n <= 5)
     {
-    int states[4] =
-      {
-        kwsysProcess_State_Exited,
-        kwsysProcess_State_Exited,
-        kwsysProcess_State_Expired,
-        kwsysProcess_State_Exception
-      };
-    int exceptions[4] = {kwsysProcess_Exception_None, kwsysProcess_Exception_None,
-                         kwsysProcess_Exception_None, kwsysProcess_Exception_Fault};
-    int values[4] = {0, 123, 1, 1};
+    int states[5] =
+    {
+      kwsysProcess_State_Exited,
+      kwsysProcess_State_Exited,
+      kwsysProcess_State_Expired,
+      kwsysProcess_State_Exception,
+      kwsysProcess_State_Exited
+    };
+    int exceptions[5] =
+    {
+      kwsysProcess_Exception_None,
+      kwsysProcess_Exception_None,
+      kwsysProcess_Exception_None,
+      kwsysProcess_Exception_Fault,
+      kwsysProcess_Exception_None
+    };
+    int values[5] = {0, 123, 1, 1, 0};
+    int r;
     const char* cmd[4];
     cmd[0] = argv[0];
     cmd[1] = "run";
     cmd[2] = argv[1];
     cmd[3] = 0;
-    return runChild(cmd, states[n-1], exceptions[n-1], values[n-1]);
+    fprintf(stdout, "Output on stdout before test %d.\n", n);
+    fprintf(stderr, "Output on stderr before test %d.\n", n);
+    fflush(stdout);
+    fflush(stderr);
+    r = runChild(cmd, states[n-1], exceptions[n-1], values[n-1], 0, 3);
+    fprintf(stdout, "Output on stdout after test %d.\n", n);
+    fprintf(stderr, "Output on stderr after test %d.\n", n);
+    fflush(stdout);
+    fflush(stderr);
+    return r;
     }
   else
     {
-    return 0;
+    fprintf(stderr, "Test number out of range\n");
+    return 1;
     }  
 }