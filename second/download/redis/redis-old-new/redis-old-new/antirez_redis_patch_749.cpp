@@ -74,7 +74,7 @@ void aofRewriteBufferReset(void) {
     listSetFreeMethod(server.aof_rewrite_buf_blocks,zfree);
 }
 
-/* Return the current size of the AOF rerwite buffer. */
+/* Return the current size of the AOF rewite buffer. */
 unsigned long aofRewriteBufferSize(void) {
     listNode *ln;
     listIter li;
@@ -245,7 +245,7 @@ int startAppendOnly(void) {
         redisLog(REDIS_WARNING,"Redis needs to enable the AOF but can't trigger a background AOF rewrite operation. Check the above logs for more info about the error.");
         return REDIS_ERR;
     }
-    /* We correctly switched on AOF, now wait for the rerwite to be complete
+    /* We correctly switched on AOF, now wait for the rewite to be complete
      * in order to append data on disk. */
     server.aof_state = REDIS_AOF_WAIT_REWRITE;
     return REDIS_OK;
@@ -286,7 +286,7 @@ void flushAppendOnlyFile(int force) {
          * the write for a couple of seconds. */
         if (sync_in_progress) {
             if (server.aof_flush_postponed_start == 0) {
-                /* No previous write postponinig, remember that we are
+                /* No previous write postponing, remember that we are
                  * postponing the flush and return. */
                 server.aof_flush_postponed_start = server.unixtime;
                 return;
@@ -337,7 +337,7 @@ void flushAppendOnlyFile(int force) {
             last_write_error_log = server.unixtime;
         }
 
-        /* Lof the AOF write error and record the error code. */
+        /* Log the AOF write error and record the error code. */
         if (nwritten == -1) {
             if (can_log) {
                 redisLog(REDIS_WARNING,"Error writing to the AOF file: %s",
@@ -361,7 +361,7 @@ void flushAppendOnlyFile(int force) {
                              "ftruncate: %s", strerror(errno));
                 }
             } else {
-                /* If the ftrunacate() succeeded we can set nwritten to
+                /* If the ftruncate() succeeded we can set nwritten to
                  * -1 since there is no longer partial data into the AOF. */
                 nwritten = -1;
             }
@@ -373,7 +373,7 @@ void flushAppendOnlyFile(int force) {
             /* We can't recover when the fsync policy is ALWAYS since the
              * reply for the client is already in the output buffers, and we
              * have the contract with the user that on acknowledged write data
-             * is synched on disk. */
+             * is synced on disk. */
             redisLog(REDIS_WARNING,"Can't recover from AOF write error when the AOF fsync policy is 'always'. Exiting...");
             exit(1);
         } else {
@@ -468,7 +468,7 @@ sds catAppendOnlyExpireAtCommand(sds buf, struct redisCommand *cmd, robj *key, r
     long long when;
     robj *argv[3];
 
-    /* Make sure we can use strtol */
+    /* Make sure we can use strtoll */
     seconds = getDecodedObject(seconds);
     when = strtoll(seconds->ptr,NULL,10);
     /* Convert argument into milliseconds for EXPIRE, SETEX, EXPIREAT */
@@ -499,7 +499,7 @@ void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int a
     robj *tmpargv[3];
 
     /* The DB this command was targeting is not the same as the last command
-     * we appendend. To issue a SELECT command is needed. */
+     * we appended. To issue a SELECT command is needed. */
     if (dictid != server.aof_selected_db) {
         char seldb[64];
 
@@ -1000,7 +1000,7 @@ int rewriteHashObject(rio *r, robj *key, robj *o) {
  * the difference accumulated from the parent into a buffer, that is
  * concatenated at the end of the rewrite. */
 ssize_t aofReadDiffFromParent(void) {
-    char buf[65536]; /* Default pipe buffer size on most Linux sytems. */
+    char buf[65536]; /* Default pipe buffer size on most Linux systems. */
     ssize_t nread, total = 0;
 
     while ((nread =
@@ -1114,7 +1114,7 @@ int rewriteAppendOnlyFile(char *filename) {
 
     /* Read again a few times to get more data from the parent.
      * We can't read forever (the server may receive data from clients
-     * fater than it is able to send data to the child), so we try to read
+     * faster than it is able to send data to the child), so we try to read
      * some more data in a loop as soon as there is a good chance more data
      * will come. If it looks like we are wasting time, we abort (this
      * happens after 20 ms without new data). */
@@ -1250,7 +1250,7 @@ void aofClosePipes(void) {
 }
 
 /* ----------------------------------------------------------------------------
- * AOF backgorund rewrite
+ * AOF background rewrite
  * ------------------------------------------------------------------------- */
 
 /* This is how rewriting of the append only file in background works:
@@ -1392,7 +1392,7 @@ void backgroundRewriteDoneHandler(int exitcode, int bysignal) {
         latencyAddSampleIfNeeded("aof-rewrite-diff-write",latency);
 
         redisLog(REDIS_NOTICE,
-            "Redidual parent diff successfully flushed to the rewritten AOF (%.2f MB)", (double) aofRewriteBufferSize() / (1024*1024));
+            "Residual parent diff successfully flushed to the rewritten AOF (%.2f MB)", (double) aofRewriteBufferSize() / (1024*1024));
 
         /* The only remaining thing to do is to rename the temporary file to
          * the configured file and switch the file descriptor used to do AOF