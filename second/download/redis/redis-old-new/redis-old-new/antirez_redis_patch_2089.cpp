@@ -8724,6 +8724,47 @@ static void aofRemoveTempFile(pid_t childpid) {
  * as a fully non-blocking VM.
  */
 
+/* Called when the user switches from "appendonly yes" to "appendonly no"
+ * at runtime using the CONFIG command. */
+static void stopAppendOnly(void) {
+    flushAppendOnlyFile();
+    fsync(server.appendfd);
+    close(server.appendfd);
+
+    server.appendfd = -1;
+    server.appendseldb = -1;
+    server.appendonly = 0;
+    /* rewrite operation in progress? kill it, wait child exit */
+    if (server.bgsavechildpid != -1) {
+        int statloc;
+
+        kill(server.bgsavechildpid,SIGKILL);
+        wait3(&statloc,0,NULL);
+        /* reset the buffer accumulating changes while the child saves */
+        sdsfree(server.bgrewritebuf);
+        server.bgrewritebuf = sdsempty();
+    }
+}
+
+/* Called when the user switches from "appendonly no" to "appendonly yes"
+ * at runtime using the CONFIG command. */
+static int startAppendOnly(void) {
+    server.appendonly = 1;
+    server.lastfsync = time(NULL);
+    server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
+    if (server.appendfd == -1) {
+        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, but I can't open the AOF file: %s",strerror(errno));
+        return REDIS_ERR;
+    }
+    if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
+        server.appendonly = 0;
+        close(server.appendfd);
+        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, I can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.",strerror(errno));
+        return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
+
 /* =================== Virtual Memory - Blocking Side  ====================== */
 
 static void vmInit(void) {
@@ -9826,6 +9867,8 @@ static void handleClientsBlockedOnSwappedKey(redisDb *db, robj *key) {
 
 static void configSetCommand(redisClient *c) {
     robj *o = getDecodedObject(c->argv[3]);
+    long long ll;
+
     if (!strcasecmp(c->argv[2]->ptr,"dbfilename")) {
         zfree(server.dbfilename);
         server.dbfilename = zstrdup(o->ptr);
@@ -9836,7 +9879,13 @@ static void configSetCommand(redisClient *c) {
         zfree(server.masterauth);
         server.masterauth = zstrdup(o->ptr);
     } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory")) {
-        server.maxmemory = strtoll(o->ptr, NULL, 10);
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll < 0) goto badfmt;
+        server.maxmemory = ll;
+    } else if (!strcasecmp(c->argv[2]->ptr,"timeout")) {
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
+            ll < 0 || ll > LONG_MAX) goto badfmt;
+        server.maxidletime = ll;
     } else if (!strcasecmp(c->argv[2]->ptr,"appendfsync")) {
         if (!strcasecmp(o->ptr,"no")) {
             server.appendfsync = APPENDFSYNC_NO;
@@ -9847,6 +9896,23 @@ static void configSetCommand(redisClient *c) {
         } else {
             goto badfmt;
         }
+    } else if (!strcasecmp(c->argv[2]->ptr,"appendonly")) {
+        int old = server.appendonly;
+        int new = yesnotoi(o->ptr);
+
+        if (new == -1) goto badfmt;
+        if (old != new) {
+            if (new == 0) {
+                stopAppendOnly();
+            } else {
+                if (startAppendOnly() == REDIS_ERR) {
+                    addReplySds(c,sdscatprintf(sdsempty(),
+                        "-ERR Unable to turn on AOF. Check server logs.\r\n"));
+                    decrRefCount(o);
+                    return;
+                }
+            }
+        }
     } else if (!strcasecmp(c->argv[2]->ptr,"save")) {
         int vlen, j;
         sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);
@@ -9927,11 +9993,24 @@ static void configGetCommand(redisClient *c) {
     if (stringmatch(pattern,"maxmemory",0)) {
         char buf[128];
 
-        snprintf(buf,128,"%llu\n",server.maxmemory);
+        ll2string(buf,128,server.maxmemory);
         addReplyBulkCString(c,"maxmemory");
         addReplyBulkCString(c,buf);
         matches++;
     }
+    if (stringmatch(pattern,"timeout",0)) {
+        char buf[128];
+
+        ll2string(buf,128,server.maxidletime);
+        addReplyBulkCString(c,"timeout");
+        addReplyBulkCString(c,buf);
+        matches++;
+    }
+    if (stringmatch(pattern,"appendonly",0)) {
+        addReplyBulkCString(c,"appendonly");
+        addReplyBulkCString(c,server.appendonly ? "yes" : "no");
+        matches++;
+    }
     if (stringmatch(pattern,"appendfsync",0)) {
         char *policy;
 