@@ -559,10 +559,11 @@ void logRegisters(ucontext_t *uc) {
 }
 
 /* Logs the stack trace using the backtrace() call. */
-void logStackTrace(ucontext_t *uc) {
+sds getStackTrace(ucontext_t *uc) {
     void *trace[100];
     int i, trace_size = 0;
     char **messages = NULL;
+    sds st = sdsempty();
 
     /* Generate the stack trace */
     trace_size = backtrace(trace, 100);
@@ -572,9 +573,12 @@ void logStackTrace(ucontext_t *uc) {
         trace[1] = getMcontextEip(uc);
     }
     messages = backtrace_symbols(trace, trace_size);
-    redisLog(REDIS_WARNING, "--- STACK TRACE");
-    for (i=1; i<trace_size; ++i)
-        redisLog(REDIS_WARNING,"%s", messages[i]);
+    for (i=1; i<trace_size; ++i) {
+        st = sdscat(st,messages[i]);
+        st = sdscatlen(st,"\n",1);
+    }
+    zlibc_free(messages);
+    return st;
 }
 
 /* Log information about the "current" client, that is, the client that is
@@ -617,7 +621,7 @@ void logCurrentClient(void) {
 
 void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
     ucontext_t *uc = (ucontext_t*) secret;
-    sds infostring, clients;
+    sds infostring, clients, st;
     struct sigaction act;
     REDIS_NOTUSED(info);
 
@@ -629,7 +633,9 @@ void sigsegvHandler(int sig, siginfo_t *info, void *secret) {
                         server.assert_file, server.assert_line);
 
     /* Log the stack trace */
-    logStackTrace(uc);
+    st = getStackTrace(uc);
+    redisLog(REDIS_WARNING, "--- STACK TRACE\n%s", st);
+    sdsfree(st);
 
     /* Log INFO and CLIENT LIST */
     redisLog(REDIS_WARNING, "--- INFO OUTPUT");
@@ -675,13 +681,28 @@ void watchdogSignalHandler(int sig, siginfo_t *info, void *secret) {
     ucontext_t *uc = (ucontext_t*) secret;
     REDIS_NOTUSED(info);
     REDIS_NOTUSED(sig);
+    sds st, log;
+    time_t now = time(NULL);
+    char date[128];
+    FILE *fp;
 
-    /* Log INFO and CLIENT LIST */
-    redisLog(REDIS_WARNING, "--- WATCHDOG TIMER EXPIRED ---"); 
+    fp = (server.logfile == NULL) ? stdout : fopen(server.logfile,"a");
+    if (fp == NULL) return;
+
+    strftime(date,sizeof(date),"%d %b %H:%M:%S",localtime(&now));
+    log = sdscatprintf(sdsempty(),
+        "\n--- WATCHDOG TIMER EXPIRED (%s) ---\n",date); 
 #ifdef HAVE_BACKTRACE
-    logStackTrace(uc);
-    redisLog(REDIS_WARNING, "------");
+    st = getStackTrace(uc);
+#else
+    st = sdsnew("Sorry: no support for backtrace().\n");
 #endif
+    log = sdscatsds(log,st);
+    log = sdscat(log,"------\n\n");
+    fprintf(fp,"%s",log);
+    if (server.logfile) fclose(fp);
+    sdsfree(st);
+    sdsfree(log);
 }
 
 /* Schedule a SIGALRM delivery after the specified period in milliseconds.