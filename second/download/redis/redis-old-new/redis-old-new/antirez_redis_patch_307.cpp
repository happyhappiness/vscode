@@ -755,18 +755,33 @@ void logRegisters(ucontext_t *uc) {
 #endif
 }
 
+/* Return a file descriptor to write directly to the Redis log with the
+ * write(2) syscall, that can be used in critical sections of the code
+ * where the rest of Redis can't be trusted (for example during the memory
+ * test) or when an API call requires a raw fd.
+ *
+ * Close it with closeDirectLogFiledes(). */
+int openDirectLogFiledes(void) {
+    int log_to_stdout = server.logfile[0] == '\0';
+    int fd = log_to_stdout ?
+        STDOUT_FILENO :
+        open(server.logfile, O_APPEND|O_CREAT|O_WRONLY, 0644);
+    return fd;
+}
+
+/* Used to close what closeDirectLogFiledes() returns. */
+void closeDirectLogFiledes(int fd) {
+    int log_to_stdout = server.logfile[0] == '\0';
+    if (!log_to_stdout) close(fd);
+}
+
 /* Logs the stack trace using the backtrace() call. This function is designed
  * to be called from signal handlers safely. */
 void logStackTrace(ucontext_t *uc) {
     void *trace[101];
-    int trace_size = 0, fd;
-    int log_to_stdout = server.logfile[0] == '\0';
+    int trace_size = 0, fd = openDirectLogFiledes();
 
-    /* Open the log file in append mode. */
-    fd = log_to_stdout ?
-        STDOUT_FILENO :
-        open(server.logfile, O_APPEND|O_CREAT|O_WRONLY, 0644);
-    if (fd == -1) return;
+    if (fd == -1) return; /* If we can't log there is anything to do. */
 
     /* Generate the stack trace */
     trace_size = backtrace(trace+1, 100);
@@ -784,7 +799,7 @@ void logStackTrace(ucontext_t *uc) {
     backtrace_symbols_fd(trace+1, trace_size, fd);
 
     /* Cleanup */
-    if (!log_to_stdout) close(fd);
+    closeDirectLogFiledes(fd);
 }
 
 /* Log information about the "current" client, that is, the client that is
@@ -827,19 +842,24 @@ void logCurrentClient(void) {
 }
 
 #if defined(HAVE_PROC_MAPS)
-void memtest_non_destructive_invert(void *addr, size_t size);
-void memtest_non_destructive_swap(void *addr, size_t size);
+
 #define MEMTEST_MAX_REGIONS 128
 
+/* A non destructive memory test executed during segfauls. */
 int memtest_test_linux_anonymous_maps(void) {
-    FILE *fp = fopen("/proc/self/maps","r");
+    FILE *fp;
     char line[1024];
+    char logbuf[1024];
     size_t start_addr, end_addr, size;
     size_t start_vect[MEMTEST_MAX_REGIONS];
     size_t size_vect[MEMTEST_MAX_REGIONS];
     int regions = 0, j;
-    uint64_t crc1 = 0, crc2 = 0, crc3 = 0;
 
+    int fd = openDirectLogFiledes();
+    if (!fd) return 0;
+
+    fp = fopen("/proc/self/maps","r");
+    if (!fp) return 0;
     while(fgets(line,sizeof(line),fp) != NULL) {
         char *start, *end, *p = line;
 
@@ -863,49 +883,28 @@ int memtest_test_linux_anonymous_maps(void) {
 
         start_vect[regions] = start_addr;
         size_vect[regions] = size;
-        printf("Testing %lx %lu\n", (unsigned long) start_vect[regions],
-                                    (unsigned long) size_vect[regions]);
+        snprintf(logbuf,sizeof(logbuf),
+            "*** Preparing to test memory region %lx (%lu bytes)\n",
+                (unsigned long) start_vect[regions],
+                (unsigned long) size_vect[regions]);
+        if (write(fd,logbuf,strlen(logbuf)) == -1) { /* Nothing to do. */ }
         regions++;
     }
 
-    /* Test all the regions as an unique sequential region.
-     * 1) Take the CRC64 of the memory region. */
+    int errors = 0;
     for (j = 0; j < regions; j++) {
-        crc1 = crc64(crc1,(void*)start_vect[j],size_vect[j]);
+        if (write(fd,".",1) == -1) { /* Nothing to do. */ }
+        errors += memtest_preserving_test((void*)start_vect[j],size_vect[j],1);
+        if (write(fd, errors ? "E" : "O",1) == -1) { /* Nothing to do. */ }
     }
-
-    /* 2) Invert bits, swap adjacent words, swap again, invert bits.
-     * This is the error amplification step. */
-    for (j = 0; j < regions; j++)
-        memtest_non_destructive_invert((void*)start_vect[j],size_vect[j]);
-    for (j = 0; j < regions; j++)
-        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);
-    for (j = 0; j < regions; j++)
-        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);
-    for (j = 0; j < regions; j++)
-        memtest_non_destructive_invert((void*)start_vect[j],size_vect[j]);
-
-    /* 3) Take the CRC64 sum again. */
-    for (j = 0; j < regions; j++)
-        crc2 = crc64(crc2,(void*)start_vect[j],size_vect[j]);
-
-    /* 4) Swap + Swap again */
-    for (j = 0; j < regions; j++)
-        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);
-    for (j = 0; j < regions; j++)
-        memtest_non_destructive_swap((void*)start_vect[j],size_vect[j]);
-
-    /* 5) Take the CRC64 sum again. */
-    for (j = 0; j < regions; j++)
-        crc3 = crc64(crc3,(void*)start_vect[j],size_vect[j]);
+    if (write(fd,"\n",1) == -1) { /* Nothing to do. */ }
 
     /* NOTE: It is very important to close the file descriptor only now
      * because closing it before may result into unmapping of some memory
      * region that we are testing. */
     fclose(fp);
-
-    /* If the two CRC are not the same, we trapped a memory error. */
-    return crc1 != crc2 || crc2 != crc3;
+    closeDirectLogFiledes(fd);
+    return errors;
 }
 #endif
 
@@ -958,10 +957,10 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
     serverLogRaw(LL_WARNING|LL_RAW, "\n------ FAST MEMORY TEST ------\n");
     bioKillThreads();
     if (memtest_test_linux_anonymous_maps()) {
-        serverLog(LL_WARNING,
+        serverLogRaw(LL_WARNING|LL_RAW,
             "!!! MEMORY ERROR DETECTED! Check your memory ASAP !!!");
     } else {
-        serverLog(LL_WARNING,
+        serverLogRaw(LL_WARNING|LL_RAW,
             "Fast memory test PASSED, however your memory can still be broken. Please run a memory test for several hours if possible.");
     }
 #endif