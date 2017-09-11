@@ -21,38 +21,38 @@ void aof_background_fsync(int fd) {
 void stopAppendOnly(void) {
     redisAssert(server.aof_state != REDIS_AOF_OFF);
     flushAppendOnlyFile(1);
-    aof_fsync(server.appendfd);
-    close(server.appendfd);
+    aof_fsync(server.aof_fd);
+    close(server.aof_fd);
 
-    server.appendfd = -1;
-    server.appendseldb = -1;
+    server.aof_fd = -1;
+    server.aof_selected_db = -1;
     server.aof_state = REDIS_AOF_OFF;
     /* rewrite operation in progress? kill it, wait child exit */
-    if (server.bgrewritechildpid != -1) {
+    if (server.aof_child_pid != -1) {
         int statloc;
 
-        if (kill(server.bgrewritechildpid,SIGKILL) != -1)
+        if (kill(server.aof_child_pid,SIGKILL) != -1)
             wait3(&statloc,0,NULL);
         /* reset the buffer accumulating changes while the child saves */
-        sdsfree(server.bgrewritebuf);
-        server.bgrewritebuf = sdsempty();
-        aofRemoveTempFile(server.bgrewritechildpid);
-        server.bgrewritechildpid = -1;
+        sdsfree(server.aof_rewrite_buf);
+        server.aof_rewrite_buf = sdsempty();
+        aofRemoveTempFile(server.aof_child_pid);
+        server.aof_child_pid = -1;
     }
 }
 
 /* Called when the user switches from "appendonly no" to "appendonly yes"
  * at runtime using the CONFIG command. */
 int startAppendOnly(void) {
-    server.lastfsync = time(NULL);
-    server.appendfd = open(server.aof_filename,O_WRONLY|O_APPEND|O_CREAT,0644);
+    server.aof_last_fsync = time(NULL);
+    server.aof_fd = open(server.aof_filename,O_WRONLY|O_APPEND|O_CREAT,0644);
     redisAssert(server.aof_state == REDIS_AOF_OFF);
-    if (server.appendfd == -1) {
+    if (server.aof_fd == -1) {
         redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
         return REDIS_ERR;
     }
     if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
-        close(server.appendfd);
+        close(server.aof_fd);
         redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
         return REDIS_ERR;
     }
@@ -84,7 +84,7 @@ void flushAppendOnlyFile(int force) {
     ssize_t nwritten;
     int sync_in_progress = 0;
 
-    if (sdslen(server.aofbuf) == 0) return;
+    if (sdslen(server.aof_buf) == 0) return;
 
     if (server.aof_fsync == AOF_FSYNC_EVERYSEC)
         sync_in_progress = bioPendingJobsOfType(REDIS_BIO_AOF_FSYNC) != 0;
@@ -118,8 +118,8 @@ void flushAppendOnlyFile(int force) {
      * While this will save us against the server being killed I don't think
      * there is much to do about the whole server stopping for power problems
      * or alike */
-    nwritten = write(server.appendfd,server.aofbuf,sdslen(server.aofbuf));
-    if (nwritten != (signed)sdslen(server.aofbuf)) {
+    nwritten = write(server.aof_fd,server.aof_buf,sdslen(server.aof_buf));
+    if (nwritten != (signed)sdslen(server.aof_buf)) {
         /* Ooops, we are in troubles. The best thing to do for now is
          * aborting instead of giving the illusion that everything is
          * working as expected. */
@@ -134,29 +134,29 @@ void flushAppendOnlyFile(int force) {
 
     /* Re-use AOF buffer when it is small enough. The maximum comes from the
      * arena size of 4k minus some overhead (but is otherwise arbitrary). */
-    if ((sdslen(server.aofbuf)+sdsavail(server.aofbuf)) < 4000) {
-        sdsclear(server.aofbuf);
+    if ((sdslen(server.aof_buf)+sdsavail(server.aof_buf)) < 4000) {
+        sdsclear(server.aof_buf);
     } else {
-        sdsfree(server.aofbuf);
-        server.aofbuf = sdsempty();
+        sdsfree(server.aof_buf);
+        server.aof_buf = sdsempty();
     }
 
     /* Don't fsync if no-appendfsync-on-rewrite is set to yes and there are
      * children doing I/O in the background. */
     if (server.aof_no_fsync_on_rewrite &&
-        (server.bgrewritechildpid != -1 || server.bgsavechildpid != -1))
+        (server.aof_child_pid != -1 || server.bgsavechildpid != -1))
             return;
 
     /* Perform the fsync if needed. */
     if (server.aof_fsync == AOF_FSYNC_ALWAYS) {
         /* aof_fsync is defined as fdatasync() for Linux in order to avoid
          * flushing metadata. */
-        aof_fsync(server.appendfd); /* Let's try to get this data on the disk */
-        server.lastfsync = server.unixtime;
+        aof_fsync(server.aof_fd); /* Let's try to get this data on the disk */
+        server.aof_last_fsync = server.unixtime;
     } else if ((server.aof_fsync == AOF_FSYNC_EVERYSEC &&
-                server.unixtime > server.lastfsync)) {
-        if (!sync_in_progress) aof_background_fsync(server.appendfd);
-        server.lastfsync = server.unixtime;
+                server.unixtime > server.aof_last_fsync)) {
+        if (!sync_in_progress) aof_background_fsync(server.aof_fd);
+        server.aof_last_fsync = server.unixtime;
     }
 }
 
@@ -228,13 +228,13 @@ void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int a
 
     /* The DB this command was targetting is not the same as the last command
      * we appendend. To issue a SELECT command is needed. */
-    if (dictid != server.appendseldb) {
+    if (dictid != server.aof_selected_db) {
         char seldb[64];
 
         snprintf(seldb,sizeof(seldb),"%d",dictid);
         buf = sdscatprintf(buf,"*2\r\n$6\r\nSELECT\r\n$%lu\r\n%s\r\n",
             (unsigned long)strlen(seldb),seldb);
-        server.appendseldb = dictid;
+        server.aof_selected_db = dictid;
     }
 
     if (cmd->proc == expireCommand || cmd->proc == pexpireCommand ||
@@ -260,14 +260,14 @@ void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int a
      * of re-entering the event loop, so before the client will get a
      * positive reply about the operation performed. */
     if (server.aof_state == REDIS_AOF_ON)
-        server.aofbuf = sdscatlen(server.aofbuf,buf,sdslen(buf));
+        server.aof_buf = sdscatlen(server.aof_buf,buf,sdslen(buf));
 
     /* If a background append only file rewriting is in progress we want to
      * accumulate the differences between the child DB and the current one
      * in a buffer, so that when the child process will do its work we
      * can append the differences to the new append only file. */
-    if (server.bgrewritechildpid != -1)
-        server.bgrewritebuf = sdscatlen(server.bgrewritebuf,buf,sdslen(buf));
+    if (server.aof_child_pid != -1)
+        server.aof_rewrite_buf = sdscatlen(server.aof_rewrite_buf,buf,sdslen(buf));
 
     sdsfree(buf);
 }
@@ -763,18 +763,18 @@ int rewriteAppendOnlyFile(char *filename) {
  * 1) The user calls BGREWRITEAOF
  * 2) Redis calls this function, that forks():
  *    2a) the child rewrite the append only file in a temp file.
- *    2b) the parent accumulates differences in server.bgrewritebuf.
+ *    2b) the parent accumulates differences in server.aof_rewrite_buf.
  * 3) When the child finished '2a' exists.
  * 4) The parent will trap the exit code, if it's OK, will append the
- *    data accumulated into server.bgrewritebuf into the temp file, and
+ *    data accumulated into server.aof_rewrite_buf into the temp file, and
  *    finally will rename(2) the temp file in the actual file name.
  *    The the new file is reopened as the new append only file. Profit!
  */
 int rewriteAppendOnlyFileBackground(void) {
     pid_t childpid;
     long long start;
 
-    if (server.bgrewritechildpid != -1) return REDIS_ERR;
+    if (server.aof_child_pid != -1) return REDIS_ERR;
     start = ustime();
     if ((childpid = fork()) == 0) {
         char tmpfile[256];
@@ -800,20 +800,20 @@ int rewriteAppendOnlyFileBackground(void) {
         redisLog(REDIS_NOTICE,
             "Background append only file rewriting started by pid %d",childpid);
         server.aof_rewrite_scheduled = 0;
-        server.bgrewritechildpid = childpid;
+        server.aof_child_pid = childpid;
         updateDictResizePolicy();
         /* We set appendseldb to -1 in order to force the next call to the
          * feedAppendOnlyFile() to issue a SELECT command, so the differences
-         * accumulated by the parent into server.bgrewritebuf will start
+         * accumulated by the parent into server.aof_rewrite_buf will start
          * with a SELECT statement and it will be safe to merge. */
-        server.appendseldb = -1;
+        server.aof_selected_db = -1;
         return REDIS_OK;
     }
     return REDIS_OK; /* unreached */
 }
 
 void bgrewriteaofCommand(redisClient *c) {
-    if (server.bgrewritechildpid != -1) {
+    if (server.aof_child_pid != -1) {
         addReplyError(c,"Background append only file rewriting already in progress");
     } else if (server.bgsavechildpid != -1) {
         server.aof_rewrite_scheduled = 1;
@@ -839,7 +839,7 @@ void aofRemoveTempFile(pid_t childpid) {
 void aofUpdateCurrentSize(void) {
     struct redis_stat sb;
 
-    if (redis_fstat(server.appendfd,&sb) == -1) {
+    if (redis_fstat(server.aof_fd,&sb) == -1) {
         redisLog(REDIS_WARNING,"Unable to check the AOF length: %s",
             strerror(errno));
     } else {
@@ -862,16 +862,16 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         /* Flush the differences accumulated by the parent to the
          * rewritten AOF. */
         snprintf(tmpfile,256,"temp-rewriteaof-bg-%d.aof",
-            (int)server.bgrewritechildpid);
+            (int)server.aof_child_pid);
         newfd = open(tmpfile,O_WRONLY|O_APPEND);
         if (newfd == -1) {
             redisLog(REDIS_WARNING,
                 "Unable to open the temporary AOF produced by the child: %s", strerror(errno));
             goto cleanup;
         }
 
-        nwritten = write(newfd,server.bgrewritebuf,sdslen(server.bgrewritebuf));
-        if (nwritten != (signed)sdslen(server.bgrewritebuf)) {
+        nwritten = write(newfd,server.aof_rewrite_buf,sdslen(server.aof_rewrite_buf));
+        if (nwritten != (signed)sdslen(server.aof_rewrite_buf)) {
             if (nwritten == -1) {
                 redisLog(REDIS_WARNING,
                     "Error trying to flush the parent diff to the rewritten AOF: %s", strerror(errno));
@@ -913,7 +913,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
          * guarantee atomicity for this switch has already happened by then, so
          * we don't care what the outcome or duration of that close operation
          * is, as long as the file descriptor is released again. */
-        if (server.appendfd == -1) {
+        if (server.aof_fd == -1) {
             /* AOF disabled */
 
              /* Don't care if this fails: oldfd will be -1 and we handle that.
@@ -935,26 +935,26 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
             goto cleanup;
         }
 
-        if (server.appendfd == -1) {
+        if (server.aof_fd == -1) {
             /* AOF disabled, we don't need to set the AOF file descriptor
              * to this new file, so we can close it. */
             close(newfd);
         } else {
             /* AOF enabled, replace the old fd with the new one. */
-            oldfd = server.appendfd;
-            server.appendfd = newfd;
+            oldfd = server.aof_fd;
+            server.aof_fd = newfd;
             if (server.aof_fsync == AOF_FSYNC_ALWAYS)
                 aof_fsync(newfd);
             else if (server.aof_fsync == AOF_FSYNC_EVERYSEC)
                 aof_background_fsync(newfd);
-            server.appendseldb = -1; /* Make sure SELECT is re-issued */
+            server.aof_selected_db = -1; /* Make sure SELECT is re-issued */
             aofUpdateCurrentSize();
             server.aof_rewrite_base_size = server.aof_current_size;
 
             /* Clear regular AOF buffer since its contents was just written to
              * the new AOF from the background rewrite buffer. */
-            sdsfree(server.aofbuf);
-            server.aofbuf = sdsempty();
+            sdsfree(server.aof_buf);
+            server.aof_buf = sdsempty();
         }
 
         redisLog(REDIS_NOTICE, "Background AOF rewrite successful");
@@ -976,10 +976,10 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
     }
 
 cleanup:
-    sdsfree(server.bgrewritebuf);
-    server.bgrewritebuf = sdsempty();
-    aofRemoveTempFile(server.bgrewritechildpid);
-    server.bgrewritechildpid = -1;
+    sdsfree(server.aof_rewrite_buf);
+    server.aof_rewrite_buf = sdsempty();
+    aofRemoveTempFile(server.aof_child_pid);
+    server.aof_child_pid = -1;
     /* Schedule a new rewrite if we are waiting for it to switch the AOF ON. */
     if (server.aof_state == REDIS_AOF_WAIT_REWRITE)
         server.aof_rewrite_scheduled = 1;