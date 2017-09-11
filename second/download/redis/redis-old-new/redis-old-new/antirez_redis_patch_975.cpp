@@ -1167,9 +1167,13 @@ int serverCron(struct aeEventLoop *eventLoop, long long id, void *clientData) {
     }
 
 
-    /* If we postponed an AOF buffer flush, let's try to do it every time the
-     * cron function is called. */
-    if (server.aof_flush_postponed_start) flushAppendOnlyFile(0);
+    /* AOF: we may have postponed buffer flush, or were not able to
+     * write our buffer because of write(2) error. Try again here. */
+    if (server.aof_flush_postponed_start ||
+        server.aof_last_write_status == REDIS_ERR)
+    {
+        flushAppendOnlyFile(0);
+    }
 
     /* Close clients that need to be closed asynchronous */
     freeClientsInAsyncFreeQueue();
@@ -1670,6 +1674,8 @@ void initServer() {
     server.unixtime = time(NULL);
     server.mstime = mstime();
     server.lastbgsave_status = REDIS_OK;
+    server.aof_last_write_status = REDIS_OK;
+    server.aof_last_write_errno = 0;
     server.repl_good_slaves_count = 0;
 
     /* Create the serverCron() time event, that's our main way to process
@@ -2035,15 +2041,22 @@ int processCommand(redisClient *c) {
 
     /* Don't accept write commands if there are problems persisting on disk
      * and if this is a master instance. */
-    if (server.stop_writes_on_bgsave_err &&
-        server.saveparamslen > 0
-        && server.lastbgsave_status == REDIS_ERR &&
+    if (((server.stop_writes_on_bgsave_err &&
+          server.saveparamslen > 0 &&
+          server.lastbgsave_status == REDIS_ERR) ||
+          server.aof_last_write_status == REDIS_ERR) &&
         server.masterhost == NULL &&
         (c->cmd->flags & REDIS_CMD_WRITE ||
          c->cmd->proc == pingCommand))
     {
         flagTransaction(c);
-        addReply(c, shared.bgsaveerr);
+        if (server.aof_last_write_status == REDIS_OK)
+            addReply(c, shared.bgsaveerr);
+        else
+            addReplySds(c,
+                sdscatprintf(sdsempty(),
+                "-MISCONF Errors writing to the AOF file: %s\r\n",
+                strerror(server.aof_last_write_errno)));
         return REDIS_OK;
     }
 
@@ -2426,7 +2439,8 @@ sds genRedisInfoString(char *section) {
             "aof_rewrite_scheduled:%d\r\n"
             "aof_last_rewrite_time_sec:%jd\r\n"
             "aof_current_rewrite_time_sec:%jd\r\n"
-            "aof_last_bgrewrite_status:%s\r\n",
+            "aof_last_bgrewrite_status:%s\r\n"
+            "aof_last_write_status:%s\r\n",
             server.loading,
             server.dirty,
             server.rdb_child_pid != -1,
@@ -2441,7 +2455,8 @@ sds genRedisInfoString(char *section) {
             (intmax_t)server.aof_rewrite_time_last,
             (intmax_t)((server.aof_child_pid == -1) ?
                 -1 : time(NULL)-server.aof_rewrite_time_start),
-            (server.aof_lastbgrewrite_status == REDIS_OK) ? "ok" : "err");
+            (server.aof_lastbgrewrite_status == REDIS_OK) ? "ok" : "err",
+            (server.aof_last_write_status == REDIS_OK) ? "ok" : "err");
 
         if (server.aof_state != REDIS_AOF_OFF) {
             info = sdscatprintf(info,