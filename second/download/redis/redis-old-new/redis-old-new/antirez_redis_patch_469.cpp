@@ -181,12 +181,12 @@ void computeDatasetDigest(unsigned char *final) {
                     double score;
 
                     eptr = ziplistIndex(zl,0);
-                    redisAssert(eptr != NULL);
+                    serverAssert(eptr != NULL);
                     sptr = ziplistNext(zl,eptr);
-                    redisAssert(sptr != NULL);
+                    serverAssert(sptr != NULL);
 
                     while (eptr != NULL) {
-                        redisAssert(ziplistGet(eptr,&vstr,&vlen,&vll));
+                        serverAssert(ziplistGet(eptr,&vstr,&vlen,&vll));
                         score = zzlGetScore(sptr);
 
                         memset(eledigest,0,20);
@@ -267,7 +267,7 @@ void debugCommand(client *c) {
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"assert")) {
         if (c->argc >= 3) c->argv[2] = tryObjectEncoding(c->argv[2]);
-        redisAssertWithInfo(c,c->argv[0],1 == 2);
+        serverAssertWithInfo(c,c->argv[0],1 == 2);
     } else if (!strcasecmp(c->argv[1]->ptr,"reload")) {
         if (rdbSave(server.rdb_filename) != REDIS_OK) {
             addReply(c,shared.err);
@@ -470,7 +470,7 @@ void debugCommand(client *c) {
 
 /* =========================== Crash handling  ============================== */
 
-void _redisAssert(char *estr, char *file, int line) {
+void _serverAssert(char *estr, char *file, int line) {
     bugReportStart();
     serverLog(REDIS_WARNING,"=== ASSERTION FAILED ===");
     serverLog(REDIS_WARNING,"==> %s:%d '%s' is not true",file,line,estr);
@@ -483,7 +483,7 @@ void _redisAssert(char *estr, char *file, int line) {
     *((char*)-1) = 'x';
 }
 
-void _redisAssertPrintClientInfo(client *c) {
+void _serverAssertPrintClientInfo(client *c) {
     int j;
 
     bugReportStart();
@@ -531,16 +531,16 @@ void serverLogObjectDebugInfo(robj *o) {
     }
 }
 
-void _redisAssertPrintObject(robj *o) {
+void _serverAssertPrintObject(robj *o) {
     bugReportStart();
     serverLog(REDIS_WARNING,"=== ASSERTION FAILED OBJECT CONTEXT ===");
     serverLogObjectDebugInfo(o);
 }
 
-void _redisAssertWithInfo(client *c, robj *o, char *estr, char *file, int line) {
-    if (c) _redisAssertPrintClientInfo(c);
-    if (o) _redisAssertPrintObject(o);
-    _redisAssert(estr,file,line);
+void _serverAssertWithInfo(client *c, robj *o, char *estr, char *file, int line) {
+    if (c) _serverAssertPrintClientInfo(c);
+    if (o) _serverAssertPrintObject(o);
+    _serverAssert(estr,file,line);
 }
 
 void _redisPanic(char *msg, char *file, int line) {