@@ -47,23 +47,23 @@ int runChild(const char* cmd[], int state, int exception, int value,
              int share, int output, int delay, double timeout, int poll,
              int repeat, int disown);
 
-int test1(int argc, const char* argv[])
+static int test1(int argc, const char* argv[])
 {
   (void)argc; (void)argv;
   fprintf(stdout, "Output on stdout from test returning 0.\n");
   fprintf(stderr, "Output on stderr from test returning 0.\n");
   return 0;
 }
 
-int test2(int argc, const char* argv[])
+static int test2(int argc, const char* argv[])
 {
   (void)argc; (void)argv;
   fprintf(stdout, "Output on stdout from test returning 123.\n");
   fprintf(stderr, "Output on stderr from test returning 123.\n");
   return 123;
 }
 
-int test3(int argc, const char* argv[])
+static int test3(int argc, const char* argv[])
 {
   (void)argc; (void)argv;
   fprintf(stdout, "Output before sleep on stdout from timeout test.\n");
@@ -80,7 +80,7 @@ int test3(int argc, const char* argv[])
   return 0;
 }
 
-int test4(int argc, const char* argv[])
+static int test4(int argc, const char* argv[])
 {
   /* Prepare a pointer to an invalid address.  Don't use null, because
   dereferencing null is undefined behaviour and compilers are free to
@@ -109,7 +109,7 @@ int test4(int argc, const char* argv[])
   return 0;
 }
 
-int test5(int argc, const char* argv[])
+static int test5(int argc, const char* argv[])
 {
   int r;
   const char* cmd[4];
@@ -132,7 +132,7 @@ int test5(int argc, const char* argv[])
 }
 
 #define TEST6_SIZE (4096*2)
-void test6(int argc, const char* argv[])
+static void test6(int argc, const char* argv[])
 {
   int i;
   char runaway[TEST6_SIZE+1];
@@ -156,7 +156,7 @@ void test6(int argc, const char* argv[])
    delaying 1/10th of a second should ever have to poll.  */
 #define MINPOLL 5
 #define MAXPOLL 20
-int test7(int argc, const char* argv[])
+static int test7(int argc, const char* argv[])
 {
   (void)argc; (void)argv;
   fprintf(stdout, "Output on stdout before sleep.\n");
@@ -176,7 +176,7 @@ int test7(int argc, const char* argv[])
   return 0;
 }
 
-int test8(int argc, const char* argv[])
+static int test8(int argc, const char* argv[])
 {
   /* Create a disowned grandchild to test handling of processes
      that exit before their children.  */
@@ -200,7 +200,7 @@ int test8(int argc, const char* argv[])
   return r;
 }
 
-int test8_grandchild(int argc, const char* argv[])
+static int test8_grandchild(int argc, const char* argv[])
 {
   (void)argc; (void)argv;
   fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
@@ -221,7 +221,7 @@ int test8_grandchild(int argc, const char* argv[])
   return 0;
 }
 
-int runChild2(kwsysProcess* kp,
+static int runChild2(kwsysProcess* kp,
               const char* cmd[], int state, int exception, int value,
               int share, int output, int delay, double timeout,
               int poll, int disown)
@@ -505,7 +505,7 @@ int main(int argc, const char* argv[])
     fprintf(stderr, "Output on stderr after test %d.\n", n);
     fflush(stdout);
     fflush(stderr);
-#if _WIN32
+#if defined(_WIN32)
     if(argv0) { free(argv0); }
 #endif
     return r;