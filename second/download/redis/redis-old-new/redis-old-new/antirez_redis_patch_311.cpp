@@ -575,8 +575,8 @@ void _serverPanic(char *msg, char *file, int line) {
 
 void bugReportStart(void) {
     if (server.bug_report_start == 0) {
-        serverLog(LL_WARNING,
-            "\n\n=== REDIS BUG REPORT START: Cut & paste starting from here ===");
+        serverLogRaw(LL_WARNING|LL_RAW,
+        "\n\n=== REDIS BUG REPORT START: Cut & paste starting from here ===\n");
         server.bug_report_start = 1;
     }
 }
@@ -627,7 +627,7 @@ void logStackContent(void **sp) {
 }
 
 void logRegisters(ucontext_t *uc) {
-    serverLog(LL_WARNING, "--- REGISTERS");
+    serverLog(LL_WARNING|LL_RAW, "\n------ REGISTERS ------\n");
 
 /* OSX */
 #if defined(__APPLE__) && defined(MAC_OS_X_VERSION_10_6)
@@ -758,7 +758,7 @@ void logRegisters(ucontext_t *uc) {
 /* Logs the stack trace using the backtrace() call. This function is designed
  * to be called from signal handlers safely. */
 void logStackTrace(ucontext_t *uc) {
-    void *trace[100];
+    void *trace[101];
     int trace_size = 0, fd;
     int log_to_stdout = server.logfile[0] == '\0';
 
@@ -769,14 +769,19 @@ void logStackTrace(ucontext_t *uc) {
     if (fd == -1) return;
 
     /* Generate the stack trace */
-    trace_size = backtrace(trace, 100);
-
-    /* overwrite sigaction with caller's address */
-    if (getMcontextEip(uc) != NULL)
-        trace[1] = getMcontextEip(uc);
+    trace_size = backtrace(trace+1, 100);
+
+    if (getMcontextEip(uc) != NULL) {
+        char *msg1 = "EIP:\n";
+        char *msg2 = "\nBacktrace:\n";
+        write(fd,msg1,strlen(msg1));
+        trace[0] = getMcontextEip(uc);
+        backtrace_symbols_fd(trace, 1, fd);
+        write(fd,msg2,strlen(msg2));
+    }
 
     /* Write symbols to log file */
-    backtrace_symbols_fd(trace, trace_size, fd);
+    backtrace_symbols_fd(trace+1, trace_size, fd);
 
     /* Cleanup */
     if (!log_to_stdout) close(fd);
@@ -792,15 +797,16 @@ void logCurrentClient(void) {
     sds client;
     int j;
 
-    serverLog(LL_WARNING, "--- CURRENT CLIENT INFO");
+    serverLogRaw(LL_WARNING|LL_RAW, "\n------ CURRENT CLIENT INFO ------\n");
     client = catClientInfoString(sdsempty(),cc);
-    serverLog(LL_WARNING,"client: %s", client);
+    serverLog(LL_WARNING|LL_RAW,"%s\n", client);
     sdsfree(client);
     for (j = 0; j < cc->argc; j++) {
         robj *decoded;
 
         decoded = getDecodedObject(cc->argv[j]);
-        serverLog(LL_WARNING,"argv[%d]: '%s'", j, (char*)decoded->ptr);
+        serverLog(LL_WARNING|LL_RAW,"argv[%d]: '%s'\n", j,
+            (char*)decoded->ptr);
         decrRefCount(decoded);
     }
     /* Check if the first argument, usually a key, is found inside the
@@ -905,34 +911,39 @@ int memtest_test_linux_anonymous_maps(void) {
 
 void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
     ucontext_t *uc = (ucontext_t*) secret;
+    void *eip = getMcontextEip(uc);
     sds infostring, clients;
     struct sigaction act;
     UNUSED(info);
 
     bugReportStart();
     serverLog(LL_WARNING,
-        "    Redis %s crashed by signal: %d", REDIS_VERSION, sig);
-    if (sig == SIGSEGV) {
+        "Redis %s crashed by signal: %d", REDIS_VERSION, sig);
+    if (eip != NULL) {
         serverLog(LL_WARNING,
-        "    SIGSEGV caused by address: %p", (void*)info->si_addr);
+        "Crashed running the instuction at: %p", eip);
+    }
+    if (sig == SIGSEGV || sig == SIGBUS) {
+        serverLog(LL_WARNING,
+        "Accessing address: %p", (void*)info->si_addr);
     }
     serverLog(LL_WARNING,
-        "    Failed assertion: %s (%s:%d)", server.assert_failed,
+        "Failed assertion: %s (%s:%d)", server.assert_failed,
                         server.assert_file, server.assert_line);
 
     /* Log the stack trace */
-    serverLog(LL_WARNING, "--- STACK TRACE");
+    serverLogRaw(LL_WARNING|LL_RAW, "\n------ STACK TRACE ------\n");
     logStackTrace(uc);
 
     /* Log INFO and CLIENT LIST */
-    serverLog(LL_WARNING, "--- INFO OUTPUT");
+    serverLogRaw(LL_WARNING|LL_RAW, "\n------ INFO OUTPUT ------\n");
     infostring = genRedisInfoString("all");
     infostring = sdscatprintf(infostring, "hash_init_value: %u\n",
         dictGetHashFunctionSeed());
-    serverLogRaw(LL_WARNING, infostring);
-    serverLog(LL_WARNING, "--- CLIENT LIST OUTPUT");
+    serverLogRaw(LL_WARNING|LL_RAW, infostring);
+    serverLogRaw(LL_WARNING|LL_RAW, "\n------ CLIENT LIST OUTPUT ------\n");
     clients = getAllClientsInfoString();
-    serverLogRaw(LL_WARNING, clients);
+    serverLogRaw(LL_WARNING|LL_RAW, clients);
     sdsfree(infostring);
     sdsfree(clients);
 
@@ -944,7 +955,7 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
 
 #if defined(HAVE_PROC_MAPS)
     /* Test memory */
-    serverLog(LL_WARNING, "--- FAST MEMORY TEST");
+    serverLogRaw(LL_WARNING|LL_RAW, "\n------ FAST MEMORY TEST ------\n");
     bioKillThreads();
     if (memtest_test_linux_anonymous_maps()) {
         serverLog(LL_WARNING,
@@ -955,7 +966,7 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
     }
 #endif
 
-    serverLog(LL_WARNING,
+    serverLogRaw(LL_WARNING|LL_RAW,
 "\n=== REDIS BUG REPORT END. Make sure to include from START to END. ===\n\n"
 "       Please report the crash by opening an issue on github:\n\n"
 "           http://github.com/antirez/redis/issues\n\n"