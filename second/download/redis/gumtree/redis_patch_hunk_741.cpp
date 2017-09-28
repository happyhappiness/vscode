     serverLog(LL_WARNING,"Write error saving DB on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
     return C_ERR;
 }
 
-int rdbSaveBackground(char *filename) {
+int rdbSaveBackground(char *filename, rdbSaveInfo *rsi) {
     pid_t childpid;
     long long start;
 
     if (server.aof_child_pid != -1 || server.rdb_child_pid != -1) return C_ERR;
 
     server.dirty_before_bgsave = server.dirty;
     server.lastbgsave_try = time(NULL);
+    openChildInfoPipe();
 
     start = ustime();
     if ((childpid = fork()) == 0) {
         int retval;
 
         /* Child */
         closeListeningSockets(0);
         redisSetProcTitle("redis-rdb-bgsave");
-        retval = rdbSave(filename);
+        retval = rdbSave(filename,rsi);
         if (retval == C_OK) {
-            size_t private_dirty = zmalloc_get_private_dirty();
+            size_t private_dirty = zmalloc_get_private_dirty(-1);
 
             if (private_dirty) {
                 serverLog(LL_NOTICE,
                     "RDB: %zu MB of memory used by copy-on-write",
                     private_dirty/(1024*1024));
             }
+
+            server.child_info_data.cow_size = private_dirty;
+            sendChildInfo(CHILD_INFO_TYPE_RDB);
         }
         exitFromChild((retval == C_OK) ? 0 : 1);
     } else {
         /* Parent */
         server.stat_fork_time = ustime()-start;
         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
+            closeChildInfoPipe();
             server.lastbgsave_status = C_ERR;
             serverLog(LL_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));
             return C_ERR;
         }
         serverLog(LL_NOTICE,"Background saving started by pid %d",childpid);
