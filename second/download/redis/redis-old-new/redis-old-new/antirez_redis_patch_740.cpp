@@ -627,45 +627,37 @@ int rdbSaveKeyValuePair(rio *rdb, robj *key, robj *val,
     return 1;
 }
 
-/* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success */
-int rdbSave(char *filename) {
+/* Produces a dump of the database in RDB format sending it to the specified
+ * Redis I/O channel. On success REDIS_OK is returned, otherwise REDIS_ERR
+ * is returned and part of the output, or all the output, can be
+ * missing because of I/O errors.
+ *
+ * When the function returns REDIS_ERR and if 'error' is not NULL, the
+ * integer pointed by 'error' is set to the value of errno just after the I/O
+ * error. */
+int rdbSaveRio(rio *rdb, int *error) {
     dictIterator *di = NULL;
     dictEntry *de;
-    char tmpfile[256];
     char magic[10];
     int j;
     long long now = mstime();
-    FILE *fp;
-    rio rdb;
     uint64_t cksum;
 
-    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
-    fp = fopen(tmpfile,"w");
-    if (!fp) {
-        redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
-            strerror(errno));
-        return REDIS_ERR;
-    }
-
-    rioInitWithFile(&rdb,fp);
     if (server.rdb_checksum)
-        rdb.update_cksum = rioGenericUpdateChecksum;
+        rdb->update_cksum = rioGenericUpdateChecksum;
     snprintf(magic,sizeof(magic),"REDIS%04d",REDIS_RDB_VERSION);
-    if (rdbWriteRaw(&rdb,magic,9) == -1) goto werr;
+    if (rdbWriteRaw(rdb,magic,9) == -1) goto werr;
 
     for (j = 0; j < server.dbnum; j++) {
         redisDb *db = server.db+j;
         dict *d = db->dict;
         if (dictSize(d) == 0) continue;
         di = dictGetSafeIterator(d);
-        if (!di) {
-            fclose(fp);
-            return REDIS_ERR;
-        }
+        if (!di) return REDIS_ERR;
 
         /* Write the SELECT DB opcode */
-        if (rdbSaveType(&rdb,REDIS_RDB_OPCODE_SELECTDB) == -1) goto werr;
-        if (rdbSaveLen(&rdb,j) == -1) goto werr;
+        if (rdbSaveType(rdb,REDIS_RDB_OPCODE_SELECTDB) == -1) goto werr;
+        if (rdbSaveLen(rdb,j) == -1) goto werr;
 
         /* Iterate this DB writing every entry */
         while((de = dictNext(di)) != NULL) {
@@ -675,20 +667,48 @@ int rdbSave(char *filename) {
 
             initStaticStringObject(key,keystr);
             expire = getExpire(db,&key);
-            if (rdbSaveKeyValuePair(&rdb,&key,o,expire,now) == -1) goto werr;
+            if (rdbSaveKeyValuePair(rdb,&key,o,expire,now) == -1) goto werr;
         }
         dictReleaseIterator(di);
     }
     di = NULL; /* So that we don't release it again on error. */
 
     /* EOF opcode */
-    if (rdbSaveType(&rdb,REDIS_RDB_OPCODE_EOF) == -1) goto werr;
+    if (rdbSaveType(rdb,REDIS_RDB_OPCODE_EOF) == -1) goto werr;
 
     /* CRC64 checksum. It will be zero if checksum computation is disabled, the
      * loading code skips the check in this case. */
-    cksum = rdb.cksum;
+    cksum = rdb->cksum;
     memrev64ifbe(&cksum);
-    if (rioWrite(&rdb,&cksum,8) == 0) goto werr;
+    if (rioWrite(rdb,&cksum,8) == 0) goto werr;
+    return REDIS_OK;
+
+werr:
+    if (error) *error = errno;
+    if (di) dictReleaseIterator(di);
+    return REDIS_ERR;
+}
+
+/* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success. */
+int rdbSave(char *filename) {
+    char tmpfile[256];
+    FILE *fp;
+    rio rdb;
+    int error;
+
+    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
+    fp = fopen(tmpfile,"w");
+    if (!fp) {
+        redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
+            strerror(errno));
+        return REDIS_ERR;
+    }
+
+    rioInitWithFile(&rdb,fp);
+    if (rdbSaveRio(&rdb,&error) == REDIS_ERR) {
+        errno = error;
+        goto werr;
+    }
 
     /* Make sure data will not remain on the OS's output buffers */
     if (fflush(fp) == EOF) goto werr;
@@ -712,7 +732,6 @@ int rdbSave(char *filename) {
     fclose(fp);
     unlink(tmpfile);
     redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
-    if (di) dictReleaseIterator(di);
     return REDIS_ERR;
 }
 