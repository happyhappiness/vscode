@@ -370,6 +370,7 @@ struct redisServer {
     pid_t bgsavechildpid;
     pid_t bgrewritechildpid;
     sds bgrewritebuf; /* buffer taken by parent during oppend only rewrite */
+    sds aofbuf;       /* AOF buffer, written before entering the event loop */
     struct saveparam *saveparams;
     int saveparamslen;
     char *logfile;
@@ -557,6 +558,7 @@ static robj *createStringObject(char *ptr, size_t len);
 static robj *dupStringObject(robj *o);
 static void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc);
 static void replicationFeedMonitors(list *monitors, int dictid, robj **argv, int argc);
+static void flushAppendOnlyFile(void);
 static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc);
 static int syncWithMaster(void);
 static robj *tryObjectEncoding(robj *o);
@@ -1528,6 +1530,7 @@ static int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientD
 static void beforeSleep(struct aeEventLoop *eventLoop) {
     REDIS_NOTUSED(eventLoop);
 
+    /* Awake clients that got all the swapped keys they requested */
     if (server.vm_enabled && listLength(server.io_ready_clients)) {
         listIter li;
         listNode *ln;
@@ -1552,6 +1555,8 @@ static void beforeSleep(struct aeEventLoop *eventLoop) {
                 processInputBuffer(c);
         }
     }
+    /* Write the AOF buffer on disk */
+    flushAppendOnlyFile();
 }
 
 static void createSharedObjects(void) {
@@ -1712,6 +1717,7 @@ static void initServer() {
     server.bgsavechildpid = -1;
     server.bgrewritechildpid = -1;
     server.bgrewritebuf = sdsempty();
+    server.aofbuf = sdsempty();
     server.lastsave = time(NULL);
     server.dirty = 0;
     server.stat_numcommands = 0;
@@ -8008,11 +8014,55 @@ static void freeMemoryIfNeeded(void) {
 
 /* ============================== Append Only file ========================== */
 
+/* Write the append only file buffer on disk.
+ *
+ * Since we are required to write the AOF before replying to the client,
+ * and the only way the client socket can get a write is entering when the
+ * the event loop, we accumulate all the AOF writes in a memory
+ * buffer and write it on disk using this function just before entering
+ * the event loop again. */
+static void flushAppendOnlyFile(void) {
+    time_t now;
+    ssize_t nwritten;
+
+    if (sdslen(server.aofbuf) == 0) return;
+
+    /* We want to perform a single write. This should be guaranteed atomic
+     * at least if the filesystem we are writing is a real physical one.
+     * While this will save us against the server being killed I don't think
+     * there is much to do about the whole server stopping for power problems
+     * or alike */
+     nwritten = write(server.appendfd,server.aofbuf,sdslen(server.aofbuf));
+     if (nwritten != (signed)sdslen(server.aofbuf)) {
+        /* Ooops, we are in troubles. The best thing to do for now is
+         * aborting instead of giving the illusion that everything is
+         * working as expected. */
+         if (nwritten == -1) {
+            redisLog(REDIS_WARNING,"Exiting on error writing to the append-only file: %s",strerror(errno));
+         } else {
+            redisLog(REDIS_WARNING,"Exiting on short write while writing to the append-only file: %s",strerror(errno));
+         }
+         exit(1);
+    }
+    sdsfree(server.aofbuf);
+    server.aofbuf = sdsempty();
+
+    /* Fsync if needed */
+    now = time(NULL);
+    if (server.appendfsync == APPENDFSYNC_ALWAYS ||
+        (server.appendfsync == APPENDFSYNC_EVERYSEC &&
+         now-server.lastfsync > 1))
+    {
+        /* aof_fsync is defined as fdatasync() for Linux in order to avoid
+         * flushing metadata. */
+        aof_fsync(server.appendfd); /* Let's try to get this data on the disk */
+        server.lastfsync = now;
+    }
+}
+
 static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc) {
     sds buf = sdsempty();
     int j;
-    ssize_t nwritten;
-    time_t now;
     robj *tmpargv[3];
 
     /* The DB this command was targetting is not the same as the last command
@@ -8058,23 +8108,11 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
             decrRefCount(argv[j]);
     }
 
-    /* We want to perform a single write. This should be guaranteed atomic
-     * at least if the filesystem we are writing is a real physical one.
-     * While this will save us against the server being killed I don't think
-     * there is much to do about the whole server stopping for power problems
-     * or alike */
-     nwritten = write(server.appendfd,buf,sdslen(buf));
-     if (nwritten != (signed)sdslen(buf)) {
-        /* Ooops, we are in troubles. The best thing to do for now is
-         * to simply exit instead to give the illusion that everything is
-         * working as expected. */
-         if (nwritten == -1) {
-            redisLog(REDIS_WARNING,"Exiting on error writing to the append-only file: %s",strerror(errno));
-         } else {
-            redisLog(REDIS_WARNING,"Exiting on short write while writing to the append-only file: %s",strerror(errno));
-         }
-         exit(1);
-    }
+    /* Append to the AOF buffer. This will be flushed on disk just before
+     * of re-entering the event loop, so before the client will get a
+     * positive reply about the operation performed. */
+    server.aofbuf = sdscatlen(server.aofbuf,buf,sdslen(buf));
+
     /* If a background append only file rewriting is in progress we want to
      * accumulate the differences between the child DB and the current one
      * in a buffer, so that when the child process will do its work we
@@ -8083,16 +8121,6 @@ static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv
         server.bgrewritebuf = sdscatlen(server.bgrewritebuf,buf,sdslen(buf));
 
     sdsfree(buf);
-    now = time(NULL);
-    if (server.appendfsync == APPENDFSYNC_ALWAYS ||
-        (server.appendfsync == APPENDFSYNC_EVERYSEC &&
-         now-server.lastfsync > 1))
-    {
-        /* aof_fsync is defined as fdatasync() for Linux in order to avoid
-         * flushing metadata. */
-        aof_fsync(server.appendfd); /* Let's try to get this data on the disk */
-        server.lastfsync = now;
-    }
 }
 
 /* In Redis commands are always executed in the context of a client, so in