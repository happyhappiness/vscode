@@ -1870,9 +1870,6 @@ int rdbSaveToSlavesSockets(rdbSaveInfo *rsi) {
         exitFromChild((retval == C_OK) ? 0 : 1);
     } else {
         /* Parent */
-        server.stat_fork_time = ustime()-start;
-        server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
-        latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
             serverLog(LL_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));
@@ -1896,6 +1893,10 @@ int rdbSaveToSlavesSockets(rdbSaveInfo *rsi) {
             close(pipefds[1]);
             closeChildInfoPipe();
         } else {
+            server.stat_fork_time = ustime()-start;
+            server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
+            latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
+
             serverLog(LL_NOTICE,"Background RDB transfer started by pid %d",
                 childpid);
             server.rdb_save_time_start = time(NULL);