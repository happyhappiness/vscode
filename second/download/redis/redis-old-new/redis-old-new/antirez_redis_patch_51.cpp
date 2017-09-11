@@ -266,6 +266,8 @@ void debugCommand(client *c) {
         blen++; addReplyStatus(c,
         "segfault -- Crash the server with sigsegv.");
         blen++; addReplyStatus(c,
+        "panic -- Crash the server simulating a panic.");
+        blen++; addReplyStatus(c,
         "restart  -- Graceful restart: save config, db, restart.");
         blen++; addReplyStatus(c,
         "crash-and-recovery <milliseconds> -- Hard crash and restart after <milliseconds> delay.");
@@ -300,6 +302,8 @@ void debugCommand(client *c) {
         setDeferredMultiBulkLength(c,blenp,blen);
     } else if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
         *((char*)-1) = 'x';
+    } else if (!strcasecmp(c->argv[1]->ptr,"panic")) {
+        serverPanic("DEBUG PANIC called at Unix time %ld", time(NULL));
     } else if (!strcasecmp(c->argv[1]->ptr,"restart") ||
                !strcasecmp(c->argv[1]->ptr,"crash-and-recover"))
     {
@@ -615,11 +619,17 @@ void _serverAssertWithInfo(const client *c, const robj *o, const char *estr, con
     _serverAssert(estr,file,line);
 }
 
-void _serverPanic(const char *msg, const char *file, int line) {
+void _serverPanic(const char *file, int line, const char *msg, ...) {
+    va_list ap;
+    va_start(ap,msg);
+    char fmtmsg[256];
+    vsnprintf(fmtmsg,sizeof(fmtmsg),msg,ap);
+    va_end(ap);
+
     bugReportStart();
     serverLog(LL_WARNING,"------------------------------------------------");
     serverLog(LL_WARNING,"!!! Software Failure. Press left mouse button to continue");
-    serverLog(LL_WARNING,"Guru Meditation: %s #%s:%d",msg,file,line);
+    serverLog(LL_WARNING,"Guru Meditation: %s #%s:%d",fmtmsg,file,line);
 #ifdef HAVE_BACKTRACE
     serverLog(LL_WARNING,"(forcing SIGSEGV in order to print the stack trace)");
 #endif