@@ -408,6 +408,28 @@ int masterTryPartialResynchronization(redisClient *c) {
     return REDIS_ERR;
 }
 
+/* Start a BGSAVE for replication goals, which is, selecting the disk or
+ * socket target depending on the configuration, and making sure that
+ * the script cache is flushed before to start.
+ *
+ * Returns REDIS_OK on success or REDIS_ERR otherwise. */
+int startBgsaveForReplication(void) {
+    int retval;
+
+    redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC with target: %s",
+        server.repl_diskless ? "slaves sockets" : "disk");
+
+    if (server.repl_diskless)
+        retval = rdbSaveToSlavesSockets();
+    else
+        retval = rdbSaveBackground(server.rdb_filename);
+
+    /* Flush the script cache, since we need that slave differences are
+     * accumulated without requiring slaves to match our cached scripts. */
+    if (retval == REDIS_OK) replicationScriptCacheFlush();
+    return retval;
+}
+
 /* SYNC and PSYNC command implemenation. */
 void syncCommand(redisClient *c) {
     /* ignore SYNC if already slave or in monitor mode */
@@ -465,7 +487,9 @@ void syncCommand(redisClient *c) {
 
     /* Here we need to check if there is a background saving operation
      * in progress, or if it is required to start one */
-    if (server.rdb_child_pid != -1) {
+    if (server.rdb_child_pid != -1 &&
+        server.rdb_child_type == REDIS_RDB_CHILD_TYPE_DISK)
+    {
         /* Ok a background save is in progress. Let's check if it is a good
          * one for replication, i.e. if there is another slave that is
          * registering differences since the server forked to save. */
@@ -480,12 +504,7 @@ void syncCommand(redisClient *c) {
         }
         if (ln) {
             /* Perfect, the server is already registering differences for
-             * another slave. Set the right state, and copy the buffer.
-             *
-             * Note that if we found a slave in WAIT_BGSAVE_END state, this
-             * means that the current child is of type
-             * REDIS_RDB_CHILD_TYPE_DISK, since the first slave in this state
-             * can only be added when an RDB save with disk target is started. */
+             * another slave. Set the right state, and copy the buffer. */
             copyClientOutputBuffer(c,slave);
             c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
             redisLog(REDIS_NOTICE,"Waiting for end of BGSAVE for SYNC");
@@ -495,17 +514,31 @@ void syncCommand(redisClient *c) {
             c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
             redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
         }
+    } else if (server.rdb_child_pid != -1 &&
+               server.rdb_child_type == REDIS_RDB_CHILD_TYPE_SOCKET)
+    {
+        /* There is an RDB child process but it is writing directly to
+         * children sockets. We need to wait for the next BGSAVE
+         * in order to synchronize. */
+        c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
+        redisLog(REDIS_NOTICE,"Waiting for next BGSAVE for SYNC");
     } else {
-        /* Ok we don't have a BGSAVE in progress, let's start one. */
-        redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC");
-        if (rdbSaveBackground(server.rdb_filename) != REDIS_OK) {
-            redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
-            addReplyError(c,"Unable to perform background save");
-            return;
+        if (server.repl_diskless) {
+            /* Diskless replication RDB child is created inside
+             * replicationCron() since we want to delay its start a
+             * few seconds to wait for more slaves to arrive. */
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
+            redisLog(REDIS_NOTICE,"Delay next BGSAVE for SYNC");
+        } else {
+            /* Ok we don't have a BGSAVE in progress, let's start one. */
+            redisLog(REDIS_NOTICE,"Starting BGSAVE for SYNC");
+            if (startBgsaveForReplication() != REDIS_OK) {
+                redisLog(REDIS_NOTICE,"Replication failed, can't BGSAVE");
+                addReplyError(c,"Unable to perform background save");
+                return;
+            }
+            c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
         }
-        c->replstate = REDIS_REPL_WAIT_BGSAVE_END;
-        /* Flush the script cache for the new slave. */
-        replicationScriptCacheFlush();
     }
 
     if (server.repl_disable_tcp_nodelay)
@@ -644,10 +677,15 @@ void sendBulkToSlave(aeEventLoop *el, int fd, void *privdata, int mask) {
 /* This function is called at the end of every background saving.
  * The argument bgsaveerr is REDIS_OK if the background saving succeeded
  * otherwise REDIS_ERR is passed to the function.
+ * The 'type' argument is the type of the child that terminated
+ * (if it had a disk or socket target).
  *
  * The goal of this function is to handle slaves waiting for a successful
- * background saving in order to perform non-blocking synchronization. */
-void updateSlavesWaitingBgsave(int bgsaveerr) {
+ * background saving in order to perform non-blocking synchronization, and
+ * to schedule a new BGSAVE if there are slaves that attached while a
+ * BGSAVE was in progress, but it was not a good one for replication (no
+ * other slave was accumulating differences). */
+void updateSlavesWaitingBgsave(int bgsaveerr, int type) {
     listNode *ln;
     int startbgsave = 0;
     listIter li;
@@ -687,12 +725,7 @@ void updateSlavesWaitingBgsave(int bgsaveerr) {
         }
     }
     if (startbgsave) {
-        /* Since we are starting a new background save for one or more slaves,
-         * we flush the Replication Script Cache to use EVAL to propagate every
-         * new EVALSHA for the first time, since all the new slaves don't know
-         * about previous scripts. */
-        replicationScriptCacheFlush();
-        if (rdbSaveBackground(server.rdb_filename) != REDIS_OK) {
+        if (startBgsaveForReplication() != REDIS_OK) {
             listIter li;
 
             listRewind(server.slaves,&li);