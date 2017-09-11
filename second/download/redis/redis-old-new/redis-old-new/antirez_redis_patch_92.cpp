@@ -979,6 +979,18 @@ void replicationCreateMasterClient(int fd) {
         server.master->flags |= CLIENT_PRE_PSYNC;
 }
 
+void restartAOF() {
+    int retry = 10;
+    while (retry-- && startAppendOnly() == C_ERR) {
+        serverLog(LL_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
+        sleep(1);
+    }
+    if (!retry) {
+        serverLog(LL_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
+        exit(1);
+    }
+}
+
 /* Asynchronously read the SYNC payload we receive from a master */
 #define REPL_MAX_WRITTEN_BEFORE_FSYNC (1024*1024*8) /* 8 MB */
 void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
@@ -1120,12 +1132,15 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     }
 
     if (eof_reached) {
+        int aof_is_enabled = server.aof_state != AOF_OFF;
         if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
             serverLog(LL_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
             cancelReplicationHandshake();
             return;
         }
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
+        if(aof_is_enabled) /* we need to stop any AOFRW fork before flusing and parsing RDB, otherwise we'll create a CoW disaster */
+            stopAppendOnly();
         signalFlushedDb(-1);
         emptyDb(
             -1,
@@ -1140,6 +1155,8 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         if (rdbLoad(server.rdb_filename) != C_OK) {
             serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
             cancelReplicationHandshake();
+            if (aof_is_enabled) /* re-enable so that on the next attempt, we can detect that AOF was enabled */
+                restartAOF();
             return;
         }
         /* Final setup of the connected slave <- master link */
@@ -1150,19 +1167,8 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         /* Restart the AOF subsystem now that we finished the sync. This
          * will trigger an AOF rewrite, and when done will start appending
          * to the new file. */
-        if (server.aof_state != AOF_OFF) {
-            int retry = 10;
-
-            stopAppendOnly();
-            while (retry-- && startAppendOnly() == C_ERR) {
-                serverLog(LL_WARNING,"Failed enabling the AOF after successful master synchronization! Trying it again in one second.");
-                sleep(1);
-            }
-            if (!retry) {
-                serverLog(LL_WARNING,"FATAL: this slave instance finished the synchronization with its master, but the AOF can't be turned on. Exiting now.");
-                exit(1);
-            }
-        }
+        if (aof_is_enabled)
+            restartAOF();
     }
 
     return;