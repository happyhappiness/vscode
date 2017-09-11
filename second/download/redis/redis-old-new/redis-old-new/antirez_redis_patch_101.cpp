@@ -835,7 +835,7 @@ int rdbSaveAuxFieldStrInt(rio *rdb, char *key, long long val) {
 }
 
 /* Save a few default AUX fields with information about the RDB generated. */
-int rdbSaveInfoAuxFields(rio *rdb, int flags) {
+int rdbSaveInfoAuxFields(rio *rdb, int flags, rdbSaveInfo *rsi) {
     int redis_bits = (sizeof(void*) == 8) ? 64 : 32;
     int aof_preamble = (flags & RDB_SAVE_AOF_PREAMBLE) != 0;
 
@@ -844,6 +844,16 @@ int rdbSaveInfoAuxFields(rio *rdb, int flags) {
     if (rdbSaveAuxFieldStrInt(rdb,"redis-bits",redis_bits) == -1) return -1;
     if (rdbSaveAuxFieldStrInt(rdb,"ctime",time(NULL)) == -1) return -1;
     if (rdbSaveAuxFieldStrInt(rdb,"used-mem",zmalloc_used_memory()) == -1) return -1;
+
+    /* Handle saving options that generate aux fields. */
+    if (rsi) {
+        if (rsi->repl_stream_db &&
+            rdbSaveAuxFieldStrInt(rdb,"repl-stream-db",rsi->repl_stream_db)
+            == -1)
+        {
+            return -1;
+        }
+    }
     if (rdbSaveAuxFieldStrInt(rdb,"aof-preamble",aof_preamble) == -1) return -1;
     return 1;
 }
@@ -856,7 +866,7 @@ int rdbSaveInfoAuxFields(rio *rdb, int flags) {
  * When the function returns C_ERR and if 'error' is not NULL, the
  * integer pointed by 'error' is set to the value of errno just after the I/O
  * error. */
-int rdbSaveRio(rio *rdb, int *error, int flags) {
+int rdbSaveRio(rio *rdb, int *error, int flags, rdbSaveInfo *rsi) {
     dictIterator *di = NULL;
     dictEntry *de;
     char magic[10];
@@ -869,7 +879,7 @@ int rdbSaveRio(rio *rdb, int *error, int flags) {
         rdb->update_cksum = rioGenericUpdateChecksum;
     snprintf(magic,sizeof(magic),"REDIS%04d",RDB_VERSION);
     if (rdbWriteRaw(rdb,magic,9) == -1) goto werr;
-    if (rdbSaveInfoAuxFields(rdb,flags) == -1) goto werr;
+    if (rdbSaveInfoAuxFields(rdb,flags,rsi) == -1) goto werr;
 
     for (j = 0; j < server.dbnum; j++) {
         redisDb *db = server.db+j;
@@ -945,15 +955,15 @@ int rdbSaveRio(rio *rdb, int *error, int flags) {
  * While the suffix is the 40 bytes hex string we announced in the prefix.
  * This way processes receiving the payload can understand when it ends
  * without doing any processing of the content. */
-int rdbSaveRioWithEOFMark(rio *rdb, int *error) {
+int rdbSaveRioWithEOFMark(rio *rdb, int *error, rdbSaveInfo *rsi) {
     char eofmark[RDB_EOF_MARK_SIZE];
 
     getRandomHexChars(eofmark,RDB_EOF_MARK_SIZE);
     if (error) *error = 0;
     if (rioWrite(rdb,"$EOF:",5) == 0) goto werr;
     if (rioWrite(rdb,eofmark,RDB_EOF_MARK_SIZE) == 0) goto werr;
     if (rioWrite(rdb,"\r\n",2) == 0) goto werr;
-    if (rdbSaveRio(rdb,error,RDB_SAVE_NONE) == C_ERR) goto werr;
+    if (rdbSaveRio(rdb,error,RDB_SAVE_NONE,rsi) == C_ERR) goto werr;
     if (rioWrite(rdb,eofmark,RDB_EOF_MARK_SIZE) == 0) goto werr;
     return C_OK;
 
@@ -964,7 +974,7 @@ int rdbSaveRioWithEOFMark(rio *rdb, int *error) {
 }
 
 /* Save the DB on disk. Return C_ERR on error, C_OK on success. */
-int rdbSave(char *filename) {
+int rdbSave(char *filename, rdbSaveInfo *rsi) {
     char tmpfile[256];
     char cwd[MAXPATHLEN]; /* Current working dir path for error messages. */
     FILE *fp;
@@ -985,7 +995,7 @@ int rdbSave(char *filename) {
     }
 
     rioInitWithFile(&rdb,fp);
-    if (rdbSaveRio(&rdb,&error,RDB_SAVE_NONE) == C_ERR) {
+    if (rdbSaveRio(&rdb,&error,RDB_SAVE_NONE,rsi) == C_ERR) {
         errno = error;
         goto werr;
     }
@@ -1023,7 +1033,7 @@ int rdbSave(char *filename) {
     return C_ERR;
 }
 
-int rdbSaveBackground(char *filename) {
+int rdbSaveBackground(char *filename, rdbSaveInfo *rsi) {
     pid_t childpid;
     long long start;
 
@@ -1040,7 +1050,7 @@ int rdbSaveBackground(char *filename) {
         /* Child */
         closeListeningSockets(0);
         redisSetProcTitle("redis-rdb-bgsave");
-        retval = rdbSave(filename);
+        retval = rdbSave(filename,rsi);
         if (retval == C_OK) {
             size_t private_dirty = zmalloc_get_private_dirty(-1);
 
@@ -1410,7 +1420,7 @@ void rdbLoadProgressCallback(rio *r, const void *buf, size_t len) {
 
 /* Load an RDB file from the rio stream 'rdb'. On success C_OK is returned,
  * otherwise C_ERR is returned and 'errno' is set accordingly. */
-int rdbLoadRio(rio *rdb) {
+int rdbLoadRio(rio *rdb, rdbSaveInfo *rsi) {
     uint64_t dbid;
     int type, rdbver;
     redisDb *db = server.db+0;
@@ -1501,6 +1511,8 @@ int rdbLoadRio(rio *rdb) {
                 serverLog(LL_NOTICE,"RDB '%s': %s",
                     (char*)auxkey->ptr,
                     (char*)auxval->ptr);
+            } else if (!strcasecmp(auxkey->ptr,"repl-stream-db")) {
+                if (rsi) rsi->repl_stream_db = atoi(auxval->ptr);
             } else {
                 /* We ignore fields we don't understand, as by AUX field
                  * contract. */
@@ -1559,16 +1571,19 @@ int rdbLoadRio(rio *rdb) {
 /* Like rdbLoadRio() but takes a filename instead of a rio stream. The
  * filename is open for reading and a rio stream object created in order
  * to do the actual loading. Moreover the ETA displayed in the INFO
- * output is initialized and finalized. */
-int rdbLoad(char *filename) {
+ * output is initialized and finalized.
+ *
+ * If you pass an 'rsi' structure initialied with RDB_SAVE_OPTION_INIT, the
+ * loading code will fiil the information fields in the structure. */
+int rdbLoad(char *filename, rdbSaveInfo *rsi) {
     FILE *fp;
     rio rdb;
     int retval;
 
     if ((fp = fopen(filename,"r")) == NULL) return C_ERR;
     startLoading(fp);
     rioInitWithFile(&rdb,fp);
-    retval = rdbLoadRio(&rdb);
+    retval = rdbLoadRio(&rdb,rsi);
     fclose(fp);
     stopLoading();
     return retval;
@@ -1721,7 +1736,7 @@ void backgroundSaveDoneHandler(int exitcode, int bysignal) {
 
 /* Spawn an RDB child that writes the RDB to the sockets of the slaves
  * that are currently in SLAVE_STATE_WAIT_BGSAVE_START state. */
-int rdbSaveToSlavesSockets(void) {
+int rdbSaveToSlavesSockets(rdbSaveInfo *rsi) {
     int *fds;
     uint64_t *clientids;
     int numfds;
@@ -1779,7 +1794,7 @@ int rdbSaveToSlavesSockets(void) {
         closeListeningSockets(0);
         redisSetProcTitle("redis-rdb-to-slaves");
 
-        retval = rdbSaveRioWithEOFMark(&slave_sockets,NULL);
+        retval = rdbSaveRioWithEOFMark(&slave_sockets,NULL,rsi);
         if (retval == C_OK && rioFlush(&slave_sockets) == 0)
             retval = C_ERR;
 
@@ -1884,7 +1899,7 @@ void saveCommand(client *c) {
         addReplyError(c,"Background save already in progress");
         return;
     }
-    if (rdbSave(server.rdb_filename) == C_OK) {
+    if (rdbSave(server.rdb_filename,NULL) == C_OK) {
         addReply(c,shared.ok);
     } else {
         addReply(c,shared.err);
@@ -1918,7 +1933,7 @@ void bgsaveCommand(client *c) {
                 "Use BGSAVE SCHEDULE in order to schedule a BGSAVE whenver "
                 "possible.");
         }
-    } else if (rdbSaveBackground(server.rdb_filename) == C_OK) {
+    } else if (rdbSaveBackground(server.rdb_filename,NULL) == C_OK) {
         addReplyStatus(c,"Background saving started");
     } else {
         addReply(c,shared.err);