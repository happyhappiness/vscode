@@ -212,6 +212,9 @@ void computeDatasetDigest(unsigned char *final) {
 void debugCommand(redisClient *c) {
     if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
         *((char*)-1) = 'x';
+    } else if (!strcasecmp(c->argv[1]->ptr,"assert")) {
+        if (c->argc >= 3) c->argv[2] = tryObjectEncoding(c->argv[2]);
+        redisAssertWithClientInfo(c,1 == 2);
     } else if (!strcasecmp(c->argv[1]->ptr,"reload")) {
         if (rdbSave(server.dbfilename) != REDIS_OK) {
             addReply(c,shared.err);
@@ -302,6 +305,38 @@ void _redisAssert(char *estr, char *file, int line) {
 #endif
 }
 
+void _redisAssertPrintClientInfo(redisClient *c) {
+    if (c) {
+        int j;
+
+        redisLog(REDIS_WARNING,"=== ASSERTION FAILED CLIENT CONTEXT ===");
+        redisLog(REDIS_WARNING,"client->flags = %d", c->flags);
+        redisLog(REDIS_WARNING,"client->fd = %d", c->fd);
+        redisLog(REDIS_WARNING,"client->argc = %d", c->argc);
+        for (j=0; j < c->argc; j++) {
+            char buf[128];
+            char *arg;
+
+            if (c->argv[j]->type == REDIS_STRING &&
+                c->argv[j]->encoding == REDIS_ENCODING_RAW)
+            {
+                arg = (char*) c->argv[j]->ptr;
+            } else {
+                snprintf(buf,sizeof(buf),"Object type: %d, encoding: %d",
+                    c->argv[j]->type, c->argv[j]->encoding);
+                arg = buf;
+            }
+            redisLog(REDIS_WARNING,"client->argv[%d] = \"%s\" (refcount: %d)",
+                j, arg, c->argv[j]->refcount);
+        }
+    }
+}
+
+void _redisAssertWithClientInfo(redisClient *c, char *estr, char *file, int line) {
+    _redisAssertPrintClientInfo(c);
+    _redisAssert(estr,file,line);
+}
+
 void _redisPanic(char *msg, char *file, int line) {
     redisLog(REDIS_WARNING,"------------------------------------------------");
     redisLog(REDIS_WARNING,"!!! Software Failure. Press left mouse button to continue");