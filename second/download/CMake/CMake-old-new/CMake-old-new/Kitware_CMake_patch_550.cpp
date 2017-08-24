@@ -34,6 +34,17 @@
 # pragma warn -8060 /* possibly incorrect assignment */
 #endif
 
+#if defined(__BEOS__) && !defined(__ZETA__)
+/* BeOS 5 doesn't have usleep(), but it has snooze(), which is identical. */
+# include <be/kernel/OS.h>
+static inline void testProcess_usleep(unsigned int msec)
+{
+  snooze(msec);
+}
+#else
+# define testProcess_usleep usleep
+#endif
+
 int runChild(const char* cmd[], int state, int exception, int value,
              int share, int output, int delay, double timeout, int poll,
              int repeat, int disown);
@@ -76,6 +87,9 @@ int test4(int argc, const char* argv[])
 #if defined(_WIN32)
   /* Avoid error diagnostic popups since we are crashing on purpose.  */
   SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
+#elif defined(__BEOS__)
+  /* Avoid error diagnostic popups since we are crashing on purpose.  */
+  disable_debugger(1);
 #endif
   (void)argc; (void)argv;
   fprintf(stdout, "Output before crash on stdout from crash test.\n");
@@ -264,7 +278,7 @@ int runChild2(kwsysProcess* kp,
 #if defined(_WIN32)
         Sleep(100);
 #else
-        usleep(100000);
+        testProcess_usleep(100000);
 #endif
         }
       if(delay)