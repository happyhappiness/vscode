@@ -230,6 +230,7 @@ int startAppendOnly(void) {
 void flushAppendOnlyFile(int force) {
     ssize_t nwritten;
     int sync_in_progress = 0;
+    mstime_t latency;
 
     if (sdslen(server.aof_buf) == 0) return;
 
@@ -266,7 +267,11 @@ void flushAppendOnlyFile(int force) {
      * While this will save us against the server being killed I don't think
      * there is much to do about the whole server stopping for power problems
      * or alike */
+    latencyStartMonitor(latency);
     nwritten = write(server.aof_fd,server.aof_buf,sdslen(server.aof_buf));
+    latencyEndMonitor(latency);
+    latencyAddSampleIfNeeded("aof-write",latency);
+
     if (nwritten != (signed)sdslen(server.aof_buf)) {
         static time_t last_write_error_log = 0;
         int can_log = 0;
@@ -360,7 +365,10 @@ void flushAppendOnlyFile(int force) {
     if (server.aof_fsync == AOF_FSYNC_ALWAYS) {
         /* aof_fsync is defined as fdatasync() for Linux in order to avoid
          * flushing metadata. */
+        latencyStartMonitor(latency);
         aof_fsync(server.aof_fd); /* Let's try to get this data on the disk */
+        latencyEndMonitor(latency);
+        latencyAddSampleIfNeeded("aof-fsync-always",latency);
         server.aof_last_fsync = server.unixtime;
     } else if ((server.aof_fsync == AOF_FSYNC_EVERYSEC &&
                 server.unixtime > server.aof_last_fsync)) {
@@ -1032,6 +1040,7 @@ int rewriteAppendOnlyFileBackground(void) {
     } else {
         /* Parent */
         server.stat_fork_time = ustime()-start;
+        latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
             redisLog(REDIS_WARNING,
                 "Can't rewrite append only file in background: fork: %s",
@@ -1081,13 +1090,17 @@ void aofRemoveTempFile(pid_t childpid) {
  * to the current length, that is much faster. */
 void aofUpdateCurrentSize(void) {
     struct redis_stat sb;
+    mstime_t latency;
 
+    latencyStartMonitor(latency);
     if (redis_fstat(server.aof_fd,&sb) == -1) {
         redisLog(REDIS_WARNING,"Unable to obtain the AOF file length. stat: %s",
             strerror(errno));
     } else {
         server.aof_current_size = sb.st_size;
     }
+    latencyEndMonitor(latency);
+    latencyAddSampleIfNeeded("aof-fstat",latency);
 }
 
 /* A background append only file rewriting (BGREWRITEAOF) terminated its work.
@@ -1097,12 +1110,14 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         int newfd, oldfd;
         char tmpfile[256];
         long long now = ustime();
+        mstime_t latency;
 
         redisLog(REDIS_NOTICE,
             "Background AOF rewrite terminated with success");
 
         /* Flush the differences accumulated by the parent to the
          * rewritten AOF. */
+        latencyStartMonitor(latency);
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof",
             (int)server.aof_child_pid);
         newfd = open(tmpfile,O_WRONLY|O_APPEND);
@@ -1118,6 +1133,8 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             close(newfd);
             goto cleanup;
         }
+        latencyEndMonitor(latency);
+        latencyAddSampleIfNeeded("aof-rewrite-diff-write",latency);
 
         redisLog(REDIS_NOTICE,
             "Parent diff successfully flushed to the rewritten AOF (%lu bytes)", aofRewriteBufferSize());
@@ -1163,13 +1180,16 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
 
         /* Rename the temporary file. This will not unlink the target file if
          * it exists, because we reference it with "oldfd". */
+        latencyStartMonitor(latency);
         if (rename(tmpfile,server.aof_filename) == -1) {
             redisLog(REDIS_WARNING,
                 "Error trying to rename the temporary AOF file: %s", strerror(errno));
             close(newfd);
             if (oldfd != -1) close(oldfd);
             goto cleanup;
         }
+        latencyEndMonitor(latency);
+        latencyAddSampleIfNeeded("aof-rename",latency);
 
         if (server.aof_fd == -1) {
             /* AOF disabled, we don't need to set the AOF file descriptor