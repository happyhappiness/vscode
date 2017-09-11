@@ -198,7 +198,7 @@ ssize_t aofRewriteBufferWrite(int fd) {
 /* Starts a background task that performs fsync() against the specified
  * file descriptor (the one of the AOF file) in another thread. */
 void aof_background_fsync(int fd) {
-    bioCreateBackgroundJob(REDIS_BIO_AOF_FSYNC,(void*)(long)fd,NULL,NULL);
+    bioCreateBackgroundJob(BIO_AOF_FSYNC,(void*)(long)fd,NULL,NULL);
 }
 
 /* Called when the user switches from "appendonly yes" to "appendonly no"
@@ -278,7 +278,7 @@ void flushAppendOnlyFile(int force) {
     if (sdslen(server.aof_buf) == 0) return;
 
     if (server.aof_fsync == AOF_FSYNC_EVERYSEC)
-        sync_in_progress = bioPendingJobsOfType(REDIS_BIO_AOF_FSYNC) != 0;
+        sync_in_progress = bioPendingJobsOfType(BIO_AOF_FSYNC) != 0;
 
     if (server.aof_fsync == AOF_FSYNC_EVERYSEC && !force) {
         /* With this append fsync policy we do background fsyncing.
@@ -1454,7 +1454,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             server.aof_state = AOF_ON;
 
         /* Asynchronously close the overwritten AOF. */
-        if (oldfd != -1) bioCreateBackgroundJob(REDIS_BIO_CLOSE_FILE,(void*)(long)oldfd,NULL,NULL);
+        if (oldfd != -1) bioCreateBackgroundJob(BIO_CLOSE_FILE,(void*)(long)oldfd,NULL,NULL);
 
         serverLog(LL_VERBOSE,
             "Background AOF rewrite signal handler took %lldus", ustime()-now);