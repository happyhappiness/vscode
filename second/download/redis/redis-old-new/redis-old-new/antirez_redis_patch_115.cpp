@@ -1319,6 +1319,7 @@ int rewriteAppendOnlyFileBackground(void) {
 
     if (server.aof_child_pid != -1 || server.rdb_child_pid != -1) return C_ERR;
     if (aofCreatePipes() != C_OK) return C_ERR;
+    openChildInfoPipe();
     start = ustime();
     if ((childpid = fork()) == 0) {
         char tmpfile[256];
@@ -1335,6 +1336,9 @@ int rewriteAppendOnlyFileBackground(void) {
                     "AOF rewrite: %zu MB of memory used by copy-on-write",
                     private_dirty/(1024*1024));
             }
+
+            server.child_info_data.cow_size = private_dirty;
+            sendChildInfo(CHILD_INFO_TYPE_AOF);
             exitFromChild(0);
         } else {
             exitFromChild(1);
@@ -1345,6 +1349,7 @@ int rewriteAppendOnlyFileBackground(void) {
         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
+            closeChildInfoPipe();
             serverLog(LL_WARNING,
                 "Can't rewrite append only file in background: fork: %s",
                 strerror(errno));