@@ -1241,14 +1241,16 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     if (eof_reached) {
         int aof_is_enabled = server.aof_state != AOF_OFF;
+
         if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
             serverLog(LL_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
             cancelReplicationHandshake();
             return;
         }
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
-        if(aof_is_enabled) /* we need to stop any AOFRW fork before flusing and parsing RDB, otherwise we'll create a CoW disaster */
-            stopAppendOnly();
+        /* We need to stop any AOFRW fork before flusing and parsing
+         * RDB, otherwise we'll create a copy-on-write disaster. */
+        if(aof_is_enabled) stopAppendOnly();
         signalFlushedDb(-1);
         emptyDb(
             -1,
@@ -1264,8 +1266,9 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         if (rdbLoad(server.rdb_filename,&rsi) != C_OK) {
             serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
             cancelReplicationHandshake();
-            if (aof_is_enabled) /* re-enable so that on the next attempt, we can detect that AOF was enabled */
-                restartAOF();
+            /* Re-enable the AOF if we disabled it earlier, in order to restore
+             * the original configuration. */
+            if (aof_is_enabled) restartAOF();
             return;
         }
         /* Final setup of the connected slave <- master link */
@@ -1289,10 +1292,8 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         /* Restart the AOF subsystem now that we finished the sync. This
          * will trigger an AOF rewrite, and when done will start appending
          * to the new file. */
-        if (aof_is_enabled)
-            restartAOF();
+        if (aof_is_enabled) restartAOF();
     }
-
     return;
 
 error: