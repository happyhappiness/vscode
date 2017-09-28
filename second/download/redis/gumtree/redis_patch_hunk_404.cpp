     } else {
         /* Parent */
         server.stat_fork_time = ustime()-start;
         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
-            redisLog(REDIS_WARNING,
+            serverLog(LL_WARNING,
                 "Can't rewrite append only file in background: fork: %s",
                 strerror(errno));
-            return REDIS_ERR;
+            return C_ERR;
         }
-        redisLog(REDIS_NOTICE,
+        serverLog(LL_NOTICE,
             "Background append only file rewriting started by pid %d",childpid);
         server.aof_rewrite_scheduled = 0;
         server.aof_rewrite_time_start = time(NULL);
         server.aof_child_pid = childpid;
         updateDictResizePolicy();
         /* We set appendseldb to -1 in order to force the next call to the
          * feedAppendOnlyFile() to issue a SELECT command, so the differences
          * accumulated by the parent into server.aof_rewrite_buf will start
          * with a SELECT statement and it will be safe to merge. */
         server.aof_selected_db = -1;
         replicationScriptCacheFlush();
-        return REDIS_OK;
+        return C_OK;
     }
-    return REDIS_OK; /* unreached */
+    return C_OK; /* unreached */
 }
 
-void bgrewriteaofCommand(redisClient *c) {
+void bgrewriteaofCommand(client *c) {
     if (server.aof_child_pid != -1) {
         addReplyError(c,"Background append only file rewriting already in progress");
     } else if (server.rdb_child_pid != -1) {
         server.aof_rewrite_scheduled = 1;
         addReplyStatus(c,"Background append only file rewriting scheduled");
-    } else if (rewriteAppendOnlyFileBackground() == REDIS_OK) {
+    } else if (rewriteAppendOnlyFileBackground() == C_OK) {
         addReplyStatus(c,"Background append only file rewriting started");
     } else {
         addReply(c,shared.err);
     }
 }
 
