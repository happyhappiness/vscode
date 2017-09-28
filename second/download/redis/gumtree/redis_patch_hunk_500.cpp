         (unsigned long) uc->uc_mcontext.gregs[17],
         (unsigned long) uc->uc_mcontext.gregs[18]
     );
     logStackContent((void**)uc->uc_mcontext.gregs[15]);
     #endif
 #else
-    redisLog(REDIS_WARNING,
+    serverLog(LL_WARNING,
         "  Dumping of registers not supported for this OS/arch");
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
-    void *trace[100];
-    int trace_size = 0, fd;
-    int log_to_stdout = server.logfile[0] == '\0';
+    void *trace[101];
+    int trace_size = 0, fd = openDirectLogFiledes();
 
-    /* Open the log file in append mode. */
-    fd = log_to_stdout ?
-        STDOUT_FILENO :
-        open(server.logfile, O_APPEND|O_CREAT|O_WRONLY, 0644);
-    if (fd == -1) return;
+    if (fd == -1) return; /* If we can't log there is anything to do. */
 
     /* Generate the stack trace */
-    trace_size = backtrace(trace, 100);
+    trace_size = backtrace(trace+1, 100);
 
-    /* overwrite sigaction with caller's address */
-    if (getMcontextEip(uc) != NULL)
-        trace[1] = getMcontextEip(uc);
+    if (getMcontextEip(uc) != NULL) {
+        char *msg1 = "EIP:\n";
+        char *msg2 = "\nBacktrace:\n";
+        if (write(fd,msg1,strlen(msg1)) == -1) {/* Avoid warning. */};
+        trace[0] = getMcontextEip(uc);
+        backtrace_symbols_fd(trace, 1, fd);
+        if (write(fd,msg2,strlen(msg2)) == -1) {/* Avoid warning. */};
+    }
 
     /* Write symbols to log file */
-    backtrace_symbols_fd(trace, trace_size, fd);
+    backtrace_symbols_fd(trace+1, trace_size, fd);
 
     /* Cleanup */
-    if (!log_to_stdout) close(fd);
+    closeDirectLogFiledes(fd);
 }
 
 /* Log information about the "current" client, that is, the client that is
  * currently being served by Redis. May be NULL if Redis is not serving a
  * client right now. */
 void logCurrentClient(void) {
     if (server.current_client == NULL) return;
 
-    redisClient *cc = server.current_client;
+    client *cc = server.current_client;
     sds client;
     int j;
 
-    redisLog(REDIS_WARNING, "--- CURRENT CLIENT INFO");
+    serverLogRaw(LL_WARNING|LL_RAW, "\n------ CURRENT CLIENT INFO ------\n");
     client = catClientInfoString(sdsempty(),cc);
-    redisLog(REDIS_WARNING,"client: %s", client);
+    serverLog(LL_WARNING|LL_RAW,"%s\n", client);
     sdsfree(client);
     for (j = 0; j < cc->argc; j++) {
         robj *decoded;
 
         decoded = getDecodedObject(cc->argv[j]);
-        redisLog(REDIS_WARNING,"argv[%d]: '%s'", j, (char*)decoded->ptr);
+        serverLog(LL_WARNING|LL_RAW,"argv[%d]: '%s'\n", j,
+            (char*)decoded->ptr);
         decrRefCount(decoded);
     }
     /* Check if the first argument, usually a key, is found inside the
      * selected DB, and if so print info about the associated object. */
     if (cc->argc >= 1) {
         robj *val, *key;
         dictEntry *de;
 
         key = getDecodedObject(cc->argv[1]);
         de = dictFind(cc->db->dict, key->ptr);
         if (de) {
             val = dictGetVal(de);
-            redisLog(REDIS_WARNING,"key '%s' found in DB containing the following object:", (char*)key->ptr);
-            redisLogObjectDebugInfo(val);
+            serverLog(LL_WARNING,"key '%s' found in DB containing the following object:", (char*)key->ptr);
+            serverLogObjectDebugInfo(val);
         }
         decrRefCount(key);
     }
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
 
         start = p;
         p = strchr(p,'-');
         if (!p) continue;
