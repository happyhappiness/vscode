@@ -41,6 +41,7 @@ void replicationDiscardCachedMaster(void);
 void replicationResurrectCachedMaster(int newfd);
 void replicationSendAck(void);
 void putSlaveOnline(client *slave);
+int cancelReplicationHandshake(void);
 
 /* --------------------------- Utility functions ---------------------------- */
 
@@ -916,18 +917,6 @@ int slaveIsInHandshakeState(void) {
            server.repl_state <= REPL_STATE_RECEIVE_PSYNC;
 }
 
-/* Abort the async download of the bulk dataset while SYNC-ing with master */
-void replicationAbortSyncTransfer(void) {
-    serverAssert(server.repl_state == REPL_STATE_TRANSFER);
-
-    aeDeleteFileEvent(server.el,server.repl_transfer_s,AE_READABLE);
-    close(server.repl_transfer_s);
-    close(server.repl_transfer_fd);
-    unlink(server.repl_transfer_tmpfile);
-    zfree(server.repl_transfer_tmpfile);
-    server.repl_state = REPL_STATE_CONNECT;
-}
-
 /* Avoid the master to detect the slave is timing out while loading the
  * RDB file in initial synchronization. We send a single newline character
  * that is valid protocol but is guaranteed to either be sent entierly or
@@ -1053,7 +1042,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     if (nread <= 0) {
         serverLog(LL_WARNING,"I/O error trying to sync with MASTER: %s",
             (nread == -1) ? strerror(errno) : "connection lost");
-        replicationAbortSyncTransfer();
+        cancelReplicationHandshake();
         return;
     }
     server.stat_net_input_bytes += nread;
@@ -1113,7 +1102,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     if (eof_reached) {
         if (rename(server.repl_transfer_tmpfile,server.rdb_filename) == -1) {
             serverLog(LL_WARNING,"Failed trying to rename the temp DB into dump.rdb in MASTER <-> SLAVE synchronization: %s", strerror(errno));
-            replicationAbortSyncTransfer();
+            cancelReplicationHandshake();
             return;
         }
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Flushing old data");
@@ -1130,7 +1119,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
         serverLog(LL_NOTICE, "MASTER <-> SLAVE sync: Loading DB in memory");
         if (rdbLoad(server.rdb_filename) != C_OK) {
             serverLog(LL_WARNING,"Failed trying to load the MASTER synchronization DB from disk");
-            replicationAbortSyncTransfer();
+            cancelReplicationHandshake();
             return;
         }
         /* Final setup of the connected slave <- master link */
@@ -1159,7 +1148,7 @@ void readSyncBulkPayload(aeEventLoop *el, int fd, void *privdata, int mask) {
     return;
 
 error:
-    replicationAbortSyncTransfer();
+    cancelReplicationHandshake();
     return;
 }
 
@@ -1639,16 +1628,26 @@ int connectWithMaster(void) {
 }
 
 /* This function can be called when a non blocking connection is currently
- * in progress to undo it. */
+ * in progress to undo it.
+ * Never call this function directly, use cancelReplicationHandshake() instead.
+ */
 void undoConnectWithMaster(void) {
     int fd = server.repl_transfer_s;
 
-    serverAssert(server.repl_state == REPL_STATE_CONNECTING ||
-                 slaveIsInHandshakeState());
     aeDeleteFileEvent(server.el,fd,AE_READABLE|AE_WRITABLE);
     close(fd);
     server.repl_transfer_s = -1;
-    server.repl_state = REPL_STATE_CONNECT;
+}
+
+/* Abort the async download of the bulk dataset while SYNC-ing with master.
+ * Never call this function directly, use cancelReplicationHandshake() instead.
+ */
+void replicationAbortSyncTransfer(void) {
+    serverAssert(server.repl_state == REPL_STATE_TRANSFER);
+    undoConnectWithMaster();
+    close(server.repl_transfer_fd);
+    unlink(server.repl_transfer_tmpfile);
+    zfree(server.repl_transfer_tmpfile);
 }
 
 /* This function aborts a non blocking replication attempt if there is one
@@ -1662,10 +1661,12 @@ void undoConnectWithMaster(void) {
 int cancelReplicationHandshake(void) {
     if (server.repl_state == REPL_STATE_TRANSFER) {
         replicationAbortSyncTransfer();
+        server.repl_state = REPL_STATE_CONNECT;
     } else if (server.repl_state == REPL_STATE_CONNECTING ||
                slaveIsInHandshakeState())
     {
         undoConnectWithMaster();
+        server.repl_state = REPL_STATE_CONNECT;
     } else {
         return 0;
     }
@@ -2189,15 +2190,15 @@ void replicationCron(void) {
          (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
         serverLog(LL_WARNING,"Timeout connecting to the MASTER...");
-        undoConnectWithMaster();
+        cancelReplicationHandshake();
     }
 
     /* Bulk transfer I/O timeout? */
     if (server.masterhost && server.repl_state == REPL_STATE_TRANSFER &&
         (time(NULL)-server.repl_transfer_lastio) > server.repl_timeout)
     {
         serverLog(LL_WARNING,"Timeout receiving bulk data from MASTER... If the problem persists try to set the 'repl-timeout' parameter in redis.conf to a larger value.");
-        replicationAbortSyncTransfer();
+        cancelReplicationHandshake();
     }
 
     /* Timed out master when we are an already connected slave? */