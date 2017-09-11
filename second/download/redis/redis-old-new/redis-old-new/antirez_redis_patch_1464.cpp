@@ -19,14 +19,14 @@ void aof_background_fsync(int fd) {
 /* Called when the user switches from "appendonly yes" to "appendonly no"
  * at runtime using the CONFIG command. */
 void stopAppendOnly(void) {
+    redisAssert(server.aof_state != REDIS_AOF_OFF);
     flushAppendOnlyFile(1);
     aof_fsync(server.appendfd);
     close(server.appendfd);
 
     server.appendfd = -1;
     server.appendseldb = -1;
-    server.appendonly = 0;
-    server.aof_wait_rewrite = 0;
+    server.aof_state = REDIS_AOF_OFF;
     /* rewrite operation in progress? kill it, wait child exit */
     if (server.bgrewritechildpid != -1) {
         int statloc;
@@ -46,6 +46,7 @@ void stopAppendOnly(void) {
 int startAppendOnly(void) {
     server.lastfsync = time(NULL);
     server.appendfd = open(server.appendfilename,O_WRONLY|O_APPEND|O_CREAT,0644);
+    redisAssert(server.aof_state == REDIS_AOF_OFF);
     if (server.appendfd == -1) {
         redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't open the append only file: %s",strerror(errno));
         return REDIS_ERR;
@@ -57,8 +58,7 @@ int startAppendOnly(void) {
     }
     /* We correctly switched on AOF, now wait for the rerwite to be complete
      * in order to append data on disk. */
-    server.appendonly = 1;
-    server.aof_wait_rewrite = 1;
+    server.aof_state = REDIS_AOF_WAIT_REWRITE;
     return REDIS_OK;
 }
 
@@ -258,15 +258,9 @@ void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int a
 
     /* Append to the AOF buffer. This will be flushed on disk just before
      * of re-entering the event loop, so before the client will get a
-     * positive reply about the operation performed.
-     *
-     * Note, we don't add stuff in the AOF buffer if aof_wait_rewrite is
-     * non zero, as this means we are starting with a new AOF and the
-     * current one is meaningless (this happens for instance after
-     * a slave resyncs with its master). */
-    if (!server.aof_wait_rewrite) {
+     * positive reply about the operation performed. */
+    if (server.aof_state == REDIS_AOF_ON)
         server.aofbuf = sdscatlen(server.aofbuf,buf,sdslen(buf));
-    }
 
     /* If a background append only file rewriting is in progress we want to
      * accumulate the differences between the child DB and the current one
@@ -316,7 +310,7 @@ int loadAppendOnlyFile(char *filename) {
     struct redisClient *fakeClient;
     FILE *fp = fopen(filename,"r");
     struct redis_stat sb;
-    int appendonly = server.appendonly;
+    int old_aof_state = server.aof_state;
     long loops = 0;
 
     if (fp && redis_fstat(fileno(fp),&sb) != -1 && sb.st_size == 0) {
@@ -332,7 +326,7 @@ int loadAppendOnlyFile(char *filename) {
 
     /* Temporarily disable AOF, to prevent EXEC from feeding a MULTI
      * to the same file we're about to read. */
-    server.appendonly = 0;
+    server.aof_state = REDIS_AOF_OFF;
 
     fakeClient = createFakeClient();
     startLoading(fp);
@@ -401,7 +395,7 @@ int loadAppendOnlyFile(char *filename) {
 
     fclose(fp);
     freeFakeClient(fakeClient);
-    server.appendonly = appendonly;
+    server.aof_state = old_aof_state;
     stopLoading();
     aofUpdateCurrentSize();
     server.auto_aofrewrite_base_size = server.appendonly_current_size;
@@ -964,7 +958,9 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         }
 
         redisLog(REDIS_NOTICE, "Background AOF rewrite successful");
-        server.aof_wait_rewrite = 0;
+        /* Change state from WAIT_REWRITE to ON if needed */
+        if (server.aof_state == REDIS_AOF_WAIT_REWRITE)
+            server.aof_state = REDIS_AOF_ON;
 
         /* Asynchronously close the overwritten AOF. */
         if (oldfd != -1) bioCreateBackgroundJob(REDIS_BIO_CLOSE_FILE,(void*)(long)oldfd,NULL,NULL);
@@ -984,10 +980,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
     server.bgrewritebuf = sdsempty();
     aofRemoveTempFile(server.bgrewritechildpid);
     server.bgrewritechildpid = -1;
-    /* If we were waiting for an AOF rewrite before to start appending
-     * to the AOF again (this happens both when the user switches on
-     * AOF with CONFIG SET, and after a slave with AOF enabled syncs with
-     * the master), but the rewrite failed (otherwise aof_wait_rewrite
-     * would be zero), we need to schedule a new one. */
-    if (server.aof_wait_rewrite) server.aofrewrite_scheduled = 1;
+    /* Schedule a new rewrite if we are waiting for it to switch the AOF ON. */
+    if (server.aof_state == REDIS_AOF_WAIT_REWRITE)
+        server.aofrewrite_scheduled = 1;
 }