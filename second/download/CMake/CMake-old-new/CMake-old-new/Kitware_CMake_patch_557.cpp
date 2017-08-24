@@ -330,18 +330,14 @@ int main(int argc, const char* argv[])
     {
     n = atoi(argv[1]);
     }
-  else if(argc == 3)
+  else if(argc == 3 && strcmp(argv[1], "run") == 0)
     {
     n = atoi(argv[2]);
     }
   /* Check arguments.  */
-  if(n < 1 || n > 7 || (argc == 3 && strcmp(argv[1], "run") != 0))
-    {
-    fprintf(stdout, "Usage: %s <test number>\n", argv[0]);
-    return 1;
-    }
-  if(argc == 3)
+  if(n >= 1 && n <= 7 && argc == 3)
     {
+    /* This is the child process for a requested test number.  */
     switch (n)
       {
       case 1: return test1(argc, argv);
@@ -355,9 +351,9 @@ int main(int argc, const char* argv[])
     fprintf(stderr, "Invalid test number %d.\n", n);
     return 1;
     }
-  
-  if(n >= 0 && n <= 7)
+  else if(n >= 1 && n <= 7)
     {
+    /* This is the parent process for a requested test number.  */
     int states[7] =
     {
       kwsysProcess_State_Exited,
@@ -427,9 +423,22 @@ int main(int argc, const char* argv[])
 #endif
     return r;
     }
+  else if(argc > 2 && strcmp(argv[1], "0") == 0)
+    {
+    /* This is the special debugging test to run a given command
+       line.  */
+    const char** cmd = argv+2;
+    int state = kwsysProcess_State_Exited;
+    int exception = kwsysProcess_Exception_None;
+    int value = 0;
+    double timeout = 0;
+    int r = runChild(cmd, state, exception, value, 0, 1, 0, timeout, 0, 1);
+    return r;
+    }
   else
     {
-    fprintf(stderr, "Test number out of range\n");
+    /* Improper usage.  */
+    fprintf(stdout, "Usage: %s <test number>\n", argv[0]);
     return 1;
-    }  
+    }
 }