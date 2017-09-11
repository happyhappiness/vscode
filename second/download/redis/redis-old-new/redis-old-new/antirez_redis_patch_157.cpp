@@ -818,14 +818,16 @@ int rdbSaveAuxFieldStrInt(rio *rdb, char *key, long long val) {
 }
 
 /* Save a few default AUX fields with information about the RDB generated. */
-int rdbSaveInfoAuxFields(rio *rdb) {
+int rdbSaveInfoAuxFields(rio *rdb, int flags) {
     int redis_bits = (sizeof(void*) == 8) ? 64 : 32;
+    int aof_preamble = (flags & RDB_SAVE_AOF_PREAMBLE) != 0;
 
     /* Add a few fields about the state when the RDB was created. */
     if (rdbSaveAuxFieldStrStr(rdb,"redis-ver",REDIS_VERSION) == -1) return -1;
     if (rdbSaveAuxFieldStrInt(rdb,"redis-bits",redis_bits) == -1) return -1;
     if (rdbSaveAuxFieldStrInt(rdb,"ctime",time(NULL)) == -1) return -1;
     if (rdbSaveAuxFieldStrInt(rdb,"used-mem",zmalloc_used_memory()) == -1) return -1;
+    if (rdbSaveAuxFieldStrInt(rdb,"aof-preamble",aof_preamble)) return -1;
     return 1;
 }
 
@@ -837,19 +839,20 @@ int rdbSaveInfoAuxFields(rio *rdb) {
  * When the function returns C_ERR and if 'error' is not NULL, the
  * integer pointed by 'error' is set to the value of errno just after the I/O
  * error. */
-int rdbSaveRio(rio *rdb, int *error) {
+int rdbSaveRio(rio *rdb, int *error, int flags) {
     dictIterator *di = NULL;
     dictEntry *de;
     char magic[10];
     int j;
     long long now = mstime();
     uint64_t cksum;
+    size_t processed = 0;
 
     if (server.rdb_checksum)
         rdb->update_cksum = rioGenericUpdateChecksum;
     snprintf(magic,sizeof(magic),"REDIS%04d",RDB_VERSION);
     if (rdbWriteRaw(rdb,magic,9) == -1) goto werr;
-    if (rdbSaveInfoAuxFields(rdb) == -1) goto werr;
+    if (rdbSaveInfoAuxFields(rdb,flags) == -1) goto werr;
 
     for (j = 0; j < server.dbnum; j++) {
         redisDb *db = server.db+j;
@@ -886,6 +889,16 @@ int rdbSaveRio(rio *rdb, int *error) {
             initStaticStringObject(key,keystr);
             expire = getExpire(db,&key);
             if (rdbSaveKeyValuePair(rdb,&key,o,expire,now) == -1) goto werr;
+
+            /* When this RDB is produced as part of an AOF rewrite, move
+             * accumulated diff from parent to child while rewriting in
+             * order to have a smaller final write. */
+            if (flags & RDB_SAVE_AOF_PREAMBLE &&
+                rdb.processed_bytes > processed+AOF_READ_DIFF_INTERVAL_BYTES)
+            {
+                processed = rdb.processed_bytes;
+                aofReadDiffFromParent();
+            }
         }
         dictReleaseIterator(di);
     }
@@ -923,7 +936,7 @@ int rdbSaveRioWithEOFMark(rio *rdb, int *error) {
     if (rioWrite(rdb,"$EOF:",5) == 0) goto werr;
     if (rioWrite(rdb,eofmark,RDB_EOF_MARK_SIZE) == 0) goto werr;
     if (rioWrite(rdb,"\r\n",2) == 0) goto werr;
-    if (rdbSaveRio(rdb,error) == C_ERR) goto werr;
+    if (rdbSaveRio(rdb,error,RDB_SAVE_NONE) == C_ERR) goto werr;
     if (rioWrite(rdb,eofmark,RDB_EOF_MARK_SIZE) == 0) goto werr;
     return C_OK;
 
@@ -955,7 +968,7 @@ int rdbSave(char *filename) {
     }
 
     rioInitWithFile(&rdb,fp);
-    if (rdbSaveRio(&rdb,&error) == C_ERR) {
+    if (rdbSaveRio(&rdb,&error,RDB_SAVE_NONE) == C_ERR) {
         errno = error;
         goto werr;
     }