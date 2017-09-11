@@ -26,6 +26,7 @@ void stopAppendOnly(void) {
     server.appendfd = -1;
     server.appendseldb = -1;
     server.appendonly = 0;
+    server.aof_wait_rewrite = 0;
     /* rewrite operation in progress? kill it, wait child exit */
     if (server.bgrewritechildpid != -1) {
         int statloc;
@@ -35,6 +36,7 @@ void stopAppendOnly(void) {
         /* reset the buffer accumulating changes while the child saves */
         sdsfree(server.bgrewritebuf);
         server.bgrewritebuf = sdsempty();
+        aofRemoveTempFile(server.bgrewritechildpid);
         server.bgrewritechildpid = -1;
     }
 }
@@ -46,15 +48,18 @@ int startAppendOnly(void) {
     server.lastfsync = time(NULL);
     server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
     if (server.appendfd == -1) {
-        redisLog(REDIS_WARNING,"Used tried to switch on AOF via CONFIG, but I can't open the AOF file: %s",strerror(errno));
+        redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
         return REDIS_ERR;
     }
     if (rewriteAppendOnlyFileBackground() == REDIS_ERR) {
         server.appendonly = 0;
         close(server.appendfd);
-        redisLog(REDIS_WARNING,"User tried turning on AOF with CONFIG SET but I can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
+        redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
         return REDIS_ERR;
     }
+    /* We correctly switched on AOF, now wait for the rerwite to be complete
+     * in order to append data on disk. */
+    server.aof_wait_rewrite = 1;
     return REDIS_OK;
 }
 
@@ -219,9 +224,15 @@ sds catAppendOnlyExpireAtCommand(sds buf, struct redisCommand *cmd, robj *key, r
 }
 
 void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc) {
-    sds buf = sdsempty();
+    sds buf;
     robj *tmpargv[3];
 
+    /* Return ASAP if we are writing a rewrite to finish in order to start
+     * appending to the Append Only File. */
+    if (server.aof_wait_rewrite) return;
+
+    buf = sdsempty();
+
     /* The DB this command was targetting is not the same as the last command
      * we appendend. To issue a SELECT command is needed. */
     if (dictid != server.appendseldb) {
@@ -953,6 +964,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         }
 
         redisLog(REDIS_NOTICE, "Background AOF rewrite successful");
+        server.aof_wait_rewrite = 0;
 
         /* Asynchronously close the overwritten AOF. */
         if (oldfd != -1) bioCreateBackgroundJob(REDIS_BIO_CLOSE_FILE,(void*)(long)oldfd,NULL,NULL);
@@ -972,4 +984,10 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
     server.bgrewritebuf = sdsempty();
     aofRemoveTempFile(server.bgrewritechildpid);
     server.bgrewritechildpid = -1;
+    /* If we were waiting for an AOF rewrite before to start appending
+     * to the AOF again (this happens both when the user switches on
+     * AOF with CONFIG SET, and after a slave with AOF enabled syncs with
+     * the master), but the rewrite failed (otherwise aof_wait_rewrite
+     * would be zero), we need to schedule a new one. */
+    if (server.aof_wait_rewrite) server.aofrewrite_scheduled = 1;
 }