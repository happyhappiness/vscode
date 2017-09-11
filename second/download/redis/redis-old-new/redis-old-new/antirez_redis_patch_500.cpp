@@ -47,7 +47,7 @@
 #define rdbExitReportCorruptRDB(reason) rdbCheckThenExit(reason, __LINE__);
 
 void rdbCheckThenExit(char *reason, int where) {
-    redisLog(REDIS_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
+    serverLog(REDIS_WARNING, "Corrupt RDB detected at rdb.c:%d (%s). "
         "Running 'redis-check-rdb %s'",
         where, reason, server.rdb_filename);
     redis_check_rdb(server.rdb_filename);
@@ -839,7 +839,7 @@ int rdbSave(char *filename) {
     snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
     fp = fopen(tmpfile,"w");
     if (!fp) {
-        redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
+        serverLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
             strerror(errno));
         return REDIS_ERR;
     }
@@ -858,18 +858,18 @@ int rdbSave(char *filename) {
     /* Use RENAME to make sure the DB file is changed atomically only
      * if the generate DB file is ok. */
     if (rename(tmpfile,filename) == -1) {
-        redisLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
+        serverLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
         unlink(tmpfile);
         return REDIS_ERR;
     }
-    redisLog(REDIS_NOTICE,"DB saved on disk");
+    serverLog(REDIS_NOTICE,"DB saved on disk");
     server.dirty = 0;
     server.lastsave = time(NULL);
     server.lastbgsave_status = REDIS_OK;
     return REDIS_OK;
 
 werr:
-    redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
+    serverLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
     fclose(fp);
     unlink(tmpfile);
     return REDIS_ERR;
@@ -896,7 +896,7 @@ int rdbSaveBackground(char *filename) {
             size_t private_dirty = zmalloc_get_private_dirty();
 
             if (private_dirty) {
-                redisLog(REDIS_NOTICE,
+                serverLog(REDIS_NOTICE,
                     "RDB: %zu MB of memory used by copy-on-write",
                     private_dirty/(1024*1024));
             }
@@ -909,11 +909,11 @@ int rdbSaveBackground(char *filename) {
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
             server.lastbgsave_status = REDIS_ERR;
-            redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
+            serverLog(REDIS_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));
             return REDIS_ERR;
         }
-        redisLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
+        serverLog(REDIS_NOTICE,"Background saving started by pid %d",childpid);
         server.rdb_save_time_start = time(NULL);
         server.rdb_child_pid = childpid;
         server.rdb_child_type = REDIS_RDB_CHILD_TYPE_DISK;
@@ -1250,14 +1250,14 @@ int rdbLoad(char *filename) {
     buf[9] = '\0';
     if (memcmp(buf,"REDIS",5) != 0) {
         fclose(fp);
-        redisLog(REDIS_WARNING,"Wrong signature trying to load DB from file");
+        serverLog(REDIS_WARNING,"Wrong signature trying to load DB from file");
         errno = EINVAL;
         return REDIS_ERR;
     }
     rdbver = atoi(buf+5);
     if (rdbver < 1 || rdbver > REDIS_RDB_VERSION) {
         fclose(fp);
-        redisLog(REDIS_WARNING,"Can't handle RDB format version %d",rdbver);
+        serverLog(REDIS_WARNING,"Can't handle RDB format version %d",rdbver);
         errno = EINVAL;
         return REDIS_ERR;
     }
@@ -1295,7 +1295,7 @@ int rdbLoad(char *filename) {
             if ((dbid = rdbLoadLen(&rdb,NULL)) == REDIS_RDB_LENERR)
                 goto eoferr;
             if (dbid >= (unsigned)server.dbnum) {
-                redisLog(REDIS_WARNING,
+                serverLog(REDIS_WARNING,
                     "FATAL: Data file was created with a Redis "
                     "server configured to handle more than %d "
                     "databases. Exiting\n", server.dbnum);
@@ -1328,13 +1328,13 @@ int rdbLoad(char *filename) {
                 /* All the fields with a name staring with '%' are considered
                  * information fields and are logged at startup with a log
                  * level of NOTICE. */
-                redisLog(REDIS_NOTICE,"RDB '%s': %s",
+                serverLog(REDIS_NOTICE,"RDB '%s': %s",
                     (char*)auxkey->ptr,
                     (char*)auxval->ptr);
             } else {
                 /* We ignore fields we don't understand, as by AUX field
                  * contract. */
-                redisLog(REDIS_DEBUG,"Unrecognized RDB AUX field: '%s'",
+                serverLog(REDIS_DEBUG,"Unrecognized RDB AUX field: '%s'",
                     (char*)auxkey->ptr);
             }
 
@@ -1372,9 +1372,9 @@ int rdbLoad(char *filename) {
         if (rioRead(&rdb,&cksum,8) == 0) goto eoferr;
         memrev64ifbe(&cksum);
         if (cksum == 0) {
-            redisLog(REDIS_WARNING,"RDB file was saved with checksum disabled: no check performed.");
+            serverLog(REDIS_WARNING,"RDB file was saved with checksum disabled: no check performed.");
         } else if (cksum != expected) {
-            redisLog(REDIS_WARNING,"Wrong RDB checksum. Aborting now.");
+            serverLog(REDIS_WARNING,"Wrong RDB checksum. Aborting now.");
             rdbExitReportCorruptRDB("RDB CRC error");
         }
     }
@@ -1384,7 +1384,7 @@ int rdbLoad(char *filename) {
     return REDIS_OK;
 
 eoferr: /* unexpected end of file is handled here with a fatal exit */
-    redisLog(REDIS_WARNING,"Short read or OOM loading DB. Unrecoverable error, aborting now.");
+    serverLog(REDIS_WARNING,"Short read or OOM loading DB. Unrecoverable error, aborting now.");
     rdbExitReportCorruptRDB("Unexpected EOF reading RDB file");
     return REDIS_ERR; /* Just to avoid warning */
 }
@@ -1393,18 +1393,18 @@ int rdbLoad(char *filename) {
  * This function covers the case of actual BGSAVEs. */
 void backgroundSaveDoneHandlerDisk(int exitcode, int bysignal) {
     if (!bysignal && exitcode == 0) {
-        redisLog(REDIS_NOTICE,
+        serverLog(REDIS_NOTICE,
             "Background saving terminated with success");
         server.dirty = server.dirty - server.dirty_before_bgsave;
         server.lastsave = time(NULL);
         server.lastbgsave_status = REDIS_OK;
     } else if (!bysignal && exitcode != 0) {
-        redisLog(REDIS_WARNING, "Background saving error");
+        serverLog(REDIS_WARNING, "Background saving error");
         server.lastbgsave_status = REDIS_ERR;
     } else {
         mstime_t latency;
 
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Background saving terminated by signal %d", bysignal);
         latencyStartMonitor(latency);
         rdbRemoveTempFile(server.rdb_child_pid);
@@ -1431,12 +1431,12 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
     uint64_t *ok_slaves;
 
     if (!bysignal && exitcode == 0) {
-        redisLog(REDIS_NOTICE,
+        serverLog(REDIS_NOTICE,
             "Background RDB transfer terminated with success");
     } else if (!bysignal && exitcode != 0) {
-        redisLog(REDIS_WARNING, "Background transfer error");
+        serverLog(REDIS_WARNING, "Background transfer error");
     } else {
-        redisLog(REDIS_WARNING,
+        serverLog(REDIS_WARNING,
             "Background transfer terminated by signal %d", bysignal);
     }
     server.rdb_child_pid = -1;
@@ -1498,14 +1498,14 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
                 }
             }
             if (j == ok_slaves[0] || errorcode != 0) {
-                redisLog(REDIS_WARNING,
+                serverLog(REDIS_WARNING,
                 "Closing slave %s: child->slave RDB transfer failed: %s",
                     replicationGetSlaveName(slave),
                     (errorcode == 0) ? "RDB transfer child aborted"
                                      : strerror(errorcode));
                 freeClient(slave);
             } else {
-                redisLog(REDIS_WARNING,
+                serverLog(REDIS_WARNING,
                 "Slave %s correctly received the streamed RDB file.",
                     replicationGetSlaveName(slave));
                 /* Restore the socket as non-blocking. */
@@ -1601,7 +1601,7 @@ int rdbSaveToSlavesSockets(void) {
             size_t private_dirty = zmalloc_get_private_dirty();
 
             if (private_dirty) {
-                redisLog(REDIS_NOTICE,
+                serverLog(REDIS_NOTICE,
                     "RDB: %zu MB of memory used by copy-on-write",
                     private_dirty/(1024*1024));
             }
@@ -1654,14 +1654,14 @@ int rdbSaveToSlavesSockets(void) {
         server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
         latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
         if (childpid == -1) {
-            redisLog(REDIS_WARNING,"Can't save in background: fork: %s",
+            serverLog(REDIS_WARNING,"Can't save in background: fork: %s",
                 strerror(errno));
             zfree(fds);
             close(pipefds[0]);
             close(pipefds[1]);
             return REDIS_ERR;
         }
-        redisLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",childpid);
+        serverLog(REDIS_NOTICE,"Background RDB transfer started by pid %d",childpid);
         server.rdb_save_time_start = time(NULL);
         server.rdb_child_pid = childpid;
         server.rdb_child_type = REDIS_RDB_CHILD_TYPE_SOCKET;