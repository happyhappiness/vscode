         serverLog(LL_WARNING,"Set size: %d", (int) setTypeSize(o));
     } else if (o->type == OBJ_HASH) {
         serverLog(LL_WARNING,"Hash size: %d", (int) hashTypeLength(o));
     } else if (o->type == OBJ_ZSET) {
         serverLog(LL_WARNING,"Sorted set size: %d", (int) zsetLength(o));
         if (o->encoding == OBJ_ENCODING_SKIPLIST)
-            serverLog(LL_WARNING,"Skiplist level: %d", (int) ((zset*)o->ptr)->zsl->level);
+            serverLog(LL_WARNING,"Skiplist level: %d", (int) ((const zset*)o->ptr)->zsl->level);
     }
 }
 
-void _serverAssertPrintObject(robj *o) {
+void _serverAssertPrintObject(const robj *o) {
     bugReportStart();
     serverLog(LL_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
     serverLogObjectDebugInfo(o);
 }
 
-void _serverAssertWithInfo(client *c, robj *o, char *estr, char *file, int line) {
+void _serverAssertWithInfo(const client *c, const robj *o, const char *estr, const char *file, int line) {
     if (c) _serverAssertPrintClientInfo(c);
     if (o) _serverAssertPrintObject(o);
     _serverAssert(estr,file,line);
 }
 
-void _serverPanic(char *msg, char *file, int line) {
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
     serverLog(LL_WARNING,"------------------------------------------------");
     *((char*)-1) = 'x';
 }
