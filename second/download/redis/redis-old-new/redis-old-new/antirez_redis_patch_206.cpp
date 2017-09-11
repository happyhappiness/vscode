@@ -550,7 +550,7 @@ void debugCommand(client *c) {
 
 /* =========================== Crash handling  ============================== */
 
-void _serverAssert(char *estr, char *file, int line) {
+void _serverAssert(const char *estr, const char *file, int line) {
     bugReportStart();
     serverLog(LL_WARNING,"=== ASSERTION FAILED ===");
     serverLog(LL_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
@@ -563,7 +563,7 @@ void _serverAssert(char *estr, char *file, int line) {
     *((char*)-1) = 'x';
 }
 
-void _serverAssertPrintClientInfo(client *c) {
+void _serverAssertPrintClientInfo(const client *c) {
     int j;
 
     bugReportStart();
@@ -587,7 +587,7 @@ void _serverAssertPrintClientInfo(client *c) {
     }
 }
 
-void serverLogObjectDebugInfo(robj *o) {
+void serverLogObjectDebugInfo(const robj *o) {
     serverLog(LL_WARNING,"Object type: %d", o->type);
     serverLog(LL_WARNING,"Object encoding: %d", o->encoding);
     serverLog(LL_WARNING,"Object refcount: %d", o->refcount);
@@ -607,23 +607,23 @@ void serverLogObjectDebugInfo(robj *o) {
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
+void _serverPanic(const char *msg, const char *file, int line) {
     bugReportStart();
     serverLog(LL_WARNING,"------------------------------------------------");
     serverLog(LL_WARNING,"!!! Software Failure. Press left mouse button to continue");