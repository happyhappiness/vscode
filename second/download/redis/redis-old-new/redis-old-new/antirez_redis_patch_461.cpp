@@ -726,11 +726,11 @@ int rdbSaveInfoAuxFields(rio *rdb) {
 }
 
 /* Produces a dump of the database in RDB format sending it to the specified
- * Redis I/O channel. On success REDIS_OK is returned, otherwise REDIS_ERR
+ * Redis I/O channel. On success C_OK is returned, otherwise C_ERR
  * is returned and part of the output, or all the output, can be
  * missing because of I/O errors.
  *
- * When the function returns REDIS_ERR and if 'error' is not NULL, the
+ * When the function returns C_ERR and if 'error' is not NULL, the
  * integer pointed by 'error' is set to the value of errno just after the I/O
  * error. */
 int rdbSaveRio(rio *rdb, int *error) {
@@ -752,7 +752,7 @@ int rdbSaveRio(rio *rdb, int *error) {
         dict *d = db->dict;
         if (dictSize(d) == 0) continue;
         di = dictGetSafeIterator(d);
-        if (!di) return REDIS_ERR;
+        if (!di) return C_ERR;
 
         /* Write the SELECT DB opcode */
         if (rdbSaveType(rdb,REDIS_RDB_OPCODE_SELECTDB) == -1) goto werr;
@@ -795,12 +795,12 @@ int rdbSaveRio(rio *rdb, int *error) {
     cksum = rdb->cksum;
     memrev64ifbe(&cksum);
     if (rioWrite(rdb,&cksum,8) == 0) goto werr;
-    return REDIS_OK;
+    return C_OK;
 
 werr:
     if (error) *error = errno;
     if (di) dictReleaseIterator(di);
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 /* This is just a wrapper to rdbSaveRio() that additionally adds a prefix
@@ -819,17 +819,17 @@ int rdbSaveRioWithEOFMark(rio *rdb, int *error) {
     if (rioWrite(rdb,"$EOF:",5) == 0) goto werr;
     if (rioWrite(rdb,eofmark,REDIS_EOF_MARK_SIZE) == 0) goto werr;
     if (rioWrite(rdb,"\r\n",2) == 0) goto werr;
-    if (rdbSaveRio(rdb,error) == REDIS_ERR) goto werr;
+    if (rdbSaveRio(rdb,error) == C_ERR) goto werr;
     if (rioWrite(rdb,eofmark,REDIS_EOF_MARK_SIZE) == 0) goto werr;
-    return REDIS_OK;
+    return C_OK;
 
 werr: /* Write error. */
     /* Set 'error' only if not already set by rdbSaveRio() call. */
     if (error && *error == 0) *error = errno;
-    return REDIS_ERR;
+    return C_ERR;
 }
 
-/* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success. */
+/* Save the DB on disk. Return C_ERR on error, C_OK on success. */
 int rdbSave(char *filename) {
     char tmpfile[256];
     FILE *fp;
@@ -841,11 +841,11 @@ int rdbSave(char *filename) {
     if (!fp) {
         serverLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
             strerror(errno));
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     rioInitWithFile(&rdb,fp);
-    if (rdbSaveRio(&rdb,&error) == REDIS_ERR) {
+    if (rdbSaveRio(&rdb,&error) == C_ERR) {
         errno = error;
         goto werr;
     }
@@ -860,26 +860,26 @@ int rdbSave(char *filename) {
     if (rename(tmpfile,filename) == -1) {
         serverLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
         unlink(tmpfile);
-        return REDIS_ERR;
+        return C_ERR;
     }
     serverLog(REDIS_NOTICE,"DB saved on disk");
     server.dirty = 0;
     server.lastsave = time(NULL);
-    server.lastbgsave_status = REDIS_OK;
-    return REDIS_OK;
+    server.lastbgsave_status = C_OK;
+    return C_OK;
 
 werr:
     serverLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
-    return REDIS_ERR;
+    return C_ERR;
 }
 
 int rdbSaveBackground(char *filename) {
     pid_t childpid;
     long long start;
 
-    if (server.rdb_child_pid != -1) return REDIS_ERR;
+    if (server.rdb_child_pid != -1) return C_ERR;
 
     server.dirty_before_bgsave = server.dirty;
     server.lastbgsave_try = time(NULL);
@@ -892,7 +892,7 @@ int rdbSaveBackground(char *filename) {
         closeListeningSockets(0);
         redisSetProcTitle("redis-rdb-bgsave");
         retval = rdbSave(filename);
-        if (retval == REDIS_OK) {
+        if (retval == C_OK) {
             size_t private_dirty = zmalloc_get_private_dirty();
 
             if (private_dirty) {
@@ -901,26 +901,26 @@ int rdbSaveBackground(char *filename) {
                     private_dirty/(1024*1024));
             }
         }
-        exitFromChild((retval == REDIS_OK) ? 0 : 1);
+        exitFromChild((retval == C_OK) ? 0 : 1);
     } else {
         /* Parent */
         server.stat_fork_time = ustime()-start;
         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
-            server.lastbgsave_status = REDIS_ERR;
+            server.lastbgsave_status = C_ERR;
             serverLog(REDIS_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));
-            return REDIS_ERR;
+            return C_ERR;
         }
         serverLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
         server.rdb_save_time_start = time(NULL);
         server.rdb_child_pid = childpid;
         server.rdb_child_type = REDIS_RDB_CHILD_TYPE_DISK;
         updateDictResizePolicy();
-        return REDIS_OK;
+        return C_OK;
     }
-    return REDIS_OK; /* unreached */
+    return C_OK; /* unreached */
 }
 
 void rdbRemoveTempFile(pid_t childpid) {
@@ -981,7 +981,7 @@ robj *rdbLoadObject(int rdbtype, rio *rdb) {
 
             if (o->encoding == OBJ_ENCODING_INTSET) {
                 /* Fetch integer value from element */
-                if (isObjectRepresentableAsLongLong(ele,&llval) == REDIS_OK) {
+                if (isObjectRepresentableAsLongLong(ele,&llval) == C_OK) {
                     o->ptr = intsetAdd(o->ptr,llval,NULL);
                 } else {
                     setTypeConvert(o,OBJ_ENCODING_HT);
@@ -1241,7 +1241,7 @@ int rdbLoad(char *filename) {
     FILE *fp;
     rio rdb;
 
-    if ((fp = fopen(filename,"r")) == NULL) return REDIS_ERR;
+    if ((fp = fopen(filename,"r")) == NULL) return C_ERR;
 
     rioInitWithFile(&rdb,fp);
     rdb.update_cksum = rdbLoadProgressCallback;
@@ -1252,14 +1252,14 @@ int rdbLoad(char *filename) {
         fclose(fp);
         serverLog(REDIS_WARNING,"Wrong signature trying to load DB from file");
         errno = EINVAL;
-        return REDIS_ERR;
+        return C_ERR;
     }
     rdbver = atoi(buf+5);
     if (rdbver < 1 || rdbver > REDIS_RDB_VERSION) {
         fclose(fp);
         serverLog(REDIS_WARNING,"Can't handle RDB format version %d",rdbver);
         errno = EINVAL;
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     startLoading(fp);
@@ -1381,12 +1381,12 @@ int rdbLoad(char *filename) {
 
     fclose(fp);
     stopLoading();
-    return REDIS_OK;
+    return C_OK;
 
 eoferr: /* unexpected end of file is handled here with a fatal exit */
     serverLog(REDIS_WARNING,"Short read or OOM loading DB. Unrecoverable error, aborting now.");
     rdbExitReportCorruptRDB("Unexpected EOF reading RDB file");
-    return REDIS_ERR; /* Just to avoid warning */
+    return C_ERR; /* Just to avoid warning */
 }
 
 /* A background saving child (BGSAVE) terminated its work. Handle this.
@@ -1397,10 +1397,10 @@ void backgroundSaveDoneHandlerDisk(int exitcode, int bysignal) {
             "Background saving terminated with success");
         server.dirty = server.dirty - server.dirty_before_bgsave;
         server.lastsave = time(NULL);
-        server.lastbgsave_status = REDIS_OK;
+        server.lastbgsave_status = C_OK;
     } else if (!bysignal && exitcode != 0) {
         serverLog(REDIS_WARNING, "Background saving error");
-        server.lastbgsave_status = REDIS_ERR;
+        server.lastbgsave_status = C_ERR;
     } else {
         mstime_t latency;
 
@@ -1413,15 +1413,15 @@ void backgroundSaveDoneHandlerDisk(int exitcode, int bysignal) {
         /* SIGUSR1 is whitelisted, so we have a way to kill a child without
          * tirggering an error conditon. */
         if (bysignal != SIGUSR1)
-            server.lastbgsave_status = REDIS_ERR;
+            server.lastbgsave_status = C_ERR;
     }
     server.rdb_child_pid = -1;
     server.rdb_child_type = REDIS_RDB_CHILD_TYPE_NONE;
     server.rdb_save_time_last = time(NULL)-server.rdb_save_time_start;
     server.rdb_save_time_start = -1;
     /* Possibly there are slaves waiting for a BGSAVE in order to be served
      * (the first stage of SYNC is a bulk transfer of dump.rdb) */
-    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? REDIS_OK : REDIS_ERR, REDIS_RDB_CHILD_TYPE_DISK);
+    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? C_OK : C_ERR, REDIS_RDB_CHILD_TYPE_DISK);
 }
 
 /* A background saving child (BGSAVE) terminated its work. Handle this.
@@ -1516,7 +1516,7 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
     }
     zfree(ok_slaves);
 
-    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? REDIS_OK : REDIS_ERR, REDIS_RDB_CHILD_TYPE_SOCKET);
+    updateSlavesWaitingBgsave((!bysignal && exitcode == 0) ? C_OK : C_ERR, REDIS_RDB_CHILD_TYPE_SOCKET);
 }
 
 /* When a background RDB saving/transfer terminates, call the right handler. */
@@ -1546,12 +1546,12 @@ int rdbSaveToSlavesSockets(void) {
     long long start;
     int pipefds[2];
 
-    if (server.rdb_child_pid != -1) return REDIS_ERR;
+    if (server.rdb_child_pid != -1) return C_ERR;
 
     /* Before to fork, create a pipe that will be used in order to
      * send back to the parent the IDs of the slaves that successfully
      * received all the writes. */
-    if (pipe(pipefds) == -1) return REDIS_ERR;
+    if (pipe(pipefds) == -1) return C_ERR;
     server.rdb_pipe_read_result_from_child = pipefds[0];
     server.rdb_pipe_write_result_to_parent = pipefds[1];
 
@@ -1594,10 +1594,10 @@ int rdbSaveToSlavesSockets(void) {
         redisSetProcTitle("redis-rdb-to-slaves");
 
         retval = rdbSaveRioWithEOFMark(&slave_sockets,NULL);
-        if (retval == REDIS_OK && rioFlush(&slave_sockets) == 0)
-            retval = REDIS_ERR;
+        if (retval == C_OK && rioFlush(&slave_sockets) == 0)
+            retval = C_ERR;
 
-        if (retval == REDIS_OK) {
+        if (retval == C_OK) {
             size_t private_dirty = zmalloc_get_private_dirty();
 
             if (private_dirty) {
@@ -1641,12 +1641,12 @@ int rdbSaveToSlavesSockets(void) {
                 write(server.rdb_pipe_write_result_to_parent,msg,msglen)
                 != msglen)
             {
-                retval = REDIS_ERR;
+                retval = C_ERR;
             }
             zfree(msg);
         }
         zfree(clientids);
-        exitFromChild((retval == REDIS_OK) ? 0 : 1);
+        exitFromChild((retval == C_OK) ? 0 : 1);
     } else {
         /* Parent */
         zfree(clientids); /* Not used by parent. Free ASAP. */
@@ -1659,25 +1659,25 @@ int rdbSaveToSlavesSockets(void) {
             zfree(fds);
             close(pipefds[0]);
             close(pipefds[1]);
-            return REDIS_ERR;
+            return C_ERR;
         }
         serverLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",childpid);
         server.rdb_save_time_start = time(NULL);
         server.rdb_child_pid = childpid;
         server.rdb_child_type = REDIS_RDB_CHILD_TYPE_SOCKET;
         updateDictResizePolicy();
         zfree(fds);
-        return REDIS_OK;
+        return C_OK;
     }
-    return REDIS_OK; /* unreached */
+    return C_OK; /* unreached */
 }
 
 void saveCommand(client *c) {
     if (server.rdb_child_pid != -1) {
         addReplyError(c,"Background save already in progress");
         return;
     }
-    if (rdbSave(server.rdb_filename) == REDIS_OK) {
+    if (rdbSave(server.rdb_filename) == C_OK) {
         addReply(c,shared.ok);
     } else {
         addReply(c,shared.err);
@@ -1689,7 +1689,7 @@ void bgsaveCommand(client *c) {
         addReplyError(c,"Background save already in progress");
     } else if (server.aof_child_pid != -1) {
         addReplyError(c,"Can't BGSAVE while AOF log rewriting is in progress");
-    } else if (rdbSaveBackground(server.rdb_filename) == REDIS_OK) {
+    } else if (rdbSaveBackground(server.rdb_filename) == C_OK) {
         addReplyStatus(c,"Background saving started");
     } else {
         addReply(c,shared.err);