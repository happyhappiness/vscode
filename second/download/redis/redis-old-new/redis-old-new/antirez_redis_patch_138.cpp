@@ -616,26 +616,52 @@ int loadAppendOnlyFile(char *filename) {
     struct redis_stat sb;
     int old_aof_state = server.aof_state;
     long loops = 0;
-    off_t valid_up_to = 0; /* Offset of the latest well-formed command loaded. */
+    off_t valid_up_to = 0; /* Offset of latest well-formed command loaded. */
 
+    if (fp == NULL) {
+        serverLog(LL_WARNING,"Fatal error: can't open the append log file for reading: %s",strerror(errno));
+        exit(1);
+    }
+
+    /* Handle a zero-length AOF file as a special case. An emtpy AOF file
+     * is a valid AOF because an empty server with AOF enabled will create
+     * a zero length file at startup, that will remain like that if no write
+     * operation is received. */
     if (fp && redis_fstat(fileno(fp),&sb) != -1 && sb.st_size == 0) {
         server.aof_current_size = 0;
         fclose(fp);
         return C_ERR;
     }
 
-    if (fp == NULL) {
-        serverLog(LL_WARNING,"Fatal error: can't open the append log file for reading: %s",strerror(errno));
-        exit(1);
-    }
-
     /* Temporarily disable AOF, to prevent EXEC from feeding a MULTI
      * to the same file we're about to read. */
     server.aof_state = AOF_OFF;
 
     fakeClient = createFakeClient();
     startLoading(fp);
 
+    /* Check if this AOF file has an RDB preamble. In that case we need to
+     * load the RDB file and later continue loading the AOF tail. */
+    char sig[5]; /* "REDIS" */
+    if (fread(sig,1,5,fp) != 5 || memcmp(sig,"REDIS",5) != 0) {
+        /* No RDB preamble, seek back at 0 offset. */
+        if (fseek(fp,0,SEEK_SET) == -1) goto readerr;
+    } else {
+        /* RDB preamble. Pass loading the RDB functions. */
+        rio rdb;
+
+        serverLog(LL_NOTICE,"Reading RDB preamble from AOF file...");
+        if (fseek(fp,0,SEEK_SET) == -1) goto readerr;
+        rioInitWithFile(&rdb,fp);
+        if (rdbLoadRio(&rdb) != C_OK) {
+            serverLog(LL_WARNING,"Error reading the RDB preamble of the AOF file, AOF loading aborted");
+            goto readerr;
+        } else {
+            serverLog(LL_NOTICE,"Reading the remaining AOF tail...");
+        }
+    }
+
+    /* Read the actual AOF file, in REPL format, command by command. */
     while(1) {
         int argc, j;
         unsigned long len;
@@ -989,7 +1015,7 @@ int rewriteHashObject(rio *r, robj *key, robj *o) {
 }
 
 /* Call the module type callback in order to rewrite a data type
- * taht is exported by a module and is not handled by Redis itself.
+ * that is exported by a module and is not handled by Redis itself.
  * The function returns 0 on error, 1 on success. */
 int rewriteModuleObject(rio *r, robj *key, robj *o) {
     RedisModuleIO io;
@@ -1015,51 +1041,23 @@ ssize_t aofReadDiffFromParent(void) {
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
+int rewriteAppendOnlyFileRio(rio *aof) {
     dictIterator *di = NULL;
     dictEntry *de;
-    rio aof;
-    FILE *fp;
-    char tmpfile[256];
-    int j;
-    long long now = mstime();
-    char byte;
     size_t processed = 0;
+    long long now = mstime();
+    int j;
 
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
         dict *d = db->dict;
         if (dictSize(d) == 0) continue;
         di = dictGetSafeIterator(d);
-        if (!di) {
-            fclose(fp);
-            return C_ERR;
-        }
 
         /* SELECT the new DB */
-        if (rioWrite(&aof,selectcmd,sizeof(selectcmd)-1) == 0) goto werr;
-        if (rioWriteBulkLongLong(&aof,j) == 0) goto werr;
+        if (rioWrite(aof,selectcmd,sizeof(selectcmd)-1) == 0) goto werr;
+        if (rioWriteBulkLongLong(aof,j) == 0) goto werr;
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
@@ -1080,39 +1078,83 @@ int rewriteAppendOnlyFile(char *filename) {
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
             } else if (o->type == OBJ_MODULE) {
-                if (rewriteModuleObject(&aof,&key,o) == 0) goto werr;
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
+        if (rdbSaveRio(&aof,&error,RDB_SAVE_AOF_PREAMBLE) == C_ERR) {
+            errno = error;
+            goto werr;
+        }
+    } else {
+        if (rewriteAppendOnlyFileRio(&aof) == C_ERR) goto werr;
+    }
 
     /* Do an initial slow fsync here while the parent is still sending
      * data, in order to make the next final fsync faster. */
@@ -1178,7 +1220,6 @@ int rewriteAppendOnlyFile(char *filename) {
     serverLog(LL_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
-    if (di) dictReleaseIterator(di);
     return C_ERR;
 }
 