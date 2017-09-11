@@ -144,7 +144,7 @@ void flushAppendOnlyFile(int force) {
     /* Don't fsync if no-appendfsync-on-rewrite is set to yes and there are
      * children doing I/O in the background. */
     if (server.aof_no_fsync_on_rewrite &&
-        (server.aof_child_pid != -1 || server.bgsavechildpid != -1))
+        (server.aof_child_pid != -1 || server.rdb_child_pid != -1))
             return;
 
     /* Perform the fsync if needed. */
@@ -815,7 +815,7 @@ int rewriteAppendOnlyFileBackground(void) {
 void bgrewriteaofCommand(redisClient *c) {
     if (server.aof_child_pid != -1) {
         addReplyError(c,"Background append only file rewriting already in progress");
-    } else if (server.bgsavechildpid != -1) {
+    } else if (server.rdb_child_pid != -1) {
         server.aof_rewrite_scheduled = 1;
         addReplyStatus(c,"Background append only file rewriting scheduled");
     } else if (rewriteAppendOnlyFileBackground() == REDIS_OK) {