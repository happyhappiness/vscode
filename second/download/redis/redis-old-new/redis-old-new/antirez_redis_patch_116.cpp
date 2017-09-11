@@ -1014,6 +1014,7 @@ int rdbSaveBackground(char *filename) {
 
     server.dirty_before_bgsave = server.dirty;
     server.lastbgsave_try = time(NULL);
+    openChildInfoPipe();
 
     start = ustime();
     if ((childpid = fork()) == 0) {
@@ -1031,6 +1032,9 @@ int rdbSaveBackground(char *filename) {
                     "RDB: %zu MB of memory used by copy-on-write",
                     private_dirty/(1024*1024));
             }
+
+            server.child_info_data.cow_size = private_dirty;
+            sendChildInfo(CHILD_INFO_TYPE_RDB);
         }
         exitFromChild((retval == C_OK) ? 0 : 1);
     } else {
@@ -1039,6 +1043,7 @@ int rdbSaveBackground(char *filename) {
         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
+            closeChildInfoPipe();
             server.lastbgsave_status = C_ERR;
             serverLog(LL_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));
@@ -1744,6 +1749,7 @@ int rdbSaveToSlavesSockets(void) {
     }
 
     /* Create the child process. */
+    openChildInfoPipe();
     start = ustime();
     if ((childpid = fork()) == 0) {
         /* Child */
@@ -1769,6 +1775,9 @@ int rdbSaveToSlavesSockets(void) {
                     private_dirty/(1024*1024));
             }
 
+            server.child_info_data.cow_size = private_dirty;
+            sendChildInfo(CHILD_INFO_TYPE_RDB);
+
             /* If we are returning OK, at least one slave was served
              * with the RDB file as expected, so we need to send a report
              * to the parent via the pipe. The format of the message is:
@@ -1837,6 +1846,7 @@ int rdbSaveToSlavesSockets(void) {
             }
             close(pipefds[0]);
             close(pipefds[1]);
+            closeChildInfoPipe();
         } else {
             serverLog(LL_NOTICE,"Background RDB transfer started by pid %d",
                 childpid);