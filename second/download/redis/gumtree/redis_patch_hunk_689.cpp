             if (expiretime != -1 && expiretime < now) continue;
 
             /* Save the key and associated value */
             if (o->type == OBJ_STRING) {
                 /* Emit a SET command */
                 char cmd[]="*3\r\n$3\r\nSET\r\n";
-                if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
+                if (rioWrite(aof,cmd,sizeof(cmd)-1) == 0) goto werr;
                 /* Key and value */
-                if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
-                if (rioWriteBulkObject(&aof,o) == 0) goto werr;
+                if (rioWriteBulkObject(aof,&key) == 0) goto werr;
+                if (rioWriteBulkObject(aof,o) == 0) goto werr;
             } else if (o->type == OBJ_LIST) {
-                if (rewriteListObject(&aof,&key,o) == 0) goto werr;
+                if (rewriteListObject(aof,&key,o) == 0) goto werr;
             } else if (o->type == OBJ_SET) {
-                if (rewriteSetObject(&aof,&key,o) == 0) goto werr;
+                if (rewriteSetObject(aof,&key,o) == 0) goto werr;
             } else if (o->type == OBJ_ZSET) {
-                if (rewriteSortedSetObject(&aof,&key,o) == 0) goto werr;
+                if (rewriteSortedSetObject(aof,&key,o) == 0) goto werr;
             } else if (o->type == OBJ_HASH) {
-                if (rewriteHashObject(&aof,&key,o) == 0) goto werr;
+                if (rewriteHashObject(aof,&key,o) == 0) goto werr;
+            } else if (o->type == OBJ_MODULE) {
+                if (rewriteModuleObject(aof,&key,o) == 0) goto werr;
             } else {
                 serverPanic("Unknown object type");
             }
             /* Save the expire time */
             if (expiretime != -1) {
                 char cmd[]="*3\r\n$9\r\nPEXPIREAT\r\n";
-                if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
-                if (rioWriteBulkObject(&aof,&key) == 0) goto werr;
-                if (rioWriteBulkLongLong(&aof,expiretime) == 0) goto werr;
+                if (rioWrite(aof,cmd,sizeof(cmd)-1) == 0) goto werr;
+                if (rioWriteBulkObject(aof,&key) == 0) goto werr;
+                if (rioWriteBulkLongLong(aof,expiretime) == 0) goto werr;
             }
             /* Read some diff from the parent process from time to time. */
-            if (aof.processed_bytes > processed+1024*10) {
-                processed = aof.processed_bytes;
+            if (aof->processed_bytes > processed+AOF_READ_DIFF_INTERVAL_BYTES) {
+                processed = aof->processed_bytes;
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
+    if (server.aof_use_rdb_preamble) {
+        int error;
+        if (rdbSaveRio(&aof,&error,RDB_SAVE_AOF_PREAMBLE,NULL) == C_ERR) {
+            errno = error;
+            goto werr;
+        }
+    } else {
+        if (rewriteAppendOnlyFileRio(&aof) == C_ERR) goto werr;
+    }
 
     /* Do an initial slow fsync here while the parent is still sending
      * data, in order to make the next final fsync faster. */
     if (fflush(fp) == EOF) goto werr;
     if (fsync(fileno(fp)) == -1) goto werr;
 
