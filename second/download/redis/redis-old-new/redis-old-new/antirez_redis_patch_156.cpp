@@ -989,7 +989,7 @@ int rewriteHashObject(rio *r, robj *key, robj *o) {
 }
 
 /* Call the module type callback in order to rewrite a data type
- * taht is exported by a module and is not handled by Redis itself.
+ * that is exported by a module and is not handled by Redis itself.
  * The function returns 0 on error, 1 on success. */
 int rewriteModuleObject(rio *r, robj *key, robj *o) {
     RedisModuleIO io;
@@ -1015,37 +1015,11 @@ ssize_t aofReadDiffFromParent(void) {
     return total;
 }
 
-/* Write a sequence of commands able to fully rebuild the dataset into
- * "filename". Used both by REWRITEAOF and BGREWRITEAOF.
- *
- * In order to minimize the number of commands needed in the rewritten
- * log Redis uses variadic commands when possible, such as RPUSH, SADD
- * and ZADD. However at max AOF_REWRITE_ITEMS_PER_CMD items per time
- * are inserted using a single command. */
-int rewriteAppendOnlyFile(char *filename) {
+void rewriteAppendOnlyFileRio(rio *aof) {
     dictIterator *di = NULL;
     dictEntry *de;
-    rio aof;
-    FILE *fp;
-    char tmpfile[256];
-    int j;
-    long long now = mstime();
-    char byte;
     size_t processed = 0;
 
-    /* Note that we have to use a different temp name here compared to the
-     * one used by rewriteAppendOnlyFileBackground() function. */
-    snprintf(tmpfile,256,"temp-rewriteaof-%d.aof", (int) getpid());
-    fp = fopen(tmpfile,"w");
-    if (!fp) {
-        serverLog(LL_WARNING, "Opening the temp file for AOF rewrite in rewriteAppendOnlyFile(): %s", strerror(errno));
-        return C_ERR;
-    }
-
-    server.aof_child_diff = sdsempty();
-    rioInitWithFile(&aof,fp);
-    if (server.aof_rewrite_incremental_fsync)
-        rioSetAutoSync(&aof,AOF_AUTOSYNC_BYTES);
     for (j = 0; j < server.dbnum; j++) {
         char selectcmd[] = "*2\r\n$6\r\nSELECT\r\n";
         redisDb *db = server.db+j;
@@ -1105,14 +1079,60 @@ int rewriteAppendOnlyFile(char *filename) {
                 if (rioWriteBulkLongLong(&aof,expiretime) == 0) goto werr;
             }
             /* Read some diff from the parent process from time to time. */
-            if (aof.processed_bytes > processed+1024*10) {
+            if (aof.processed_bytes > processed+AOF_READ_DIFF_INTERVAL_BYTES) {
                 processed = aof.processed_bytes;
                 aofReadDiffFromParent();
             }
         }
         dictReleaseIterator(di);
         di = NULL;
     }
+    return C_OK;
+
+werr:
+    if (di) dictReleaseIterator(di);
+    return C_ERR;
+}
+
+/* Write a sequence of commands able to fully rebuild the dataset into
+ * "filename". Used both by REWRITEAOF and BGREWRITEAOF.
+ *
+ * In order to minimize the number of commands needed in the rewritten
+ * log Redis uses variadic commands when possible, such as RPUSH, SADD
+ * and ZADD. However at max AOF_REWRITE_ITEMS_PER_CMD items per time
+ * are inserted using a single command. */
+int rewriteAppendOnlyFile(char *filename) {
+    rio aof;
+    FILE *fp;
+    char tmpfile[256];
+    int j;
+    long long now = mstime();
+    char byte;
+
+    /* Note that we have to use a different temp name here compared to the
+     * one used by rewriteAppendOnlyFileBackground() function. */
+    snprintf(tmpfile,256,"temp-rewriteaof-%d.aof", (int) getpid());
+    fp = fopen(tmpfile,"w");
+    if (!fp) {
+        serverLog(LL_WARNING, "Opening the temp file for AOF rewrite in rewriteAppendOnlyFile(): %s", strerror(errno));
+        return C_ERR;
+    }
+
+    server.aof_child_diff = sdsempty();
+    rioInitWithFile(&aof,fp);
+
+    if (server.aof_rewrite_incremental_fsync)
+        rioSetAutoSync(&aof,AOF_AUTOSYNC_BYTES);
+
+    if (server.aof_use_rdb_prefix) {
+        int error;
+        if (rdbSaveRio(&rdb,&error,RDB_SAVE_AOF_PREAMBLE) == C_ERR) {
+            errno = error;
+            goto werr;
+        }
+    } else {
+        rewriteAppendOnlyFileRio(&aof);
+    }
 
     /* Do an initial slow fsync here while the parent is still sending
      * data, in order to make the next final fsync faster. */
@@ -1178,7 +1198,6 @@ int rewriteAppendOnlyFile(char *filename) {
     serverLog(LL_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
-    if (di) dictReleaseIterator(di);
     return C_ERR;
 }
 