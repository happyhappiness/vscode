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
+    if (rdbSaveAuxFieldStrInt(rdb,"aof-preamble",aof_preamble) == -1) return -1;
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
+                rdb->processed_bytes > processed+AOF_READ_DIFF_INTERVAL_BYTES)
+            {
+                processed = rdb->processed_bytes;
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
@@ -1373,67 +1386,61 @@ void rdbLoadProgressCallback(rio *r, const void *buf, size_t len) {
     }
 }
 
-int rdbLoad(char *filename) {
+/* Load an RDB file from the rio stream 'rdb'. On success C_OK is returned,
+ * otherwise C_ERR is returned and 'errno' is set accordingly. */
+int rdbLoadRio(rio *rdb) {
     uint64_t dbid;
     int type, rdbver;
     redisDb *db = server.db+0;
     char buf[1024];
     long long expiretime, now = mstime();
-    FILE *fp;
-    rio rdb;
 
-    if ((fp = fopen(filename,"r")) == NULL) return C_ERR;
-
-    rioInitWithFile(&rdb,fp);
-    rdb.update_cksum = rdbLoadProgressCallback;
-    rdb.max_processing_chunk = server.loading_process_events_interval_bytes;
-    if (rioRead(&rdb,buf,9) == 0) goto eoferr;
+    rdb->update_cksum = rdbLoadProgressCallback;
+    rdb->max_processing_chunk = server.loading_process_events_interval_bytes;
+    if (rioRead(rdb,buf,9) == 0) goto eoferr;
     buf[9] = '\0';
     if (memcmp(buf,"REDIS",5) != 0) {
-        fclose(fp);
         serverLog(LL_WARNING,"Wrong signature trying to load DB from file");
         errno = EINVAL;
         return C_ERR;
     }
     rdbver = atoi(buf+5);
     if (rdbver < 1 || rdbver > RDB_VERSION) {
-        fclose(fp);
         serverLog(LL_WARNING,"Can't handle RDB format version %d",rdbver);
         errno = EINVAL;
         return C_ERR;
     }
 
-    startLoading(fp);
     while(1) {
         robj *key, *val;
         expiretime = -1;
 
         /* Read type. */
-        if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
+        if ((type = rdbLoadType(rdb)) == -1) goto eoferr;
 
         /* Handle special types. */
         if (type == RDB_OPCODE_EXPIRETIME) {
             /* EXPIRETIME: load an expire associated with the next key
              * to load. Note that after loading an expire we need to
              * load the actual type, and continue. */
-            if ((expiretime = rdbLoadTime(&rdb)) == -1) goto eoferr;
+            if ((expiretime = rdbLoadTime(rdb)) == -1) goto eoferr;
             /* We read the time so we need to read the object type again. */
-            if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
+            if ((type = rdbLoadType(rdb)) == -1) goto eoferr;
             /* the EXPIRETIME opcode specifies time in seconds, so convert
              * into milliseconds. */
             expiretime *= 1000;
         } else if (type == RDB_OPCODE_EXPIRETIME_MS) {
             /* EXPIRETIME_MS: milliseconds precision expire times introduced
              * with RDB v3. Like EXPIRETIME but no with more precision. */
-            if ((expiretime = rdbLoadMillisecondTime(&rdb)) == -1) goto eoferr;
+            if ((expiretime = rdbLoadMillisecondTime(rdb)) == -1) goto eoferr;
             /* We read the time so we need to read the object type again. */
-            if ((type = rdbLoadType(&rdb)) == -1) goto eoferr;
+            if ((type = rdbLoadType(rdb)) == -1) goto eoferr;
         } else if (type == RDB_OPCODE_EOF) {
             /* EOF: End of file, exit the main loop. */
             break;
         } else if (type == RDB_OPCODE_SELECTDB) {
             /* SELECTDB: Select the specified database. */
-            if ((dbid = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
+            if ((dbid = rdbLoadLen(rdb,NULL)) == RDB_LENERR)
                 goto eoferr;
             if (dbid >= (unsigned)server.dbnum) {
                 serverLog(LL_WARNING,
@@ -1448,9 +1455,9 @@ int rdbLoad(char *filename) {
             /* RESIZEDB: Hint about the size of the keys in the currently
              * selected data base, in order to avoid useless rehashing. */
             uint64_t db_size, expires_size;
-            if ((db_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
+            if ((db_size = rdbLoadLen(rdb,NULL)) == RDB_LENERR)
                 goto eoferr;
-            if ((expires_size = rdbLoadLen(&rdb,NULL)) == RDB_LENERR)
+            if ((expires_size = rdbLoadLen(rdb,NULL)) == RDB_LENERR)
                 goto eoferr;
             dictExpand(db->dict,db_size);
             dictExpand(db->expires,expires_size);
@@ -1462,8 +1469,8 @@ int rdbLoad(char *filename) {
              *
              * An AUX field is composed of two strings: key and value. */
             robj *auxkey, *auxval;
-            if ((auxkey = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
-            if ((auxval = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
+            if ((auxkey = rdbLoadStringObject(rdb)) == NULL) goto eoferr;
+            if ((auxval = rdbLoadStringObject(rdb)) == NULL) goto eoferr;
 
             if (((char*)auxkey->ptr)[0] == '%') {
                 /* All the fields with a name staring with '%' are considered
@@ -1485,9 +1492,9 @@ int rdbLoad(char *filename) {
         }
 
         /* Read key */
-        if ((key = rdbLoadStringObject(&rdb)) == NULL) goto eoferr;
+        if ((key = rdbLoadStringObject(rdb)) == NULL) goto eoferr;
         /* Read value */
-        if ((val = rdbLoadObject(type,&rdb)) == NULL) goto eoferr;
+        if ((val = rdbLoadObject(type,rdb)) == NULL) goto eoferr;
         /* Check if the key already expired. This function is used when loading
          * an RDB file from disk, either at startup, or when an RDB was
          * received from the master. In the latter case, the master is
@@ -1508,9 +1515,9 @@ int rdbLoad(char *filename) {
     }
     /* Verify the checksum if RDB version is >= 5 */
     if (rdbver >= 5 && server.rdb_checksum) {
-        uint64_t cksum, expected = rdb.cksum;
+        uint64_t cksum, expected = rdb->cksum;
 
-        if (rioRead(&rdb,&cksum,8) == 0) goto eoferr;
+        if (rioRead(rdb,&cksum,8) == 0) goto eoferr;
         memrev64ifbe(&cksum);
         if (cksum == 0) {
             serverLog(LL_WARNING,"RDB file was saved with checksum disabled: no check performed.");
@@ -1519,9 +1526,6 @@ int rdbLoad(char *filename) {
             rdbExitReportCorruptRDB("RDB CRC error");
         }
     }
-
-    fclose(fp);
-    stopLoading();
     return C_OK;
 
 eoferr: /* unexpected end of file is handled here with a fatal exit */
@@ -1530,6 +1534,24 @@ int rdbLoad(char *filename) {
     return C_ERR; /* Just to avoid warning */
 }
 
+/* Like rdbLoadRio() but takes a filename instead of a rio stream. The
+ * filename is open for reading and a rio stream object created in order
+ * to do the actual loading. Moreover the ETA displayed in the INFO
+ * output is initialized and finalized. */
+int rdbLoad(char *filename) {
+    FILE *fp;
+    rio rdb;
+    int retval;
+
+    if ((fp = fopen(filename,"r")) == NULL) return C_ERR;
+    startLoading(fp);
+    rioInitWithFile(&rdb,fp);
+    retval = rdbLoadRio(&rdb);
+    fclose(fp);
+    stopLoading();
+    return retval;
+}
+
 /* A background saving child (BGSAVE) terminated its work. Handle this.
  * This function covers the case of actual BGSAVEs. */
 void backgroundSaveDoneHandlerDisk(int exitcode, int bysignal) {